#include "sort.h"
#include <stdlib.h>
#include <string.h>

static void merge_sort_impl(void* buf, void* base, size_t n, size_t size, compare_fn comp) {
  if (n == 1) {
    memcpy(buf, base, size);
    return;
  }

  size_t n1 = n / 2, n2 = n - n1;
  char* base2 = (char*)base + n1 * size;
  char* buf2 = (char*)buf + n1 * size;
  merge_sort_impl(base, buf, n1, size, comp);
  merge_sort_impl(base2, buf2, n2, size, comp);
  merge(buf, base, n1, base2, n2, size, comp);
}

static size_t lomuto_partition(void* base, size_t n, size_t size, compare_fn comp, void* slot) {
  char* end = (char*)base + n * size;
  char* pivot = end - size;
  char* tmp = (char*)base; 

  for (char* ptr = (char*)base; ptr + size < end; ptr += size) {
    if (comp(ptr, pivot) <= 0) {
      swap(tmp, ptr, size, slot);
      tmp += size;
    }
  }

  swap(tmp, pivot, size, slot);
  return (tmp - (char*)base) / size;
}

static void quick_sort_impl(void* base, size_t n, size_t size, compare_fn comp, void* slot) {
  if (n < 2) return;

  size_t pivot = lomuto_partition(base, n, size, comp, slot);
  char* base2 = (char*)base + (pivot + 1) * size;
  quick_sort_impl(base, pivot, size, comp, slot);
  quick_sort_impl(base2, n - pivot - 1, size, comp, slot);
}

void quick_sort(void* base, size_t n, size_t size, compare_fn comp) {
  char slot[size];
  quick_sort_impl(base, n, size, comp, slot);
}

void merge_sort(void* base, size_t n, size_t size, compare_fn comp) {
  if (n < 2) return;
  void* buf = calloc(n, size);
  safe_memcpy(buf, base, n, size);
  merge_sort_impl(base, buf, n, size, comp);
  free(buf);
}
void merge(void* _out, const void* _in1, size_t n1, 
                  const void* _in2, size_t n2, size_t size, compare_fn comp) {
  char* out = (char*)_out;
  const char* in1 = (const char*)_in1;
  const char* in2 = (const char*)_in2;
  const char* end1 = in1 + n1 * size; 
  const char* end2 = in2 + n2 * size;
  
  for (; in1 < end1; in1 += size, out += size) {
    for (; in2 < end2 && comp(in2, in1) < 0; in2 += size, out += size) {
      memcpy(out, in2, size);
    }
    memcpy(out, in1, size);
  }
  memcpy(out, in2, end2 - in2);
}
