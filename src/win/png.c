
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win/png.h"


static uintptr_t win_png_length(const png_header_t *png) {
  const png_chunk_t *chunk;
  if (!png) {
    return 0;
  }
  chunk = &png->idhr.header;
  while (PNG_CHUNK_END != chunk->type) {
    if (0 == chunk->length) {
      return 0;
    }
    chunk = (png_chunk_t*)((uintptr_t)chunk + chunk->length);
  }
  return (uintptr_t)++chunk - (uintptr_t)png;
}

error_t win_png_from_offset(win_file_t *in, uintptr_t offset, png_info_t *out) {
  const png_header_t *png;
  if (!in) {
    return ERR_WIN_INVALID_ARGS;
  }
  png = (png_header_t*)win_ptr_from_offset(in, offset);
  out->width = letobe32(png->idhr.width);
  out->height = letobe32(png->idhr.height);
  out->data.bytes = (uint8_t*)png;
  out->data.length = win_png_length(png);
  return 0;
}

