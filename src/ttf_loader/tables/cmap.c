#include "cmap.h"
#include "font_directory.h"

cmap_table_t* cmap_table_create(FILE* font_file, table_directory_t* table_directory) {
  cmap_table_t* table = (cmap_table_t*)malloc(table_directory->length);
  if (table == NULL) {
    return NULL; // TODO: error handling
  }
  return table;
}
