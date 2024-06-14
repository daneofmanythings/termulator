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

// V0 ///////////////////////////////////////////////////
typedef struct cmap_subtable_v0 { // byte encoding table
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint8_t glyph_id_array[256];
} cmap_subtable_v0_t;

// V2 ////////////////////////////////////////////////////
typedef struct v2_sub_header v2_sub_header_t;
typedef struct cmap_subtable_v2 { // high byte mapping through table
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint16_t sub_header_keys[256];
  v2_sub_header_t* sub_headers; // TODO: implement;
  uint16_t* glyph_id_array;
} cmap_subtable_v2_t;

struct v2_sub_header {
  uint16_t first_code;
  uint16_t entry_count;
  int16_t id_delta;
  uint16_t id_range_offset;
};

// V4 //////////////////////////////////////////////////////
typedef struct cmap_subtable_v4 { // segment mapping to delta values
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint16_t seg_count_x2;
  uint16_t search_range;
  uint16_t entry_selector;
  uint16_t range_shift;
  uint16_t* end_code; // length = 2 * largest power of 2 <= (seg_count_x2 / 2)
  uint16_t reserved_pad;
  uint16_t start_code;
  int16_t* id_delta;         // length = log2(largest power of 2 <= (seg_count_x2 / 2))
  uint16_t* id_range_offset; // length = seg_count_x2 - seg_count_end_code
  uint16_t* glyph_id_array;
} cmap_subtable_v4_t;

// V6 /////////////////////////////////////////////////////
typedef struct cmap_subtable_v6 { // trimmed table mapping
  uint16_t format;
  uint16_t length;
  uint16_t language;
  uint16_t first_code;
  uint16_t entry_count;
  uint16_t* glyph_id_array; // length entry_count
} cmap_subtable_v6_t;

// V8 //////////////////////////////////////////////////////
typedef struct v8_sequential_map_group v8_sequential_map_group_t;
typedef struct cmap_subtable_v8 { // mixed 16-bit and 32-bit coverage
  uint16_t format;
  uint16_t reserved;
  uint32_t length;
  uint32_t language;
  uint8_t is_32[8192];
  uint32_t num_groups;
  v8_sequential_map_group_t* groups; // length num_groups
} cmap_subtable_v8_t;

struct v8_sequential_map_group {
  uint32_t start_char_code;
  uint32_t end_char_code;
  uint32_t start_glyph_id;
};

// V10 ///////////////////////////////////////////////////
typedef struct cmap_subtable_v10 { // trimmed array
  uint16_t format;
  uint16_t reserved;
  uint32_t length;
  uint32_t language;
  uint32_t start_char_code;
  uint32_t num_chars;
  uint16_t* glyph_id_array;
} cmap_subtable_v10_t;

// V12 ////////////////////////////////////////////////////
typedef struct v12_sequential_map_group v12_sequential_map_group_t;
typedef struct cmap_subtable_v12 { // segmented coverage
  uint16_t format;
  uint16_t reserved;
  uint32_t length;
  uint32_t language;
  uint32_t num_groups;
  v12_sequential_map_group_t* groups; // length num_groups
} cmap_subtable_v12_t;

struct v12_sequential_map_group {
  uint32_t start_char_code;
  uint32_t end_char_code;
  uint32_t start_glyph_id;
};

// V13 //////////////////////////////////////////////////////
typedef struct v13_constant_map_group v13_constant_map_group_t;
typedef struct cmap_subtable_v13 { // many-to-one range mappings
  uint16_t format;
  uint16_t reserved;
  uint32_t length;
  uint32_t language;
  uint32_t num_groups;
  v13_constant_map_group_t* groups; // length num_groups
} cmap_subtable_v13_t;

struct v13_constant_map_group {
  uint32_t start_char_code;
  uint32_t end_char_code;
  uint32_t glyph_id;
};

// V14 ////////////////////////////////////////////////////////
typedef struct v14_variation_selector v14_variation_selector_t;
typedef struct v14_default_uvs_table v14_default_uvs_table_t;
typedef struct v14_non_default_uvs_table v14_non_default_uvs_table_t;
typedef struct unicode_range unicode_range_t; // default_uvs_table
typedef struct uvs_mapping uvs_mapping_t;     // non_default_uvs_table

typedef struct cmap_subtable_v14 { // unicode variation sequences
  uint16_t format;                 // set to 14
  uint32_t length;
  uint32_t num_var_selector_records;
  v14_variation_selector_t* var_selector; // length num_var_selector_records
  v14_default_uvs_table_t* default_uvs;
  v14_non_default_uvs_table_t* non_default_uvs;
} cmap_subtable_v14_t;

struct v14_variation_selector {
  uint8_t var_selector[3]; // uint24_t
  OFFSET32 default_uvs_offset;
  OFFSET32 non_default_uvs_offset;
};

typedef struct v14_default_uvs_table {
  uint32_t num_unicode_value_ranges;
  unicode_range_t* ranges;
} v14_default_uvs_table_t;

typedef struct v14_non_default_uvs_table {
  uint32_t num_uvs_mappings;
  uvs_mapping_t* uvs_mappings;
} v14_non_default_uvs_table_t;

typedef struct unicode_range {
  uint8_t start_unicode_value[3]; // uint24_t
  uint8_t additional_count;
} unicode_range_t;

typedef struct uvs_mapping {
  uint8_t unicode_value[3]; // uint24_t
  uint16_t glyph_id;
} uvs_mapping_t;

#endif // !DEBUG
