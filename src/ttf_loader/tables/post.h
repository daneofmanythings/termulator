#ifndef SRC_TTFLOADER_TABLES_POST_H
#define SRC_TTFLOADER_TABLES_POST_H

#include <stdio.h>

#include "font_directory.h"

typedef struct post_header {
  VERSION16DOT16 version;
  FIXED italic_angle;
  FWORD underline_position;
  FWORD underline_thickness;
  uint32_t is_fixed_pitch;
  uint32_t min_mem_type_42;
  uint32_t max_mem_type_42;
  uint32_t min_mem_type_1;
  uint32_t max_mem_type_1;
} post_header_t;

typedef struct post_data {
  uint16_t num_glyphs;
  uint16_t* glyph_name_index;
  uint8_t* string_data;
} post_data_t;

typedef struct post_table {
  post_header_t header;
  post_data_t data;
} post_table_t;

post_table_t* post_table_create(uint32_t* table_data, table_directory_t* table_directory);
void post_table_destroy(post_table_t* table);
char* post_table_get_glyph_at(post_table_t* table, uint16_t glyph_num);

#endif // !DEBUG
