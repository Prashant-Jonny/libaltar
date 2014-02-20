
/* Copyright (c) 2013, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_TYPES_H__
#define __ALTAR_WIN_TYPES_H__

#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#elif __unix__
/* todo */
#elif __linux__
/* todo */
#endif

#pragma pack(push, 1)
typedef struct {
  uint32_t ident;
  uint32_t size;
} section_header_t;

typedef struct {
  section_header_t *hdr;
} win_file_header_t;

#pragma pack(pop)

typedef struct {
#ifdef _WIN32
  HANDLE fd, map;
#else
  int fd;
#endif
  win_file_header_t *base;
} win_file_t;

#endif /* __ALTAR_WIN_TYPES_H__ */

