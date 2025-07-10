#include <stdio.h>
#include "bigint.h"
#include "macro.h"

void print256(const char* msg, uint256_t x) {
  uint256_t rem = UINT256_ZERO;
  char dec[80] = {0};
  dec[0] = '0';
  size_t p = 0;
  while (cmp256(x, UINT256_ZERO) > 0) {
    x = divmod256(x, UINT256_C(10), &rem);
    dec[p++] = rem.lo.lo + '0';
  }
  for (size_t i = 0; i < p / 2; ++i) {
    char tmp = dec[i];
    dec[i] = dec[p - i - 1];
    dec[p - i - 1] = tmp;
  }
  printf("%s %s\n", msg, dec);
}

void print_biguint(const char* msg, const biguint_t* x) {
  vec_t dec;
  vec_init(&dec, 256, sizeof(char));
  biguint_t y, z;
  biguint_copy(&y, x);
  while (y.dig.len > 1 || *(uint64_t*)vec_first(&y.dig) > 0) {
    uint64_t rem = biguint_div64(&y, 10, &z);
    char el = rem + '0';
    vec_push(&dec, &el);
    Swap(&y, &z, biguint_t);
    biguint_del(&z);
  }
  biguint_del(&y);
  biguint_del(&z);
  
  for (size_t i = 0; i < dec.len / 2; ++i) {
    Swap((char*)vec_index(&dec, i), (char*)vec_index(&dec, dec.len-i-1), char);
  }
  
  if (dec.len == 0)
    vec_push(&dec, "0");
  vec_push(&dec, "\0");
  printf("%s %s\n", msg, (char*)dec.data.elems);
  vec_del(&dec);
}

void fib256(size_t maxn) {
  uint256_t fib[2];
  fib[0] = UINT256_C(0);
  fib[1] = UINT256_C(1);
  
  print256("0:", fib[0]);
  print256("1:", fib[1]);
  
  for (size_t i = 2; i <= maxn; ++i) {
    fib[i&1] = add256(fib[0], fib[1]);
    if (i < 10 || i % 10 == 0) {
      printf("%lu:", i);
      print256("", fib[i&1]);
    }
  }
}

void fib_biguint(size_t maxn) {
  biguint_t fib[2];
  biguint_init(&fib[0], 0);
  biguint_init(&fib[1], 1);
  
  print_biguint("0:", &fib[0]);
  print_biguint("1:", &fib[1]);
  
  for (size_t i = 2; i <= maxn; ++i) {
    biguint_adds(&fib[i&1], &fib[(i&1)^1]);
    if (i < 10 || i % 10 == 0) {
      printf("%lu:", i);
      print_biguint("", &fib[i&1]);
    }
  }

  biguint_del(&fib[0]);
  biguint_del(&fib[1]);
}

int main(void) {
  fib256(200);
  fib_biguint(500);
}
