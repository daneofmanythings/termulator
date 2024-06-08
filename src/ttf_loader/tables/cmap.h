#ifndef SRC_TTFHEADER_TABLES_CMAP_H
#define SRC_TTFHEADER_TABLES_CMAP_H

#include "../data_types.h"
#include "font_directory.h"

typedef struct cmap_table {
  //
} cmap_table_t;
cmap_table_t* cmap_table_create(FILE* font_file, table_directory_t* table_directory);

typedef struct encoding_record {
  uint16_t platform_id;
  uint16_t encoding_id;
  OFFSET32 subtable_offset;
} encoding_record_t;

typedef struct cmap_header {
  uint16_t version;
  uint16_t num_tables;
  encoding_record_t encoding_records[];
} cmap_header_t;

#endif // !DEBUG
