
/* Copyright (c) 2014, Acolyte Strike Force. All rights reserved. See LICENSE. */

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
#define ERR_WIN_BAD_FILESIG       4
#define ERR_WIN_UNKNOWN_SECTION   5
#define ERR_WIN_INVALID_ID        6

#define SECTION_FORM              0x4D524F46
#define SECTION_GENERATE          0x384E4547
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

/* Packed structures: structures which map internally to the file format */

#pragma pack(push, 1)
typedef struct {
  uint32_t ident;
  uint32_t size;
} section_header_t;

typedef struct {
  section_header_t header;
  unsigned debug : 1;
  uint32_t debug_mask : 31;
  uint32_t filename_offset;
  uint32_t config_offset;
  uint32_t last_obj;
  uint32_t last_tile;
  uint32_t game_id;
  uint32_t padding[4];
  uint32_t name_offset;
  uint32_t major;
  uint32_t minor;
  uint32_t release;
  uint32_t build;
  uint32_t largest_vpw;
  uint32_t largest_vph;
  uint32_t fullscreen : 1;
  uint32_t sync_vertex_1 : 1;
  uint32_t sync_vertex_2 : 1;
  uint32_t interpolate : 1;
  uint32_t unknown : 1;
  uint32_t show_cursor : 1;
  uint32_t sizeable : 1;
  uint32_t screen_key : 1;
  uint32_t sync_vertex_3 : 1;
  uint32_t studio_version : 3;
  uint32_t steam_enabled : 1;
  uint32_t localdata_enabled : 1;
} section_generate_t;

typedef struct {
  section_header_t header;
  uint32_t fullscreen;
  uint32_t interpolate;
} section_options_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_extensions_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_sounds_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_sprites_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_backgrounds_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_paths_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_scripts_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_shaders_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_fonts_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_timelines_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_objects_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_rooms_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_datafiles_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_texinfo_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_code_t;

typedef struct {
  uint32_t offset;
  uint32_t patchinfo;
  uint32_t inst;
} var_entry_t;

typedef struct {
  section_header_t header;
  var_entry_t vars;
} section_variables_t;

typedef struct {
  section_header_t header;
  uint32_t unk;
} section_functions_t;

typedef struct {
  section_header_t header;
  uint32_t count;
  uint32_t offsets;
} section_strings_t;

typedef struct {
  uint32_t length;
  uint8_t data;
} string_entry_t;

typedef struct {
  section_header_t header;
  uint32_t count;
  uint32_t offsets;
} section_textures_t;

typedef struct {
  uint32_t unk;
  uint32_t offset;
} tex_entry_t;

typedef struct {
  section_header_t header;
  uint32_t count;
  uint32_t offsets;
} section_audio_t;

typedef struct {
  uint32_t length;
} audio_entry_t;
#pragma pack(pop)

/* Unpacked structures: structures which are exposed via the API */

typedef struct {
#ifdef _WIN32
  HANDLE fd, mapd;
  LPVOID map;
#else
  int fd;
  struct stat finfo;
  void *map;
#endif
  section_header_t *base;
  section_generate_t *gen;
  section_options_t *options;
  section_extensions_t *extensions;
  section_sounds_t *sounds;
  section_sprites_t *sprites;
  section_backgrounds_t *backgrounds;
  section_paths_t *paths;
  section_scripts_t *scripts;
  section_shaders_t *shaders;
  section_fonts_t *fonts;
  section_timelines_t *timelines;
  section_objects_t *objects;
  section_rooms_t *rooms;
  section_datafiles_t *datafiles;
  section_texinfo_t *texinfo;
  section_code_t *code;
  section_variables_t *variables;
  section_functions_t *functions;
  section_strings_t *strings;
  section_textures_t *textures;
  section_audio_t *audio;
} win_file_t;

typedef struct {
  unsigned length;
  const char *bytes;
} string_info_t;

typedef struct {
  unsigned length;
  const uint8_t *bytes;
} data_info_t;

typedef struct {
  unsigned width;
  unsigned height;
  data_info_t data;
} png_info_t;

typedef struct {
  png_info_t png;
} texture_info_t;

#endif /* __ALTAR_WIN_TYPES_H__ */

