#include "bigint.h"
#include <assert.h>

uint64_t adc64(uint64_t a, uint64_t b, uint64_t* c) {
  *c = a + b;
  return *c < a;
}

uint64_t sbb64(uint64_t a, uint64_t b, uint64_t* c) {
  *c = a - b;
  return *c > a;
}

uint64_t umul64(uint64_t a, uint64_t b, uint64_t* lo) {
  const uint64_t a_lo = a & UINT32_MAX, a_hi = a >> 32;
  const uint64_t b_lo = b & UINT32_MAX, b_hi = b >> 32;
  const uint64_t m1 = a_lo * b_hi, m2 = b_lo * a_hi;
  uint64_t hi = a_hi * b_hi + (m1 >> 32) + (m2 >> 32);
  hi += adc64(m1 << 32, m2 << 32, &b); 
  hi += adc64(a_lo * b_lo, b, lo);
  return hi;
}

uint128_t add128(uint128_t a, uint128_t b) {
  uint128_t c;
  c.hi = a.hi + b.hi;
  c.hi += adc64(a.lo, b.lo, &c.lo);
  return c;
}
  
uint128_t sub128(uint128_t a, uint128_t b) {
  uint128_t c;
  c.hi = a.hi - b.hi;
  c.hi -= sbb64(a.lo, b.lo, &c.lo);
  return c;
}

uint128_t mul128(uint128_t a, uint128_t b) {
  uint128_t c;
  c.hi = umul64(a.lo, b.lo, &c.lo);
  c.hi += a.lo * b.hi;
  c.hi += b.lo * a.hi;
  return c;
}

int cmp128(uint128_t a, uint128_t b) {
  if (a.hi != b.hi) return a.hi < b.hi ? -1 : 1;
  else return a.lo < b.lo ? -1 : a.lo != b.lo; 
}

// 128 > sh >= 0
uint128_t shl128(uint128_t a, int sh) {
  assert(sh < 128 && sh >= 0);
  if (sh == 0) 
    return a;
  
  if (sh <= 63) {
    a.hi = (a.hi << sh) | (a.lo >> (64 - sh));
    a.lo <<= sh;
  } else {
    a.hi = a.lo << (sh - 64); 
    a.lo = 0;
  }
  return a;
}

// 128 > sh >= 0
uint128_t shr128(uint128_t a, int sh) {
  assert(sh < 128 && sh >= 0);
  if (sh == 0) 
    return a;
  
  if (sh <= 63) {
    a.lo = (a.lo >> sh) | (a.hi << (64 - sh));
    a.hi >>= sh;
  } else {
    a.lo = a.hi >> (sh - 64);
    a.hi = 0;
  }
  return a;
}

int clz128(uint128_t a) {
  return a.hi > 0 ? __builtin_clzll(a.hi) : 64 + __builtin_clzll(a.lo); 
}

uint128_t and128(uint128_t a, uint128_t b) {
  a.lo &= b.lo;
  a.hi &= b.hi;
  return a;
}

uint128_t or128(uint128_t a, uint128_t b) {
  a.lo |= b.lo;
  a.hi |= b.hi;
  return a;
}

uint128_t xor128(uint128_t a, uint128_t b) {
  a.lo ^= b.lo;
  a.hi ^= b.hi;
  return a;
}

// The idea from: https://danlark.org/2020/06/14/128-bit-division/
uint128_t divmod128(uint128_t a, uint128_t b, uint128_t* rem) {
  assert((b.lo | b.hi) != 0);

  if (cmp128(a, b) < 0) {
    if (rem) *rem = a;
    return UINT128_ZERO;
  }

  int shift = clz128(b) - clz128(a);
  b = shl128(b, shift);
  uint128_t quot =  UINT128_ZERO;
  for (; shift >= 0; --shift) {
    quot = shl128(quot, 1);
    if (cmp128(a, b) >= 0) {
      a = sub128(a, b);
      quot = or128(quot, UINT128_C(1));
    }
    b = shr128(b, 1);
  }

  if (rem) *rem = a;
  return quot;
}

uint128_t div128(uint128_t a, uint128_t b) {
  return divmod128(a, b, NULL);
}

uint128_t adc128(uint128_t a, uint128_t b, uint128_t* c) {
  *c = add128(a, b);
  return UINT128_C(cmp128(*c, a) < 0);
}

