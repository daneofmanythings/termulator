#include "cmap.h"
#include <endian.h>
#include <string.h>

static void cmap_header_be_to_host(cmap_table_t* table);
static void cmap_encoding_record_be_to_host(encoding_record_t* encoding_record);

cmap_table_t* cmap_table_create(uint32_t* table_data, table_directory_t* table_directory) {
  uint8_t* table_data_read_ptr = (uint8_t*)table_data;

  cmap_table_t* table = (cmap_table_t*)malloc(sizeof(cmap_table_t));
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  memcpy(table, table_data_read_ptr, sizeof(uint16_t) * 2);
  table_data_read_ptr += sizeof(uint16_t) * 2;

  cmap_header_be_to_host(table);

  size_t encoding_records_length = sizeof(encoding_record_t) * table->num_tables;
  encoding_record_t* encoding_records = (encoding_record_t*)malloc(encoding_records_length);
  if (encoding_records == NULL) {
    free(table);
    table = NULL;
    return NULL; // TODO: error handling
  }

  memcpy(encoding_records, table_data_read_ptr, encoding_records_length);
  table_data_read_ptr += encoding_records_length;

  table->encoding_records = encoding_records;
  for (size_t i = 0; i < table->num_tables; ++i) {
    cmap_encoding_record_be_to_host(&table->encoding_records[i]);
  }

  // TODO: implement subtables

  return table;
}

static void cmap_header_be_to_host(cmap_table_t* table) {
  table->version = be16toh(table->version);
  table->num_tables = be16toh(table->num_tables);
}

static void cmap_encoding_record_be_to_host(encoding_record_t* encoding_record) {
  encoding_record->platform_id = be16toh(encoding_record->platform_id);
  encoding_record->encoding_id = be16toh(encoding_record->encoding_id);
  encoding_record->subtable_offset = be32toh(encoding_record->subtable_offset);
}

uint16_t subtable_peek_format(uint16_t* subtable);
void subtable_v0_destroy(cmap_subtable_v0_t* subtable);
void subtable_v2_destroy(cmap_subtable_v2_t* subtable);
void subtable_v4_destroy(cmap_subtable_v4_t* subtable);
void subtable_v6_destroy(cmap_subtable_v6_t* subtable);
void subtable_v8_destroy(cmap_subtable_v8_t* subtable);
void subtable_v10_destroy(cmap_subtable_v10_t* subtable);
void subtable_v12_destroy(cmap_subtable_v12_t* subtable);
void subtable_v13_destroy(cmap_subtable_v13_t* subtable);
void subtable_v14_destroy(cmap_subtable_v14_t* subtable);

void cmap_table_destroy(cmap_table_t* table) {
  free(table->encoding_records);
  table->encoding_records = NULL;

  for (size_t i = 0; i < table->num_tables; ++i) {
    void* subtable = &table->subtables[i];
    if (subtable == NULL) {
      continue;
    }
    //   uint16_t subtable_format = subtable_peek_format(subtable);
    //   switch (subtable_format) {
    //   case 0:
    //     subtable_v0_destroy(subtable);
    //     break;
    //   case 2:
    //     subtable_v2_destroy(subtable);
    //     break;
    //   case 4:
    //     subtable_v4_destroy(subtable);
    //     break;
    //   case 6:
    //     subtable_v6_destroy(subtable);
    //     break;
    //   case 8:
    //     subtable_v8_destroy(subtable);
    //     break;
    //   case 10:
    //     subtable_v10_destroy(subtable);
    //     break;
    //   case 12:
    //     subtable_v12_destroy(subtable);
    //     break;
    //   case 13:
    //     subtable_v13_destroy(subtable);
    //     break;
    //   case 14:
    //     subtable_v14_destroy(subtable);
    //     break;
    //   default:
    //     break;
    //   }
  }
}

uint16_t subtable_peek_format(uint16_t* subtable) {
  uint16_t format = 0;
  memcpy(&format, subtable, sizeof(uint16_t));
  return format;
}

void subtable_v0_destroy(cmap_subtable_v0_t* subtable) {
  free(subtable);
  subtable = NULL;
}

void subtable_v2_destroy(cmap_subtable_v2_t* subtable) {
  free(subtable->sub_headers);
  subtable->sub_headers = NULL;
  free(subtable->glyph_id_array);
  subtable->glyph_id_array = NULL;
  free(subtable);
  subtable = NULL;
}

void subtable_v4_destroy(cmap_subtable_v4_t* subtable) {
  free(subtable->end_code);
  subtable->end_code = NULL;
  free(subtable->id_delta);
  subtable->id_delta = NULL;
  free(subtable->id_range_offset);
  subtable->id_range_offset = NULL;
  free(subtable->glyph_id_array);
  subtable->glyph_id_array = NULL;
  free(subtable);
  subtable = NULL;
}

void subtable_v6_destroy(cmap_subtable_v6_t* subtable) {
  free(subtable->glyph_id_array);
  subtable->glyph_id_array = NULL;
  free(subtable);
  subtable = NULL;
}

void subtable_v8_destroy(cmap_subtable_v8_t* subtable) {
  free(subtable->groups);
  subtable->groups = NULL;
  free(subtable);
  subtable = NULL;
}

void subtable_v10_destroy(cmap_subtable_v10_t* subtable) {
  free(subtable->glyph_id_array);
  subtable->glyph_id_array = NULL;
  free(subtable);
  subtable = NULL;
}

void subtable_v12_destroy(cmap_subtable_v12_t* subtable) {
  free(subtable->groups);
  subtable->groups = NULL;
  free(subtable);
  subtable = NULL;
}

void subtable_v13_destroy(cmap_subtable_v13_t* subtable) {
  free(subtable->groups);
  subtable->groups = NULL;
  free(subtable);
  subtable = NULL;
}

void subtable_v14_destroy(cmap_subtable_v14_t* subtable) {
  free(subtable->var_selector);
  subtable->var_selector = NULL;
  // TODO: implement the rest
}
