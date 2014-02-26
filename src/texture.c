
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win/texture.h"


error_t win_get_texture_info(win_file_t *in, unsigned id, texture_info_t *out) {
  const tex_entry_t *tex;
  if (!in) {
    return ERR_WIN_INVALID_ARGS;
  }
  if (id >= in->textures->count) {
    return ERR_WIN_INVALID_ID;
  }
  tex = (tex_entry_t*)win_ptr_from_offset(in, (&in->textures->offsets)[id]);
  return win_png_from_offset(in, tex->offset, &out->png);
}

