
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_METHODS_H__
#define __ALTAR_WIN_METHODS_H__

#include "altar/win/types.h"

error_t win_open(const char* fname, win_file_t *out);
void win_close(win_file_t* file);

#endif /* __ALTAR_WIN_METHODS_H__ */

