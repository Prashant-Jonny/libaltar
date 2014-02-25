
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win/util.h"


uint32_t letobe32(uint32_t val) {
  uint8_t *bytes = (uint8_t*)&val;
  return bytes[3] | (bytes[2] << 8) | (bytes[1] << 16) | (bytes[0] << 24);
}

