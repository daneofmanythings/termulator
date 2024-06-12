#include <assert.h>
#include <endian.h>
#include <stdint.h>
#include <string.h>

#include "post.h"

static inline void test_printer(post_table_t* table);
static void test_printing_string_data_lengths(post_table_t* table, size_t string_data_length);

static void post_table_be_to_host(post_table_t* table);
char* post_table_get_glyph_at(post_table_t* table, uint16_t glyph_num);

post_table_t* post_table_create(uint8_t* table_data, table_directory_t* table_directory) {
  post_table_t* table = (post_table_t*)malloc(sizeof(post_table_t));
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  uint8_t* table_data_read_ptr = table_data;

  memcpy(&table->header, table_data_read_ptr, sizeof(post_header_t));
  table_data_read_ptr += sizeof(post_header_t);

  if (table->header.version == 0x00025000) {
    fprintf(stderr, "post_table::create::ERROR ('post' table version '2.5' is not supported.)\n");
    free(table);
    table = NULL;
    return NULL;
  }

  memcpy(&table->data.num_glyphs, table_data_read_ptr, sizeof(uint16_t));
  table_data_read_ptr += sizeof(uint16_t);

  size_t glyph_name_index_length = be16toh(table->data.num_glyphs) * sizeof(uint16_t);
  uint16_t* glyph_name_index = (uint16_t*)malloc(glyph_name_index_length);
  if (glyph_name_index == NULL) {
    free(table);
    table = NULL;
    return NULL; // TODO: error handling
  }

  memcpy(glyph_name_index, table_data_read_ptr, glyph_name_index_length);
  table_data_read_ptr += glyph_name_index_length;
  table->data.glyph_name_index = glyph_name_index;

  post_table_be_to_host(table);

  size_t string_data_length = table_directory->length - sizeof(table->header) -
                              sizeof(uint16_t) * (table->data.num_glyphs + 1);

  uint8_t* string_data = (uint8_t*)malloc(string_data_length);
  if (string_data == NULL) {
    return NULL; // TODO: error handling
  }
  memcpy(string_data, table_data_read_ptr, string_data_length);
  table->data.string_data = string_data;

  // test_printing_string_data_lengths(table, string_data_length);

  return table;
}

static void post_table_be_to_host(post_table_t* table) {
  table->header.version = be32toh(table->header.version);
  table->header.italic_angle = be16toh(table->header.italic_angle);
  table->header.underline_position = be16toh(table->header.underline_position);
  table->header.underline_thickness = be16toh(table->header.underline_thickness);
  table->header.is_fixed_pitch = be32toh(table->header.is_fixed_pitch);
  table->header.min_mem_type_42 = be32toh(table->header.min_mem_type_42);
  table->header.max_mem_type_42 = be32toh(table->header.max_mem_type_42);
  table->header.min_mem_type_1 = be32toh(table->header.min_mem_type_1);
  table->header.max_mem_type_1 = be32toh(table->header.max_mem_type_1);
  table->data.num_glyphs = be16toh(table->data.num_glyphs);
  for (size_t i = 0; i < table->data.num_glyphs; ++i) {
    table->data.glyph_name_index[i] = be16toh(table->data.glyph_name_index[i]);
  }
}

// TODO: validate the position within string_data. possibly store string_data length.
char* post_table_get_glyph_at(post_table_t* table, uint16_t glyph_num) {
  if (glyph_num >= table->data.num_glyphs) {
    return NULL; // TODO: errror handling
  }

  size_t name_index = table->data.glyph_name_index[glyph_num];
  size_t i = 0;
  size_t offset_index = 0;
  size_t len = 0;
  while (i < name_index) {
    len = table->data.string_data[offset_index];
    offset_index += len + 1;
    i += 1;
  }
  char* glyph_name = (char*)malloc(len + 1);
  if (glyph_name == NULL) {
    return NULL; // TODO: error handling
  }
  memcpy(glyph_name, &table->data.string_data[offset_index + 1], len);
  glyph_name[len] = '\0';
  return glyph_name;
}

static inline void test_printer(post_table_t* table) {
  uint16_t string_length = 8883;
  printf("string_length: %d\n", string_length);
  for (size_t i = 0; i < string_length; ++i) {
    printf("%c", table->data.string_data[i]);
  }
  printf("\n");
}

static void test_printing_string_data_lengths(post_table_t* table, size_t string_data_length) {
  size_t i = 0;
  uint8_t len = 0;
  while (i < string_data_length) {
    len = table->data.string_data[i];
    printf("string %zu, length %d, value: ", i, len);
    for (size_t j = 1; j <= len; j++) {
      printf("%c", table->data.string_data[j + i]);
    }
    printf("\n");
    i += len + 1;
  }
}
