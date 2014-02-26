
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win/audio.h"


error_t win_get_audio_info(win_file_t *in, unsigned id, audio_info_t *out) {
  const audio_entry_t *aud;
  if (!in) {
    return ERR_WIN_INVALID_ARGS;
  }
  if (id >= in->audio->count) {
    return ERR_WIN_INVALID_ID;
  }
  aud = (audio_entry_t*)win_ptr_from_offset(in, (&in->audio->offsets)[id]);
  out->riff.length = aud->length;
  out->riff.bytes = &aud->data;
  return 0;
}

