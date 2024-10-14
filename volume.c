#include "volume.h"
#include "macro.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

void volume_init(volume_t* self, size_t cap, size_t elsz) {
  self->cap = cap;
  self->elsz = elsz,
  self->elems = calloc(cap, elsz);
}

void volume_del(volume_t* self) {
  free(self->elems);
  self->elems = NULL;
  self->cap = 0; 
}

bool volume_needs_to_grow(volume_t* self, size_t len, size_t extra) {
  return extra > self->cap - len;
}

void volume_grow(volume_t* self, size_t len, size_t extra) {
  assert(extra > 0);

  size_t req_cap = len + extra;
  size_t cap = Max(self->cap * 2, req_cap);

  self->elems = safe_realloc(self->elems, cap, self->elsz);
  self->cap = cap;
}

void volume_reserve(volume_t* self, size_t len, size_t extra) {
  if (volume_needs_to_grow(self, len, extra)) {
    volume_grow(self, len, extra);        
  }
}

void volume_shrink(volume_t* self, size_t new_cap) {
  assert(new_cap <= self->cap);

  if (new_cap == 0) {
    free(self->elems);
    self->elems = NULL;
  } else {
    self->elems = safe_realloc(self->elems, new_cap, self->elsz);
  }
  
  self->cap = new_cap;
}
