#ifndef SRC_TTFLOADER_TABLES_HHEA_H
#define SRC_TTFLOADER_TABLES_HHEA_H

#include "../data_types.h"
#include "font_directory.h"

typedef struct hhea_table {
  uint16_t major_version;
  uint16_t minor_version;
  FWORD ascender;
  FWORD descender;
  FWORD line_gap;
  UFWORD advance_width_max;
  FWORD min_left_side_bearing;
  FWORD min_right_side_bearing;
  FWORD x_max_extent;
  int16_t caret_slope_rise;
  int16_t caret_slope_run;
  int16_t caret_offset;
  int16_t _reserved[4];
  int16_t metric_data_format;
  uint16_t number_of_h_metrics;
} hhea_table_t;

hhea_table_t* hhea_table_create(uint8_t* table_data, table_directory_t* table_directory);

#endif // !DEBUG
