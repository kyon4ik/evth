#pragma once

#include "utils.h"

typedef struct {
  // capacity
  size_t cap;
  // element size
  size_t elsz;
  // pointer to elements
  void *elems;
} volume_t;

// initializes volume
void volume_init(volume_t* self, size_t cap, size_t elsz);

// deletes volume
void volume_del(volume_t* self);

void volume_grow(volume_t* self, size_t len, size_t extra);

// reserves enough space to contain extra elements
void volume_reserve(volume_t* self, size_t len, size_t extra);

// shrinks to new_cap, that is less than self->cap
void volume_shrink(volume_t* self, size_t new_cap);
