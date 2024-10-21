#include <stdio.h>
#include "bigint.h" 

const size_t MAX_N = 50;

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
  uint256_t fact = UINT256_C(1);
  print256("0! =", fact);

  for (size_t i = 1; i <= MAX_N; ++i) {
    fact = mul256(fact, UINT256_C(i)); 
    printf("%lu! =", i);
    print256("", fact);
  } 
}
