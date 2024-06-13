#ifndef SRC_TTFHEADER_TABLES_CMAP_H
#define SRC_TTFHEADER_TABLES_CMAP_H

#include "../data_types.h"
#include "font_directory.h"

typedef struct encoding_record {
  uint16_t platform_id;
  uint16_t encoding_id;
  OFFSET32 subtable_offset;
} encoding_record_t;

typedef struct cmap_table {
  uint16_t version;
  uint16_t num_tables;
  encoding_record_t* encoding_records;
  void* subtables;
} cmap_table_t;
cmap_table_t* cmap_table_create(uint32_t* table_data, table_directory_t* table_directory);

// SUBTABLES ////////////////////////////////////////////
typedef struct cmap_subtable_v0 { // byte encoding table
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint8_t glyph_id_array[256];
} cmap_subtable_v0_t;

typedef struct subtable_v2_sub_header {
  uint16_t first_code;
  uint16_t entry_count;
  int16_t id_delta;
  uint16_t id_range_offset;
} subtable_v2_sub_header_t;

typedef struct cmap_subtable_v2 { // high byte mapping through table
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint16_t sub_header_keys[256];
  subtable_v2_sub_header_t* sub_headers; // TODO: implement;
  uint16_t* glyph_id_array;
} cmap_subtable_v2_t;

typedef struct cmap_subtable_v4 { // segment mapping to delta values
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint16_t seg_count_x2;
  uint16_t search_range;
  uint16_t entry_selector;
  uint16_t range_shift;
  uint16_t end_code[seg_count_end_code]; // 2 * largest power of 2 <= (seg_count_x2 / 2)
  uint16_t reserved_pad;
  uint16_t start_code;
  int16_t id_delta[seg_count_id_delta]; // log2(largest power of 2 <= (seg_count_x2 / 2))
  uint16_t id_range_offset[seg_count_id_range_offset]; // seg_count_x2 - seg_count_end_code
  uint16_t* glyph_id_array;
} cmap_subtable_v4_t;

typedef struct cmap_subtable_v6 { // trimmed table mapping
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint16_t first_code;
  uint16_t entry_count;
  uint16_t* glyph_id_array; // length entry_count
} cmap_subtable_v6_t;

typedef struct subtable_v8_sequential_map_group {
  uint32_t start_char_code;
  uint32_t end_char_code;
  uint32_t start_glyph_id;
} subtable_v8_sequential_map_group_t;

typedef struct cmap_subtable_v8 { // mixed 16-bit and 32-bit coverage
  uint16_t format;
  uint16_t reserved;
  uint32_t length;
  uint32_t language;
  uint8_t is_32[8192];
  uint32_t num_groups;
  subtable_v8_sequential_map_group_t* groups; // length num_groups
} cmap_subtable_v8_t;

#endif // !DEBUG