uint128_t sbb128(uint128_t a, uint128_t b, uint128_t* c) {
  *c = sub128(a, b);
  return UINT128_C(cmp128(*c, a) > 0);
}

uint128_t umul128(uint128_t a, uint128_t b, uint128_t* lo) {
  uint128_t hi;
  uint64_t m;
  lo->hi = umul64(a.lo, b.lo, &lo->lo);
  hi.lo = umul64(a.lo, b.hi, &m);
  lo->hi += m;
  hi.hi = adc64(hi.lo, umul64(b.lo, a.hi, &m), &hi.lo);
  lo->hi += m; 
  hi.hi += a.hi * b.hi;
  return hi;
}

static bool eq128(uint128_t a, uint128_t b) {
  return a.hi == b.hi && a.lo == b.lo;
}

int cmp256(uint256_t a, uint256_t b) {
  if (!eq128(a.hi, b.hi)) return cmp128(a.hi, b.hi);
  else return cmp128(a.lo, b.lo); 
}

uint256_t shl256(uint256_t a, int sh) {
  assert(sh < 256 && sh >= 0);
  if (sh == 0) 
    return a;
  
  if (sh <= 127) {
    a.hi = or128(shl128(a.hi, sh), shr128(a.lo, 128 - sh));
    a.lo = shl128(a.lo, sh);
  } else {
    a.hi = shl128(a.lo, sh - 128); 
    a.lo = UINT128_ZERO;
  }
  return a;
}

uint256_t shr256(uint256_t a, int sh) {
  assert(sh < 256 && sh >= 0);
  if (sh == 0) 
    return a;
  
  if (sh <= 127) {
    a.lo = or128(shr128(a.lo, sh), shl128(a.hi, 128 - sh));
    a.hi = shr128(a.hi, sh);
  } else {
    a.lo = shr128(a.hi, sh - 128);
    a.hi = UINT128_ZERO;
  }
  return a;
}

uint256_t and256(uint256_t a, uint256_t b) {
  a.lo = and128(a.lo, b.lo);
  a.hi = and128(a.hi, b.hi);
  return a;
}

uint256_t or256(uint256_t a, uint256_t b) {
  a.lo = or128(a.lo, b.lo);
  a.hi = or128(a.hi, b.hi);
  return a;
}

uint256_t xor256(uint256_t a, uint256_t b) {
  a.lo = xor128(a.lo, b.lo);
  a.hi = xor128(a.hi, b.hi);
  return a;
}

uint256_t add256(uint256_t a, uint256_t b) {
  uint256_t c;
  c.hi = add128(a.hi, b.hi);
  c.hi = add128(c.hi, adc128(a.lo, b.lo, &c.lo));
  return c;
}

uint256_t sub256(uint256_t a, uint256_t b) {
  uint256_t c;
  c.hi = sub128(a.hi, b.hi);
  c.hi = sub128(c.hi, sbb128(a.lo, b.lo, &c.lo));
  return c;
}

uint256_t mul256(uint256_t a, uint256_t b) {
  uint256_t c;
  c.hi = umul128(a.lo, b.lo, &c.lo);
  c.hi = add128(c.hi, mul128(a.lo, b.hi));
  c.hi = add128(c.hi, mul128(b.lo, a.hi));
  return c;
}

int clz256(uint256_t a) {
  return cmp128(a.hi, UINT128_ZERO) > 0 ? clz128(a.hi) : 128 + clz128(a.lo);
}

// The idea from: https://danlark.org/2020/06/14/128-bit-division/
uint256_t divmod256(uint256_t a, uint256_t b, uint256_t* rem) {
  assert(!eq128(or128(b.lo, b.hi), UINT128_ZERO));

  if (cmp256(a, b) < 0) {
    if (rem) *rem = a;
    return UINT256_ZERO;
  }

  int shift = clz256(b) - clz256(a);
  b = shl256(b, shift);
  uint256_t quot = UINT256_ZERO;
  for (; shift >= 0; --shift) {
    quot = shl256(quot, 1);
    if (cmp256(a, b) >= 0) {
      a = sub256(a, b);
      quot = or256(quot, UINT256_C(1));
    }
    b = shr256(b, 1);
  }

  if (rem) *rem = a;
  return quot;
}

uint256_t div256(uint256_t a, uint256_t b) {
  return divmod256(a, b, NULL);
}
