
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_PNG_H__
#define __ALTAR_WIN_PNG_H__

#include "altar/win/types.h"

#define PNG_CHUNK_END             0x444E4549

#pragma pack(push, 1)
typedef struct {
  uint32_t length;
  uint32_t type;
} png_chunk_t;

typedef struct {
  png_chunk_t header;
  uint32_t width;
  uint32_t height;
} png_idhr_t;

typedef struct {
  uint32_t padding[2];
  png_idhr_t idhr;
} png_header_t;
#pragma pack(pop)

error_t win_png_from_offset(win_file_t *in, uintptr_t offset, png_info_t *out);

#endif /* __ALTAR_WIN_PNG_H__ */

