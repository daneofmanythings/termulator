#ifndef SRC_TTFLOADER_TABLES_FONTDIRECTORY_H
#define SRC_TTFLOADER_TABLES_FONTDIRECTORY_H

#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_types.h"

typedef struct offset_subtable {
  uint32_t scalar_type;
  uint16_t num_tables;
  uint16_t search_range;
  uint16_t entry_selector;
  uint16_t range_shift;
} offset_subtable_t;

void offset_subtable_print(offset_subtable_t* offset_subtable);

typedef struct table_directory {
  TAG tag;
  uint32_t checksum;
  uint32_t offset;
  uint32_t length;
} table_directory_t;

void table_directory_print(table_directory_t* table_directory);

typedef struct font_directory {
  offset_subtable_t offset_subtable;
  table_directory_t* table_directories[];
} font_directory_t;

font_directory_t* font_directory_create(FILE* font_ptr);
void font_directory_print(font_directory_t* font_directory);

#endif // !DEBUG
