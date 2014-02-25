
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_FILE_H__
#define __ALTAR_WIN_FILE_H__

#include "altar/win/types.h"


#define SECTION_FORM              0x4D524F46
#define SECTION_GENERAL           0x384E4547
#define SECTION_OPTIONS           0x4E54504F
#define SECTION_EXTENSIONS        0x4E545845
#define SECTION_SOUNDS            0x444E4F53
#define SECTION_SPRITES           0x54525053
#define SECTION_BACKGROUNDS       0x444E4742
#define SECTION_PATHS             0x48544150
#define SECTION_SCRIPTS           0x54504353
#define SECTION_SHADERS           0x52444853
#define SECTION_FONTS             0x544E4F46
#define SECTION_TIMELINES         0x4E4C4D54
#define SECTION_OBJECTS           0x544A424F
#define SECTION_ROOMS             0x4D4F4F52
#define SECTION_DATAFILES         0x4C464144
#define SECTION_TEXINFO           0x47415054
#define SECTION_CODE              0x45444F43
#define SECTION_VARIABLES         0x49524156
#define SECTION_FUNCTIONS         0x434E5546
#define SECTION_STRINGS           0x47525453
#define SECTION_TEXTURES          0x52545854
#define SECTION_AUDIO             0x4F445541

error_t win_open(const char* fname, win_file_t *out);
void win_close(win_file_t* file);

void *win_ptr_from_offset(win_file_t *in, uintptr_t offset);

#endif /* __ALTAR_WIN_FILE_H__ */

