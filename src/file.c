
/* Copyright (c) 2013, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win.h"

error_t win_analyze(win_file_t *file) {
  error_t err = 0;

l_error:
  return err;
}

error_t win_open(const char* fname, win_file_t *out) {
  error_t err;
#ifdef _WIN32
  out->fd = CreateFileA(fname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
  if (INVALID_HANDLE_VALUE == out->fd) {
    err = ERR_WIN_OPEN_FAILED;
    goto l_error;
  }
  out->mapd = CreateFileMappingA(out->fd, NULL, PAGE_READONLY, 0, 0, NULL);
  if (NULL == out->mapd) {
    err = ERR_WIN_MAP_FAILED;
    goto l_cleanup_fd;
  }
  out->map = MapViewOfFile(out->mapd, FILE_MAP_READ, 0, 0, 0);
  if (NULL == out->base) {
    err = ERR_WIN_MAP_FAILED;
    goto l_cleanup_map;
  }
#else
  out->fd = open(fname, O_RDONLY);
  if (-1 == out->fd) {
    err = ERR_WIN_OPEN_FAILED;
    goto l_error;
  }
  if (-1 == fstat(out->fd, &out->finfo)) {
    err = ERR_WIN_MAP_FAILED;
    goto l_cleanup_fd;
  }
  out->map = mmap(0, out->finfo.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, out->fd, 0);
  if ((void*)-1 == out->map) {
    err = ERR_WIN_MAP_FAILED;
    goto l_cleanup_fd;
  }
#endif
  if ((err = win_analyze(out))) {
    goto l_cleanup_map;
  }
  return 0;
#ifdef _WIN32
l_cleanup_map:
  UnmapViewOfFile(out->map);
  CloseHandle(out->mapd);
l_cleanup_fd:
  CloseHandle(out->fd);
#else
l_cleanup_map:
  munmap(out->map, out->finfo.st_size);
l_cleanup_fd:
  close(out->fd);
#endif
l_error:
  return err;
}

void win_close(win_file_t* in) {
  /* */
}

