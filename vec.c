#include "vec.h"

void vec_init(vec_t* self, size_t cap, size_t elsz) {
  volume_init(&self->data, cap, elsz);
  self->len = 0;
}

void vec_del(vec_t* self) {
  volume_del(&self->data);
}

void vec_push(vec_t* self, const void* val) {
  if (self->len == self->data.cap) {
    volume_grow(&self->data, self->len, 1);
  }

  void* end = ptr_add(self->data.elems, self->len, self->data.elsz);
  safe_memcpy(end, val, 1, self->data.elsz);
  self->len += 1;
}

void* vec_index(vec_t* self, size_t idx) {
  assert(idx < self->len);
  return ptr_add(self->data.elems, idx, self->data.elsz);
}

const void* vec_first(const vec_t* self) {
  assert(self->len > 0);
  return self->data.elems;
}

const void* vec_last(const vec_t* self) {
  assert(self->len > 0);
  return ptr_add(self->data.elems, self->len - 1, self->data.elsz);
}

void* vec_first_mut(vec_t* self) {
  assert(self->len > 0);
  return self->data.elems;
}

void* vec_last_mut(vec_t* self) {
  assert(self->len > 0);
  return ptr_add(self->data.elems, self->len - 1, self->data.elsz);
}

bool vec_pop(vec_t* self) {
  if (self->len == 0) {
    return false;
  } else {
    self->len -= 1;
    return true;
  }
}

void vec_reserve(vec_t* self, size_t extra) {
  volume_reserve(&self->data, self->len, extra);
}

void vec_shrink_to_fit(vec_t* self) {
  if (self->data.cap > self->len) {
    volume_shrink(&self->data, self->len);
  }
}
