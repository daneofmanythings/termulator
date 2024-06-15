#ifndef SRC_TTFLOADER_TABLES_GASP_H
#define SRC_TTFLOADER_TABLES_GASP_H

#include "font_directory.h"

typedef struct gasp_range {
  uint16_t range_max_ppem;
  uint16_t range_gasp_behavior;
} gasp_range_t;

typedef struct gasp_table {
  uint16_t version;
  uint16_t num_ranges;
  gasp_range_t gasp_ranges[];
} gasp_table_t;

gasp_table_t* gasp_table_create(uint32_t* table_data, table_directory_t* table_directory);
void gasp_table_destroy(gasp_table_t* table);

#endif // !DEBUG
