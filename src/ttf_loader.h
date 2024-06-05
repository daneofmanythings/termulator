#ifndef SRC_TTFLOADER_H
#define SRC_TTFLOADER_H

#include <stdio.h>

#include "./ttf_loader/tables/font_directory.h"
#include "./ttf_loader/tables/font_table.h"

typedef struct ttf_font_data {
  font_directory_t* font_directory;
  void* tables[];
} ttf_font_data_t;

ttf_font_data_t* ttf_font_data_load_from_file(FILE* font_file);
void ttf_font_data_destroy(ttf_font_data_t* font_data);

#endif // !DEBUG
