#include "maxp.h"
#include "../../lib.h"
#include "font_table.h"
#include <endian.h>

static void maxp_table_be_to_host(maxp_table_t* table);

maxp_table_t* maxp_table_create(FILE* font_file, table_directory_t* table_directory) {
  maxp_table_t* table = (maxp_table_t*)malloc(table_directory->length);
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  tl_fseek("maxp", font_file, table_directory->offset);
  tl_fread(table, table_directory->length, 1, font_file);
  font_table_verify_checksum("maxp", table_directory->checksum, (uint32_t*)table,
                             table_directory->length);

  maxp_table_be_to_host(table);

  return table;
}

static void maxp_table_be_to_host(maxp_table_t* table) {
  table->version = be32toh(table->version);
  table->num_glyphs = be16toh(table->num_glyphs);

  if (table->version == 0x00005000) { // exiting early for version .5
    return;
  }

  table->max_points = be16toh(table->max_points);
  table->max_contours = be16toh(table->max_contours);
  table->max_composite_points = be16toh(table->max_composite_points);
  table->max_composite_contours = be16toh(table->max_composite_contours);
  table->max_zones = be16toh(table->max_zones);
  table->max_twilight_points = be16toh(table->max_twilight_points);
  table->max_storage = be16toh(table->max_storage);
  table->max_function_defs = be16toh(table->max_function_defs);
  table->max_instuction_defs = be16toh(table->max_instuction_defs);
  table->max_stack_elements = be16toh(table->max_stack_elements);
  table->max_size_of_instuctions = be16toh(table->max_size_of_instuctions);
  table->max_component_elements = be16toh(table->max_component_elements);
}
