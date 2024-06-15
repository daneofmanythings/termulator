#include "../ttf_loader.h"
#include "tables/font_directory.h"

ttf_font_data_t* ttf_font_data_load_from_file(FILE* font_file) {
  font_directory_t* font_directory = font_directory_create(font_file);
  uint16_t num_tables = font_directory->offset_subtable.num_tables;

  ttf_font_data_t* font_data =
      (ttf_font_data_t*)malloc(sizeof(ttf_font_data_t) + sizeof(void*) * num_tables);
  if (font_data == NULL) {
    fprintf(stderr, "ttf_font_data_load_from_file::malloc\n");
    exit(1);
  }

  for (size_t table_index = 0; table_index < num_tables; ++table_index) {
    // TODO: implement a system for delaying certain tables under certain conditions
    // in order to use data from other tables in the initialization of specific tables
    font_data->tables[table_index] =
        (void*)font_table_create(font_file, font_directory->table_directories[table_index]);
  }

  font_data->font_directory = font_directory;
  // font_directory_print(font_data->font_directory);

  fclose(font_file);
  return font_data;
}

void ttf_font_data_destroy(ttf_font_data_t* font_data) {
  size_t num_tables = font_data->font_directory->offset_subtable.num_tables;
  if (font_data->tables == NULL) {
    num_tables = 0;
  }
  for (size_t i = 0; i < num_tables; ++i) {
    if (font_data->tables[i] == NULL) {
      continue;
    }
    font_table_destroy(font_data->font_directory->table_directories[i]->tag, font_data->tables[i]);
    font_data->tables[i] = NULL;
  }

  font_directory_destroy(font_data->font_directory);
  free(font_data);
}
