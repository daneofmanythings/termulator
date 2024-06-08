#include <assert.h>
#include <endian.h>
#include <stdlib.h>

#include "../../lib.h"
#include "font_table.h"
#include "hhea.h"

static void hhea_table_be_to_host(hhea_table_t* table);

hhea_table_t* hhea_table_create(FILE* font_file, table_directory_t* table_directory) {
  hhea_table_t* table = (hhea_table_t*)malloc(table_directory->length);
  if (table == NULL) {
    // TODO: error handling
    return NULL;
  }

  tl_fseek("hhea", font_file, table_directory->offset);
  tl_fread(table, table_directory->length, 1, font_file);
  font_table_verify_checksum("hhea", table_directory->checksum, (uint32_t*)table,
                             table_directory->length);

  hhea_table_be_to_host(table);

  // these are constants. https://learn.microsoft.com/en-us/typography/opentype/spec/hhea
  assert(table->major_version == 1);
  assert(table->minor_version == 0);
  for (size_t i = 0; i < 4; ++i) {
    assert(table->_reserved[i] == 0);
  }
  assert(table->metric_data_format == 0);

  return table;
}

static void hhea_table_be_to_host(hhea_table_t* table) {
  table->major_version = be16toh(table->major_version);
  table->minor_version = be16toh(table->minor_version);
  table->ascender = be16toh(table->ascender);
  table->descender = be16toh(table->descender);
  table->line_gap = be16toh(table->line_gap);
  table->advance_width_max = be16toh(table->advance_width_max);
  table->min_left_side_bearing = be16toh(table->min_left_side_bearing);
  table->min_right_side_bearing = be16toh(table->min_right_side_bearing);
  table->x_max_extent = be16toh(table->x_max_extent);
  table->caret_slope_rise = be16toh(table->caret_slope_rise);
  table->caret_slope_run = be16toh(table->caret_slope_run);
  table->caret_offset = be16toh(table->caret_offset);
  table->_reserved[0] = be16toh(table->_reserved[0]);
  table->_reserved[1] = be16toh(table->_reserved[1]);
  table->_reserved[2] = be16toh(table->_reserved[2]);
  table->_reserved[3] = be16toh(table->_reserved[3]);
  table->metric_data_format = be16toh(table->metric_data_format);
  table->number_of_h_metrics = be16toh(table->number_of_h_metrics);
}
