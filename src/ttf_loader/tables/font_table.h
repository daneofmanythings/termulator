#ifndef SRC_TTFLOADER_TABLES_FONTTABLE_H
#define SRC_TTFLOADER_TABLES_FONTTABLE_H

#include "font_directory.h"
#include <math.h>

void* font_table_create(FILE* font_file, table_directory_t* table_directory);

static uint64_t intify_tag(TAG tag) {
  uint64_t intified = 0;

  for (size_t pos = 0; pos < 4; ++pos) {
    intified += tag[pos] * pow(10, 3 * (3 - pos));
  }

  return intified;
}

#endif // !DEBUG
