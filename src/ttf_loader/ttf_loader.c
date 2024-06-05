#include "../ttf_loader.h"
#include "tables/font_directory.h"

ttf_font_data_t* ttf_font_data_load_from_file(FILE* font_file) {
  ttf_font_data_t* font_data = (ttf_font_data_t*)malloc(sizeof(ttf_font_data_t));
  if (font_data == NULL) {
    fprintf(stderr, "ttf_font_data_load_from_file::malloc\n");
    exit(1);
  }

  font_directory_t* font_directory = font_directory_create(font_file);
  font_data->font_directory = font_directory;

  fclose(font_file);
  return font_data;
}

void ttf_font_data_destroy(ttf_font_data_t* font_data) {
  font_directory_destroy(font_data->font_directory);
  free(font_data);
}
