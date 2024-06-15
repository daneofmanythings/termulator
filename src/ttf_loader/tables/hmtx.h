#ifndef SRC_TTFLOADER_TABLES_HMTX_H
#define SRC_TTFLOADER_TABLES_HMTX_H

#include "font_directory.h"

typedef struct hmtx_table {
  //
} hmtx_table_t;

hmtx_table_t* hmtx_table_create(FILE* font_file, table_directory_t* table_directory);
void hmtx_table_destroy(hmtx_table_t* table);

#endif // !DEBUG
