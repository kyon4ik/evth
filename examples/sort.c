#include <stdio.h>
#include <string.h>
#include "../sort.h" 
#include "../binheap.h"

int asc(const void* x, const void* y) {
  return *(int*)x - *(int*)y;
}

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  vec_t a, b;
  vec_init(&a, n, sizeof(int));
  vec_init(&b, m, sizeof(int));

  int el;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &el);
    vec_push(&a, &el);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d", &el);
    vec_push(&b, &el);
  }

  quick_sort(a.data.elems, a.len, sizeof(int), asc);
  binheap_sort(b, asc);

  for (int i = 0; i < n; ++i) {
    printf("%d ", *(int*)vec_index(&a, i));
  }
  printf("\n");
  for (int i = 0; i < m; ++i) {
    printf("%d ", *(int*)vec_index(&b, i));
  }
  printf("\n");

  int j = 0;
  for (int i = 0; i < n; ++i) {
    while (j < m && memcmp(vec_index(&b, j), vec_index(&a, i), sizeof(int)) < 0) {
      j += 1;
    }
    if (j < m && memcmp(vec_index(&b, j), vec_index(&a, i), sizeof(int)) == 0) {
      printf("%d ", *(int*)vec_index(&a, i));
      j += 1;
    }
  }

  vec_del(&a);
  vec_del(&b);
}
