#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)
#define gen_swap(x, y, T) do { T tmp = *x; *x = *y; *y = tmp; } while (0)

typedef int (*compare_fn)(const void*, const void*);

void* safe_realloc(void* ptr, size_t nmemb, size_t size);

void safe_memcpy(void* dest, const void* src, size_t n, size_t size);

void* ptr_add(void* ptr, size_t n, size_t elsz);

void swap(void* obj1, void* obj2, size_t size, void* slot);
