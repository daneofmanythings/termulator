#ifndef SRC_TTFHEADER_TABLES_HEAD_H
#define SRC_TTFHEADER_TABLES_HEAD_H

#include "../data_types.h"
#include "font_directory.h"

typedef struct head_table {
  uint16_t major_version;
  uint16_t minor_version;
  FIXED font_revision;
  uint32_t checksum_adjustment;
  uint32_t magic_number;
  uint16_t flags;
  uint16_t units_per_em;
  LONGDATETIME created;
  LONGDATETIME modified;
  int16_t x_min;
  int16_t y_min;
  int16_t x_max;
  int16_t y_max;
  uint16_t mac_style;
  uint16_t lowest_rec_ppem;
  int16_t font_direction_hint;
  int16_t index_to_loc_format;
  int16_t glyph_data_format;
} head_table_t;
head_table_t* head_table_create(uint32_t* table_data, table_directory_t* table_directory);
void head_table_destroy(head_table_t* table);

#endif // !DEBUG
