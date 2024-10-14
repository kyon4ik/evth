#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../binheap.h" 

#define SGN(X) ((X) > 0 ? 1 : ((X) < 0 ? -1 : 0)) 

int asc(const void* x, const void* y) {
  return SGN(*(int64_t*)y - *(int64_t*)x);
}

int main(void) {
  int n;
  scanf("%d", &n);

  vec_t v;
  vec_init(&v, n, sizeof(int64_t));
  for (int i = 0; i < n; ++i) {
    int64_t x;
    scanf("%ld", &x);
    vec_push(&v, &x);
  }
  
  binheap_t heap; 
  binheap_build(&heap, v.data.elems, n, asc, sizeof(int64_t));
  vec_del(&v);

  int64_t res = 0;
  while (heap.data.len > 1) {
    int64_t x, y; 
    memcpy(&x, binheap_peek(&heap), sizeof(int64_t));
    binheap_pop(&heap);
    memcpy(&y, binheap_peek(&heap), sizeof(int64_t));
    binheap_pop(&heap);
    int64_t z = x + y;
    res += z;
    binheap_push(&heap, &z);
  }
  
  printf("%ld\n", res);
  binheap_del(&heap);
}
