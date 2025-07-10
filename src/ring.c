#include "ring.h"

void ring_init(ring_t* self, size_t cap, size_t elsz) {
  volume_init(&self->data, cap, elsz);
  self->head = 0;
  self->len = 0;
}

void ring_del(ring_t* self) {
  volume_del(&self->data);
  self->len = 0;
}
