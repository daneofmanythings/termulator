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
