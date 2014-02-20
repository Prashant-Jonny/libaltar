
/* Copyright (c) 2013, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win.h"

static error_t win_analyze(win_file_t *file) {
  error_t err = 0;

l_error:
  return err;
}

error_t win_open(const char* fname, win_file_t *out) {
  error_t err;
  if (NULL == fname || NULL == out) {
    return ERR_WIN_INVALID_ARGS;
  }
#ifdef _WIN32
  out->mapd = out->map = NULL;
  out->fd = CreateFileA(fname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
  if (INVALID_HANDLE_VALUE == out->fd) {
    err = ERR_WIN_OPEN_FAILED;
    goto l_error;
  }
  out->mapd = CreateFileMappingA(out->fd, NULL, PAGE_READONLY, 0, 0, NULL);
  if (NULL == out->mapd) {
    err = ERR_WIN_MAP_FAILED;
    goto l_error;
  }
  out->map = MapViewOfFile(out->mapd, FILE_MAP_READ, 0, 0, 0);
  if (NULL == out->base) {
    err = ERR_WIN_MAP_FAILED;
    goto l_error;
  }
#else
  out->map = NULL;
  out->fd = open(fname, O_RDONLY);
  if (-1 == out->fd) {
    err = ERR_WIN_OPEN_FAILED;
    goto l_error;
  }
  if (-1 == fstat(out->fd, &out->finfo)) {
    err = ERR_WIN_MAP_FAILED;
    goto l_error;
  }
  out->map = mmap(0, out->finfo.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, out->fd, 0);
  if ((void*)-1 == out->map) {
    err = ERR_WIN_MAP_FAILED;
    goto l_error;
  }
#endif
  if ((err = win_analyze(out))) {
    goto l_error;
  }
  return 0;
l_error:
  win_close(out);
  return err;
}

void win_close(win_file_t* file) {
  if (NULL == file) {
    return;
  }
#ifdef _WIN32
  if (NULL != file->map) {
    UnmapViewOfFile(file->map);
    file->map = NULL;
  }
  if (NULL != file->mapd) {
    CloseHandle(file->mapd);
    file->mapd = NULL;
  }
  if (INVALID_HANDLE_VALUE != file->fd) {
    CloseHandle(file->fd);
    file->fd = INVALID_HANDLE_VALUE;
  }
#else
  if (NULL != file->map) {
    munmap(file->map, file->finfo.st_size);
    memset(&file->finfo, sizeof(file->finfo), 0);
    file->map = NULL;
  }
  if (NULL != file->fd) {
    close(file->fd);
    file->fd = NULL;
  }
#endif
}

