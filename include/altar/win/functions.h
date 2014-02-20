/* Copyright (c) 2013, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_TYPES_H__
#define __ALTAR_WIN_TYPES_H__

#include "altar/win/types.h"

error_t win_open(const char* fname, win_file_t *out);
void win_close(win_file_t* in);

#endif /* __ALTAR_WIN_TYPES_H__ */

