#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gasp.h"

void gasp_table_be_to_host(gasp_table_t* table);
void gasp_range_be_to_host(gasp_range_t* table);

gasp_table_t* gasp_table_create(uint32_t* table_data, table_directory_t* table_directory) {
  gasp_table_t* table = (gasp_table_t*)malloc(sizeof(gasp_table_t));
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  memcpy(table, table_data, table_directory->length);

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

void gasp_table_destroy(gasp_table_t* table) {
  if (table == NULL) {
    return;
  }
  free(table);
  table = NULL;
}
