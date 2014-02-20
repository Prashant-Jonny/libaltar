
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

#include "altar/win.h"


static error_t win_analyze(win_file_t *file) {
  section_header_t *hdr, *hdr_end;
  file->base = (section_header_t*)file->map;
  if (SECTION_FORM != file->base->ident) {
    return ERR_WIN_BAD_FILESIG;
  }
  hdr = file->base + 1;
  hdr_end = (section_header_t*)((uintptr_t)file->base + file->base->size);
  while (hdr < hdr_end) {
    switch (hdr->ident) {
      case SECTION_GENERATE:
      file->gen = (section_generate_t*)hdr;
      break;
      case SECTION_OPTIONS:
      file->options = (section_options_t*)hdr;
      break;
      case SECTION_EXTENSIONS:
      file->extensions = (section_extensions_t*)hdr;
      break;
      case SECTION_SOUNDS:
      file->sounds = (section_sounds_t*)hdr;
      break;
      case SECTION_SPRITES:
      file->sprites = (section_sprites_t*)hdr;
      break;
      case SECTION_BACKGROUNDS:
      file->backgrounds = (section_backgrounds_t*)hdr;
      break;
      case SECTION_PATHS:
      file->paths = (section_paths_t*)hdr;
      break;
      case SECTION_SCRIPTS:
      file->scripts = (section_scripts_t*)hdr;
      break;
      case SECTION_SHADERS:
      file->shaders = (section_shaders_t*)hdr;
      break;
      case SECTION_FONTS:
      file->fonts = (section_fonts_t*)hdr;
      break;
      case SECTION_TIMELINES:
      file->timelines = (section_timelines_t*)hdr;
      break;
      case SECTION_OBJECTS:
      file->objects = (section_objects_t*)hdr;
      break;
      case SECTION_ROOMS:
      file->rooms = (section_rooms_t*)hdr;
      break;
      case SECTION_DATAFILES:
      file->datafiles = (section_datafiles_t*)hdr;
      break;
      case SECTION_TEXINFO:
      file->texinfo = (section_texinfo_t*)hdr;
      break;
      case SECTION_CODE:
      file->code = (section_code_t*)hdr;
      break;
      case SECTION_VARIABLES:
      file->variables = (section_variables_t*)hdr;
      break;
      case SECTION_FUNCTIONS:
      file->functions = (section_functions_t*)hdr;
      break;
      case SECTION_STRINGS:
      file->strings = (section_strings_t*)hdr;
      break;
      case SECTION_TEXTURES:
      file->textures = (section_textures_t*)hdr;
      break;
      case SECTION_AUDIO:
      file->audio = (section_audio_t*)hdr;
      break;
      default:
      return ERR_WIN_UNKNOWN_SECTION;
    }
    hdr = (section_header_t*)((uintptr_t)(hdr + 1) + hdr->size);
  }
  return 0;
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

