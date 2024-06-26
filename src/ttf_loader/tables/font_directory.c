#include "font_directory.h"
#include "../../lib.h"
#include "../data_types.h"
#include <endian.h>

static void offset_subtable_be_to_host(offset_subtable_t* offset_subtable) {
  offset_subtable->scalar_type = be32toh(offset_subtable->scalar_type);
  offset_subtable->num_tables = be16toh(offset_subtable->num_tables);
  offset_subtable->search_range = be16toh(offset_subtable->search_range);
  offset_subtable->entry_selector = be16toh(offset_subtable->entry_selector);
  offset_subtable->range_shift = be16toh(offset_subtable->range_shift);
}

void offset_subtable_print(offset_subtable_t* offset_subtable) {
  printf("offset_subtable: \n");
  printf("---\n");
  printf("scalar type: 0x%08X\n", offset_subtable->scalar_type);
  printf("num tables: %d\n", offset_subtable->num_tables);
  printf("search range: %d\n", offset_subtable->search_range);
  printf("entry selector: %d\n", offset_subtable->entry_selector);
  printf("range shift: %d\n", offset_subtable->range_shift);
  printf("---\n");
}

static void table_directory_be_to_host(table_directory_t* table_directory) {
  table_directory->tag = be32toh(table_directory->tag);
  table_directory->checksum = be32toh(table_directory->checksum);
  table_directory->offset = be32toh(table_directory->offset);
  table_directory->length = be32toh(table_directory->length);
}

void table_directory_print(table_directory_t* table_directory) {
  uint8_t tag_string[5];
  tag_stringify(table_directory->tag, tag_string);
  printf("[%s] ", tag_string);
  printf("offset: %d ", table_directory->offset);
  printf("length: %d ", table_directory->length);
  printf("checksum: %d\n", table_directory->checksum);
}

font_directory_t* font_directory_create(FILE* font_file) {
  offset_subtable_t offset_subtable;
  tl_fread(&offset_subtable, sizeof(offset_subtable), 1, font_file);
  offset_subtable_be_to_host(&offset_subtable);

  font_directory_t* font_directory = (font_directory_t*)malloc(
      sizeof(font_directory_t) + offset_subtable.num_tables * sizeof(table_directory_t*));
  if (font_directory == NULL) {
    return NULL;
  }

  memcpy(&font_directory->offset_subtable, &offset_subtable, sizeof(offset_subtable_t));

  for (size_t i = 0; i < font_directory->offset_subtable.num_tables; ++i) {
    font_directory->table_directories[i] = (table_directory_t*)malloc(sizeof(table_directory_t));
    if (font_directory->table_directories[i] == NULL) {
      fprintf(stderr, "font_directory::table_directory_t::malloc\n");
      exit(1);
    }
    tl_fread(font_directory->table_directories[i], sizeof(table_directory_t), 1, font_file);
    table_directory_be_to_host(font_directory->table_directories[i]);
  }

  return font_directory;
}

void font_directory_destroy(font_directory_t* fd) {
  for (size_t i = 0; i < fd->offset_subtable.num_tables; ++i) {
    free(fd->table_directories[i]);
    fd->table_directories[i] = NULL;
  }
  free(fd);
  fd = NULL;
}

void font_directory_print(font_directory_t* font_directory) {
  offset_subtable_print(&font_directory->offset_subtable);

  for (size_t i = 0; i < font_directory->offset_subtable.num_tables; ++i) {
    table_directory_print(font_directory->table_directories[i]);
  }
}
