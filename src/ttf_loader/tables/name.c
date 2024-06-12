#include <endian.h>
#include <stdint.h>

#include "name.h"

name_table_t* name_table_create(uint8_t* table_data, table_directory_t* table_directory) {

  name_table_t* table = (name_table_t*)malloc(sizeof(name_table_t));
  if (table == NULL) {
    return NULL; // TODO: error handling
  }
  table->count = 10;

  name_record_t* name_records = (name_record_t*)malloc(sizeof(name_record_t) * table->count);
  if (name_records == NULL) {
    free(table);
    table = NULL;
    return NULL; // TODO: error handling
  }
  free(name_records);
  name_records = NULL;

  return table;
}
