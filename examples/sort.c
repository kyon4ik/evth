#include <stdio.h>
#include <stdlib.h>
#include "../sort.h" 

int comp(const void* _x, const void* _y) {
  const int* x = (const int*)_x;
  const int* y = (const int*)_y;
  return *x - *y;
}

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  int* a = (int*)calloc(n, sizeof(int));
  int* b = (int*)calloc(m, sizeof(int));
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d", &b[i]);
  }

  quick_sort(a, n, sizeof(*a), comp);
  quick_sort(b, m, sizeof(*b), comp);

  int j = 0;
  for (int i = 0; i < n; ++i) {
    while (j < m && b[j] < a[i]) {
      j += 1;
    }
    if (j < m && b[j] == a[i]) {
      printf("%d ", a[i]);
      j += 1;
    }
  }

  free(a);
  free(b);
}
