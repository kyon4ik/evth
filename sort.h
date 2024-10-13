#pragma once

#include "utils.h"

void quick_sort(void* base, size_t n, size_t size, compare_fn comp);

void merge_sort(void* base, size_t n, size_t size, compare_fn comp);

void merge(void* _out, 
          const void* _in1, size_t n1, 
          const void* _in2, size_t n2, 
          size_t size, compare_fn comp);

