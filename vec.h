#pragma once

#include "volume.h"

#include <stdbool.h>

typedef struct {
  volume_t data;
  size_t len; 
} vec_t;

void vec_init(vec_t* self, size_t cap, size_t elsz);

void vec_del(vec_t* self);

// Access functions
void* vec_index(vec_t* self, size_t idx);

const void* vec_first(const vec_t* self);

const void* vec_last(const vec_t* self);

void* vec_first_mut(vec_t* self);

void* vec_last_mut(vec_t* self);

// Modify functions 
void vec_push(vec_t* self, const void* val);

bool vec_pop(vec_t* self);

void vec_reserve(vec_t* self, size_t extra);

void vec_shrink_to_fit(vec_t* self);
