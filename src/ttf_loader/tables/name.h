#ifndef SRC_TTFLOADER_TABLES_NAME_H
#define SRC_TTFLOADER_TABLES_NAME_H

#include "../data_types.h"
#include "font_directory.h"

typedef struct name_record {
  uint16_t platform_id;
  uint16_t encoding_id;
  uint16_t language_id;
  uint16_t name_id;
  uint16_t length;
  OFFSET16 string_offset;
} name_record_t;

typedef struct lang_tag_record {
  uint16_t length;
  OFFSET16 lang_tag_offset;
} lang_tag_record_t;

typedef struct name_table_t {
  uint16_t version;
  uint16_t count;
  OFFSET16 storage_offset;
  name_record_t* name_records;
  uint16_t lang_tag_count;
  lang_tag_record_t* lang_tag_records;
  uint8_t* string_data;
} name_table_t;

name_table_t* name_table_create(uint32_t* table_data, table_directory_t* table_directory);

#endif // !DEBUG
