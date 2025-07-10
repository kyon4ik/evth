#pragma once

#include "volume.h"

typedef struct {
  size_t head;
  size_t len;
  volume_t data;
} ring_t; 

void ring_init(ring_t* self, size_t cap, size_t elsz);

void ring_del(ring_t* self);
