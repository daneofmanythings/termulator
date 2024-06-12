#include "cmap.h"

cmap_table_t* cmap_table_create(uint8_t* table_data, table_directory_t* table_directory) {

  cmap_table_t* table = (cmap_table_t*)malloc(sizeof(cmap_table_t));
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  return table;
}
