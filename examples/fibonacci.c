#include <stdio.h>
#include "bigint.h"

const size_t MAXN = 200;

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

int main(void) {
  uint256_t fib[2];
  fib[0] = UINT256_C(0);
  fib[1] = UINT256_C(1);
  
  print256("0:", fib[0]);
  print256("1:", fib[1]);
  
  for (size_t i = 2; i <= MAXN; ++i) {
    fib[i&1] = add256(fib[0], fib[1]);
    if (i < 10 || i % 10 == 0) {
      printf("%lu:", i);
      print256("", fib[i&1]);
    }
  }
}
