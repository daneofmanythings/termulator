#include <endian.h>
#include <stdint.h>
#include <string.h>

#include "name.h"

static void name_table_header_be_to_host(name_table_t* table);
static void name_record_be_to_host(name_record_t* name_record);
static void lang_tag_record_be_to_host(lang_tag_record_t* lang_tag_record);

static void name_record_print(name_record_t* name_record) {
  printf("----\n");
  printf("platform_id: %d\n", name_record->platform_id);
  printf("encoding_id: %d\n", name_record->encoding_id);
  printf("language_id: %d\n", name_record->language_id);
  printf("name_id: %d\n", name_record->name_id);
  printf("length: %d\n", name_record->length);
  printf("string_offset: %d\n", name_record->string_offset);
}

static void lang_tag_record_print(lang_tag_record_t* lang_tag_record) {
  printf("----\n");
  printf("length: %d\n", lang_tag_record->length);
  printf("lang_tag_offset: %d\n", lang_tag_record->lang_tag_offset);
}

static void string_data_print(name_table_t* table, uint16_t length, uint16_t offset) {
  for (size_t i = 0; i < length; ++i) {
    printf("%c", table->string_data[offset + i - 1]);
  }
  printf("\n");
}

// TODO: VERIFY THAT THE NAME_RECORDS ARE BEING PARSED CORRECTLY, AND THAT THE STRING DATA
// IS BEING LOADED CORRECTLY. THE STRINGS SEEM FISHY.
name_table_t* name_table_create(uint32_t* table_data, table_directory_t* table_directory) {

  name_table_t* table = (name_table_t*)malloc(sizeof(name_table_t));
  if (table == NULL) {
    return NULL; // TODO: error handling
  }
  uint8_t* table_data_read_ptr = (uint8_t*)table_data;

  memcpy(table, table_data_read_ptr, sizeof(uint16_t) * 3);
  table_data_read_ptr += sizeof(uint16_t) * 3;
  name_table_header_be_to_host(table);

  name_record_t* name_records = (name_record_t*)malloc(sizeof(name_record_t) * table->count);
  if (name_records == NULL) {
    free(table);
    table = NULL;
    return NULL; // TODO: error handling
  }

  memcpy(name_records, table_data_read_ptr, sizeof(name_record_t) * table->count);

  for (size_t i = 0; i < table->count; ++i) {
    name_record_be_to_host(&name_records[i]);
    // name_record_print(&name_records[i]);
  }
  table_data_read_ptr += sizeof(name_record_t) * table->count;
  table->name_records = name_records;

  table->lang_tag_count = 0;
  table->lang_tag_records = NULL;
  if (table->version == 1) {
    memcpy(&table->lang_tag_count, table_data_read_ptr, sizeof(uint16_t));
    table_data_read_ptr += sizeof(uint16_t);

    lang_tag_record_t* lang_tag_records =
        (lang_tag_record_t*)malloc(sizeof(lang_tag_record_t) * table->lang_tag_count);
    if (lang_tag_records == NULL) {
      return NULL; // TODO: error handling
    }

    memcpy(lang_tag_records, table_data_read_ptr,
           sizeof(lang_tag_record_t) * table->lang_tag_count);

    for (size_t i = 0; i < table->lang_tag_count; ++i) {
      lang_tag_record_be_to_host(&lang_tag_records[i]);
      // lang_tag_record_print(&lang_tag_records[i]);
    }
  }

  size_t string_data_length = table_directory->length - table->storage_offset;

  uint8_t* string_data = (uint8_t*)malloc(string_data_length);
  if (string_data == NULL) {
    return NULL; // TODO: error handling
  }

  table_data_read_ptr = (uint8_t*)table + table->storage_offset;

  memcpy(string_data, table_data_read_ptr, string_data_length);
  table->string_data = string_data;

  // for (size_t i = 0; i < table->count; ++i) {
  //   printf("\nname_table: %zu\n---\n ", i);
  //   string_data_print(table, table->name_records[i].length,
  //   table->name_records[i].string_offset); printf("---\n");
  // }

  return table;
}

static void name_table_header_be_to_host(name_table_t* table) {
  table->version = be16toh(table->version);
  table->count = be16toh(table->count);
  table->storage_offset = be16toh(table->storage_offset);
}

static void name_record_be_to_host(name_record_t* name_record) {
  name_record->platform_id = be16toh(name_record->platform_id);
  name_record->encoding_id = be16toh(name_record->encoding_id);
  name_record->language_id = be16toh(name_record->language_id);
  name_record->name_id = be16toh(name_record->name_id);
  name_record->length = be16toh(name_record->length);
  name_record->string_offset = be16toh(name_record->string_offset);
}

static void lang_tag_record_be_to_host(lang_tag_record_t* lang_tag_record) {
  lang_tag_record->length = be16toh(lang_tag_record->length);
  lang_tag_record->lang_tag_offset = be16toh(lang_tag_record->lang_tag_offset);
}
