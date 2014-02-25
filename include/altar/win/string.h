
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_STRING_H__
#define __ALTAR_WIN_STRING_H__

#include "altar/win.h"


error_t win_string_from_offset(win_file_t *in, uintptr_t offset, string_info_t *out);
error_t win_get_string_info(win_file_t *in, unsigned id, string_info_t *out);

#endif /* __ALTAR_WIN_STRING_H__ */

