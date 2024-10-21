#pragma once

#include <stdint.h>

#include "vec.h"

#define UINT128_MAX (uint128_t){ .lo = UINT64_MAX, .hi = UINT64_MAX }
#define UINT128_ZERO (uint128_t){ .lo = 0, .hi = 0 }
#define UINT128_C(x) (uint128_t) { .lo = x, .hi = 0 }

#define UINT256_MAX (uint256_t){ .lo = UINT128_MAX, .hi = UINT128_MAX }
#define UINT256_ZERO (uint256_t){ .lo = UINT128_ZERO, .hi = UINT128_ZERO }
#define UINT256_C(x) (uint256_t) { .lo = UINT128_C(x), .hi = UINT128_ZERO }

typedef struct {
  uint64_t lo, hi;
} uint128_t;

typedef struct {
  uint128_t lo, hi; 
} uint256_t;

typedef struct {
  vec_t dig; 
} biguint_t;

uint64_t adc64(uint64_t a, uint64_t b, uint64_t* c);
uint64_t sbb64(uint64_t a, uint64_t b, uint64_t* c);
uint64_t umul64(uint64_t a, uint64_t b, uint64_t* lo);

uint128_t adc128(uint128_t a, uint128_t b, uint128_t* c);
uint128_t sbb128(uint128_t a, uint128_t b, uint128_t* c);
uint128_t umul128(uint128_t a, uint128_t b, uint128_t* lo);

int cmp128(uint128_t a, uint128_t b);
int cmp256(uint256_t a, uint256_t b);

int clz128(uint128_t a);
int clz256(uint256_t a);

uint128_t shl128(uint128_t a, int sh);
uint128_t shr128(uint128_t a, int sh);
uint128_t and128(uint128_t a, uint128_t b);
uint128_t or128(uint128_t a, uint128_t b);
uint128_t xor128(uint128_t a, uint128_t b);

uint256_t shl256(uint256_t a, int sh);
uint256_t shr256(uint256_t a, int sh);
uint256_t and256(uint256_t a, uint256_t b);
uint256_t or256(uint256_t a, uint256_t b);
uint256_t xor256(uint256_t a, uint256_t b);

uint128_t add128(uint128_t a, uint128_t b);
uint128_t sub128(uint128_t a, uint128_t b);
uint128_t mul128(uint128_t a, uint128_t b);
uint128_t div128(uint128_t a, uint128_t b);
uint128_t divmod128(uint128_t a, uint128_t b, uint128_t* rem);

uint256_t add256(uint256_t a, uint256_t b);
uint256_t sub256(uint256_t a, uint256_t b);
uint256_t mul256(uint256_t a, uint256_t b);
uint256_t div256(uint256_t a, uint256_t b);
uint256_t divmod256(uint256_t a, uint256_t b, uint256_t* rem);
