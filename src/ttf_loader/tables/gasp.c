#include <endian.h>
#include <stdint.h>
#include <stdio.h>

#include "../../lib.h"
#include "font_table.h"
#include "gasp.h"

void gasp_table_be_to_host(gasp_table_t* table);
void gasp_range_be_to_host(gasp_range_t* table);

gasp_table_t* gasp_table_create(FILE* font_file, table_directory_t* table_directory) {
  gasp_table_t* table = (gasp_table_t*)malloc(table_directory->length);
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  tl_fseek("gasp_table_create", font_file, table_directory->offset);
  tl_fread(table, table_directory->length, 1, font_file);

  gasp_table_be_to_host(table);

  return table;
}

void gasp_table_be_to_host(gasp_table_t* table) {
  table->version = be16toh(table->version);
  table->num_ranges = be16toh(table->num_ranges);
  for (size_t range_idx = 0; range_idx < table->num_ranges; range_idx++) {
    gasp_range_be_to_host(&table->gasp_ranges[range_idx]);
  }
}

void gasp_range_be_to_host(gasp_range_t* table) {
  table->range_max_ppem = be16toh(table->range_max_ppem);
  table->range_gasp_behavior = be16toh(table->range_gasp_behavior);
}
