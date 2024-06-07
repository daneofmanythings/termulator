#include "gasp.h"
#include "../../lib.h"
#include "font_table.h"
#include <endian.h>
#include <stdint.h>
#include <stdio.h>

void gasp_table_correct_endianness(gasp_table_t* table);
void gasp_range_correct_endianness(gasp_range_t* table);

gasp_table_t* gasp_table_create(FILE* font_file, table_directory_t* table_directory) {
  gasp_table_t header;
  tl_fseek("gasp_table_create::reading header", font_file, table_directory->offset);
  tl_fread(&header, sizeof(uint16_t), 2, font_file);
  uint16_t num_range_tables = header.num_ranges;

  // size_t table_size = sizeof(gasp_table_t) + sizeof(gasp_range_t) * num_range_tables;
  size_t table_size = 16;
  gasp_table_t* table = (gasp_table_t*)malloc(table_size);
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  tl_fseek("gasp_table_create", font_file, table_directory->offset);
  tl_fread(table, table_size, 1, font_file);

  gasp_table_correct_endianness(table);
  printf("gasp version=%d\ngasp num_ranges=%d\n", table->version, table->num_ranges);

  font_table_verify_checksum("gasp", table_directory->checksum, (uint32_t*)table, table_size);

  return table;
}

void gasp_table_correct_endianness(gasp_table_t* table) {
  // table->version = be16toh(table->version);
  // table->num_ranges = be16toh(table->num_ranges);
  *(uint32_t*)table = be32toh(*(uint32_t*)table);
  for (size_t range_idx = 0; range_idx < table->num_ranges; range_idx++) {
    gasp_range_correct_endianness(&table->gasp_ranges[range_idx]);
  }
}

void gasp_range_correct_endianness(gasp_range_t* table) {
  *(uint32_t*)table = be32toh(*(uint32_t*)table);
  // table->range_max_ppem = be16toh(table->range_max_ppem);
  // table->range_gasp_behavior = be16toh(table->range_gasp_behavior);
}
