
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win.h"
#include "altar/win/png.h"


static error_t win_string_from_offset(win_file_t *in, uintptr_t offset, string_info_t *out) {
  const string_entry_t *str;
  if (!in) {
    return ERR_WIN_INVALID_ARGS;
  }
  str = (string_entry_t*)win_ptr_from_offset(in, offset);
  out->length = str->length;
  out->bytes = (char*)&str->data;
  return 0;
}

error_t win_get_string_info(win_file_t *in, unsigned id, string_info_t *out) {
  if (NULL == in) {
    return ERR_WIN_INVALID_ARGS;
  }
  if (id > in->strings->count) {
    return ERR_WIN_INVALID_ID;
  }
  return win_string_from_offset(in, (&in->strings->offsets)[id], out);
}

error_t win_get_texture_info(win_file_t *in, unsigned id, texture_info_t *out) {
  const tex_entry_t *tex;
  if (NULL == in) {
    return ERR_WIN_INVALID_ARGS;
  }
  if (id > in->textures->count) {
    return ERR_WIN_INVALID_ID;
  }
  tex = (tex_entry_t*)win_ptr_from_offset(in, (&in->textures->offsets)[id]);
  return win_png_from_offset(in, tex->offset, &out->png);
}

