#ifndef SRC_TTFLOADER_TABLES_FONTTABLE_H
#define SRC_TTFLOADER_TABLES_FONTTABLE_H

#include <endian.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "font_directory.h"

void* font_table_create(FILE* font_file, table_directory_t* table_directory);
void font_table_destroy(TAG tag, void* table);

#endif // !DEBUG
