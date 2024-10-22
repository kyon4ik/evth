#pragma once

#include "volume.h"

#include <stdbool.h>

#define VecIdx(v, idx, T) (*(T*)vec_index(v, idx))

typedef struct {
  volume_t data;
  size_t len; 
} vec_t;

#define Self vec_t*
#define CSelf const vec_t*

void vec_init(Self self, size_t cap, size_t elsz);

void vec_build(Self self, const void* data, size_t n, size_t elsz);

void vec_copy(Self self, CSelf other);

void vec_del(Self self);

// Access functions
void* vec_index(CSelf self, size_t idx);

const void* vec_first(CSelf self);

const void* vec_last(CSelf self);

void* vec_first_mut(CSelf self);

void* vec_last_mut(CSelf self);

// Modify functions 
void vec_push(Self self, const void* val);

bool vec_pop(Self self);

void vec_reserve(Self self, size_t extra);

void vec_shrink_to_fit(Self self);

#undef Self
#undef CSelf
