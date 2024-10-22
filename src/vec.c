#include "vec.h"
#include <assert.h>

#define Self vec_t*
#define CSelf const vec_t*

void vec_init(Self self, size_t cap, size_t elsz) {
  volume_init(&self->data, cap, elsz);
  self->len = 0;
}

void vec_build(Self self, const void* data, size_t n, size_t elsz) {
  volume_init(&self->data, n, elsz);
  safe_memcpy(self->data.elems, data, n, elsz);
  self->len = n;
}

void vec_copy(Self self, CSelf other) {
  vec_build(self, other->data.elems, other->len, other->data.elsz);
}

void vec_del(Self self) {
  volume_del(&self->data);
}

void vec_push(Self self, const void* val) {
  if (self->len == self->data.cap) {
    volume_grow(&self->data, self->len, 1);
  }

  void* end = ptr_add(self->data.elems, self->len, self->data.elsz);
  safe_memcpy(end, val, 1, self->data.elsz);
  self->len += 1;
}

void* vec_index(CSelf self, size_t idx) {
  assert(idx < self->len);
  return ptr_add(self->data.elems, idx, self->data.elsz);
}

const void* vec_first(CSelf self) {
  assert(self->len > 0);
  return self->data.elems;
}

const void* vec_last(CSelf self) {
  assert(self->len > 0);
  return ptr_add(self->data.elems, self->len - 1, self->data.elsz);
}

void* vec_first_mut(CSelf self) {
  assert(self->len > 0);
  return self->data.elems;
}

void* vec_last_mut(CSelf self) {
  assert(self->len > 0);
  return ptr_add(self->data.elems, self->len - 1, self->data.elsz);
}

bool vec_pop(Self self) {
  bool res = self->len != 0;
  self->len -= res;
  return res;
}

void vec_reserve(Self self, size_t extra) {
  volume_reserve(&self->data, self->len, extra);
}

void vec_shrink_to_fit(Self self) {
  if (self->data.cap > self->len) {
    volume_shrink(&self->data, self->len);
  }
}
