#include "binheap.h"
#include <assert.h>

void binheap_init(binheap_t* self, size_t cap, compare_fn comp, size_t elsz) {
  vec_init(&self->data, cap, elsz);
  self->comp = comp;
}

static void heapify(binheap_t* self) {
  size_t n = self->data.len;
  for (size_t i = n - 1; i > 0; --i) {
    binheap_sift_down(self, i);
  }  
  if (n > 0) {
    binheap_sift_down(self, 0);
  }
}

void binheap_build(binheap_t* self, const void* data, size_t n, compare_fn comp, size_t elsz) {
  vec_build(&self->data, data, n, elsz);
  self->comp = comp;
  heapify(self);
}

void binheap_del(binheap_t* self) {
  vec_del(&self->data);
}

static void binheap_sift_down_range(binheap_t* self, size_t pos, size_t end) {
  char swap_slot[self->data.data.elsz];
  size_t child = 2 * pos + 1;

  while (child + 2 <= end) {
    void* first = vec_index(&self->data, child);
    void* second = vec_index(&self->data, child + 1);
    child += self->comp(first, second) <= 0;

    void* value = vec_index(&self->data, pos);
    void* child_value = vec_index(&self->data, child);
    if (self->comp(value, child_value) >= 0) {
      return;
    }

    swap(value, child_value, self->data.data.elsz, swap_slot);
    pos = child;
    child = 2 * pos + 1;
  }

  if (child + 1 != end) {
    return;
  }
  
  void* value = vec_index(&self->data, pos);
  void* child_value = vec_index(&self->data, child);
  if (self->comp(value, child_value) < 0) {
    swap(value, child_value, self->data.data.elsz, swap_slot);
  }
}

void binheap_sort(vec_t data, compare_fn comp) {
  binheap_t self = {.data = data, .comp = comp };
  heapify(&self);

  char swap_slot[self.data.data.elsz];
  size_t end = self.data.len;
  while (end > 1) {
    end -= 1;

    void* cur = vec_index(&self.data, end);
    swap(vec_first_mut(&self.data), cur, self.data.data.elsz, swap_slot);

    binheap_sift_down_range(&self, 0, end);
  }
}

const void* binheap_peek(const binheap_t* self) {
  return vec_first(&self->data);
} 

size_t binheap_sift_up(binheap_t* self, size_t start, size_t pos) {
  char swap_slot[self->data.data.elsz];

  while (pos > start) {
    size_t parent = (pos - 1) / 2;

    void* value = vec_index(&self->data, pos); 
    void* parent_value = vec_index(&self->data, parent);
    if (self->comp(value, parent_value) <= 0) {
      break;
    }

    swap(value, parent_value, self->data.data.elsz, swap_slot);
    pos = parent;
  }

  return pos;
}

void binheap_sift_down(binheap_t* self, size_t pos) {
  binheap_sift_down_range(self, pos, self->data.len);
}

void binheap_push(binheap_t* self, const void* val) {
  size_t old_len = self->data.len;
  vec_push(&self->data, val);
  binheap_sift_up(self, 0, old_len);
}

void binheap_pop(binheap_t* self) {
  if (self->data.len == 0) {
    return;
  }

  void* last = vec_last_mut(&self->data);
  safe_memcpy(vec_first_mut(&self->data), last, 1, self->data.data.elsz);
  vec_pop(&self->data);

  if (self->data.len > 1) {
    binheap_sift_down(self, 0);
  }
}
