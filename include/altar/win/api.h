
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_API_H__
#define __ALTAR_WIN_API_H__

#include "altar/win/types.h"

error_t win_open(const char* fname, win_file_t *out);
void win_close(win_file_t* file);

error_t win_get_generate_info(win_file_t *in, generate_info_t *out);
error_t win_get_string_info(win_file_t *in, unsigned id, string_info_t *out);
error_t win_get_texture_info(win_file_t *in, unsigned id, texture_info_t *out);

#endif /* __ALTAR_WIN_API_H__ */

