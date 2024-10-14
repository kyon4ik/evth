#pragma once

#include <stddef.h>

typedef int (*compare_fn)(const void*, const void*);

void* safe_realloc(void* ptr, size_t nmemb, size_t size);

void safe_memcpy(void* dest, const void* src, size_t n, size_t size);

void* ptr_add(void* ptr, size_t n, size_t elsz);

void swap(void* obj1, void* obj2, size_t size, void* slot);
