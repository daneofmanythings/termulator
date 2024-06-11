#ifndef SRC_TTFLOADER_TABLES_FONTTABLE_H
#define SRC_TTFLOADER_TABLES_FONTTABLE_H

#include <endian.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "font_directory.h"

void* font_table_create(FILE* font_file, table_directory_t* table_directory);

static uint32_t font_table_calculate_checksum(uint32_t* table, uint32_t length) {
  uint32_t sum = 0L;
  uint32_t* end_ptr = table + ((length + 3) & ~3) / sizeof(uint32_t);
  while (table < end_ptr) {
    sum += be32toh(*table);
    table++;
  }
  return sum;
}

/* NOTE:
This function assumes that the length of any table is a multiple of four bytes,
or that tables are padded with zero to four-byte aligned offsets. Actual table lengths
recorded in the table directory should not include padding, however. To accommodate
data with a length that is not a multiple of four, the below algorithm must be modified
to treat the data as though it contains zero padding to a length that is a multiple of four.
*/
static bool font_table_verify_checksum(const char* name, uint32_t checksum, uint32_t* table,
                                       uint32_t length) {
  uint32_t calculated_checksum = font_table_calculate_checksum(table, length);
  if (checksum != calculated_checksum) {
    fprintf(stderr, "'%s' INVALID CHECKSUM. %u != %u\n", name, checksum, calculated_checksum);
    return false;
  }
  return true;
}

#endif // !DEBUG
