#ifndef SRC_TTFLOADER_TABLES_FONTTABLE_H
#define SRC_TTFLOADER_TABLES_FONTTABLE_H

#include "font_directory.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void* font_table_create(FILE* font_file, table_directory_t* table_directory);

static uint64_t intify_tag(TAG tag) {
  uint64_t intified = 0;

  for (size_t pos = 0; pos < 4; ++pos) {
    intified += tag[pos] * pow(10, 3 * (3 - pos));
  }

  return intified;
}

static uint32_t font_table_calculate_checksum(uint32_t* table, uint32_t length) {
  uint32_t sum = 0L;
  uint32_t* end_ptr = table + ((length + 3) & ~3) / sizeof(uint32_t);
  while (table < end_ptr) {
    sum += *table;
    table++;
  }
  return sum;
}

static bool font_table_verify_checksum(const char* name, uint32_t checksum, uint32_t* table,
                                       uint32_t length) {
  uint32_t calculated_checksum = font_table_calculate_checksum((uint32_t*)table, length);
  if (checksum != calculated_checksum) {
    fprintf(stderr, "checksum validation for %s failed. %u != %u\n", name, checksum,
            calculated_checksum);
    return false;
  }
  return true;
}

static void font_file_align_pointer_to_table(FILE* font_file, table_directory_t* table_directory) {
  int result = fseek(font_file, table_directory->offset, SEEK_SET);
  if (result != 0) {
    fprintf(stderr, "error seeking in file\n");
  }
}

#endif // !DEBUG
