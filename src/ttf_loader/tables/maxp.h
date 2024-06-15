#ifndef SRC_TTFLOADER_TABLES_MAXP_H
#define SRC_TTFLOADER_TABLES_MAXP_H

#include "../data_types.h"
#include "font_directory.h"

typedef struct maxp_table {
  VERSION16DOT16 version;
  uint16_t num_glyphs;
  uint16_t max_points;
  uint16_t max_contours;
  uint16_t max_composite_points;
  uint16_t max_composite_contours;
  uint16_t max_zones;
  uint16_t max_twilight_points;
  uint16_t max_storage;
  uint16_t max_function_defs;
  uint16_t max_instuction_defs;
  uint16_t max_stack_elements;
  uint16_t max_size_of_instuctions;
  uint16_t max_component_elements;
  uint16_t max_component_depth;
} maxp_table_t;

maxp_table_t* maxp_table_create(uint32_t* table_data, table_directory_t* table_directory);
void maxp_table_destroy(maxp_table_t* table);

#endif // !DEBUG
