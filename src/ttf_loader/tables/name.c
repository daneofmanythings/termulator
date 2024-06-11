#include "name.h"
#include "../../lib.h"
#include "font_table.h"
#include <endian.h>
#include <stdint.h>

name_table_t* name_table_create(FILE* font_file, table_directory_t* table_directory) {

  name_table_t* table = (name_table_t*)malloc(table_directory->length);
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  tl_fseek("name", font_file, table_directory->offset);
  tl_fread(&table->version, sizeof(uint16_t), 1,
           font_file); // copy over version, count, and storage offset

  table->version = be16toh(table->version);
  // table->count = be16toh(table->count);
  // table->storage_offset = be16toh(table->storage_offset);

  name_record_t* name_records = (name_record_t*)malloc(sizeof(name_record_t) * table->count);
  if (name_records == NULL) {
    free(table);
    table = NULL;
    return NULL; // TODO: error handling
  }

  tl_fread(name_records, sizeof(name_record_t), table->count, font_file);

  return table;
}
