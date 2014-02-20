
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win.h"


static void *win_ptr_from_offset(win_file_t *in, uintptr_t offset) {
  return (void*)((uintptr_t)in->base + offset);
}

static void win_string_from_offset(win_file_t *in, uintptr_t offset, string_info_t *out) {
  const string_entry_t *str;
  if (!offset) {
    out->length = 0;
    out->bytes = "";
  }
  str = (string_entry_t*)win_ptr_from_offset(in, offset);
  out->length = str->length;
  out->bytes = (char*)&str->data;
}

static void win_png_from_offset(win_file_t *in, uintptr_t offset, unsigned len, data_info_t *out) {
  static uint8_t null = 0;
  if (!offset) {
    out->length = 0;
    out->bytes = &null;
  }
  out->length = len;
  out->bytes = (uint8_t*)win_ptr_from_offset(in, offset); /** todo **/
}

error_t win_get_generate_info(win_file_t *in, generate_info_t *out) {
  if (NULL == in) {
    return ERR_WIN_INVALID_ARGS;
  }
  out->debug = in->gen->debug;
  win_string_from_offset(in, in->gen->name_offset, &out->name);
  win_string_from_offset(in, in->gen->filename_offset, &out->filename);
  win_string_from_offset(in, in->gen->config_offset, &out->configuration);
  out->last_obj = in->gen->last_obj;
  out->last_tile = in->gen->last_tile;
  out->game_id = in->gen->game_id;
  out->major = in->gen->major;
  out->minor = in->gen->minor;
  out->release = in->gen->release;
  out->build = in->gen->build;
  out->interpolate = in->gen->interpolate;
  out->show_cursor = in->gen->show_cursor;
  out->sizeable = in->gen->sizeable;
  out->screen_key = in->gen->screen_key;
  out->studio_version = in->gen->studio_version;
  out->steam_enabled = in->gen->steam_enabled;
  out->localdata_enabled = in->gen->localdata_enabled;
  return 0;
}

error_t win_get_string_info(win_file_t *in, unsigned id, string_info_t *out) {
  if (NULL == in) {
    return ERR_WIN_INVALID_ARGS;
  }
  if (id > in->strings->count) {
    return ERR_WIN_INVALID_ID;
  }
  win_string_from_offset(in, (&in->strings->offsets)[id], out);
  return 0;
}

error_t win_get_texture_info(win_file_t *in, unsigned id, texture_info_t *out) {
  const tex_entry_t *tex;
  const tex_entry_png_t *png;
  if (NULL == in) {
    return ERR_WIN_INVALID_ARGS;
  }
  if (id > in->textures->count) {
    return ERR_WIN_INVALID_ID;
  }
  tex = (tex_entry_t*)win_ptr_from_offset((&in->textures->offsets)[id]);
  png = (tex_entry_png_t*)win_ptr_from_offset(t_tex->offset);
  out->width = letobe32(png->width);
  out->height = letobe32(png->height);
  /* ... */
  return 0;
}

