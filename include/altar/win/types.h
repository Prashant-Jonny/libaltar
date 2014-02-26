
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
  uint32_t info_mask : 18;
  uint32_t license_key_crc32;
  uint32_t license_md5_offset;
  uint64_t timestamp;
  uint32_t display_offset;
  uint64_t active_targets;
} section_general_t;

typedef struct {
  section_header_t header;
  uint32_t fullscreen;
  uint32_t interpolate;
  uint32_t use_new_audio;
  uint32_t borderless;
  uint32_t show_cursor;
  uint32_t scale;
  uint32_t sizeable;
  uint32_t stay_on_top;
  uint32_t window_color;
  uint32_t change_resolution;
  uint32_t color_depth;
  uint32_t resolution;
  uint32_t frequency;
  uint32_t buttonless;
  uint32_t sync_vertex;
  uint32_t fullscreen_key;
  uint32_t help_key;
  uint32_t quit_key;
  uint32_t save_key;
  uint32_t screenshot_key;
  uint32_t close_secondary;
  uint32_t process_priority;
  uint32_t freeze_lose_focus;
  uint32_t show_load_progress;
  uint32_t mbe_splash_bg_offset;
  uint32_t mbe_splash_fg_offset;
  uint32_t mbe_splash_ld_offset;
  uint32_t load_transparency;
  uint32_t load_alpha;
  uint32_t scale_load_progress;
  uint32_t display_errors;
  uint32_t write_errors;
  uint32_t abort_errors;
  uint32_t treat_uninit_zero;
  uint32_t creation_event_order;
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
  uint8_t data;
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
  section_general_t *gen;
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

typedef struct {
  data_info_t riff;
} audio_info_t;

#endif /* __ALTAR_WIN_TYPES_H__ */

