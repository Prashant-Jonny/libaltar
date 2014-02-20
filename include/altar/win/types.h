
/* Copyright (c) 2013, Acolyte Strike Force. All rights reserved. See LICENSE. */

#ifndef __ALTAR_WIN_TYPES_H__
#define __ALTAR_WIN_TYPES_H__

#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#endif

typedef unsigned error_t;

#define ERR_WIN_INVALID_ARGS      1
#define ERR_WIN_OPEN_FAILED       2
#define ERR_WIN_MAP_FAILED        3

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
  HANDLE fd, mapd;
  LPVOID map;
#else
  int fd;
  struct stat finfo;
  void *map;
#endif
  win_file_header_t *base;
} win_file_t;

#endif /* __ALTAR_WIN_TYPES_H__ */

