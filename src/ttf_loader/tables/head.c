#include "head.h"
#include "../../lib.h"
#include "font_directory.h"
#include "font_table.h"
#include <endian.h>

static void head_table_be_to_host(head_table_t* table);

head_table_t* head_table_create(FILE* font_file, table_directory_t* table_directory) {
  head_table_t* table = (head_table_t*)malloc(table_directory->length);
  if (table == NULL) {
    return NULL; // TODO: error handling
  }

  tl_fseek("head", font_file, table_directory->offset);
  tl_fread(table, table_directory->length, 1, font_file);

  // TODO: implement the special checksum verification for this table.
  // https://learn.microsoft.com/en-us/typography/opentype/spec/head

  /*
    The 'head' table is a special case in checksum calculations, as it includes
    a checksumAdjustment field that is calculated and written after the table’s
    checksum is calculated and written into the table directory entry, necessarily
    invalidating that checksum value.

    When generating font data, to calculate and write the 'head' table checksum and
    checksumAdjustment field, do the following:

    1. Set the checksumAdjustment field to 0.
    2. Calculate the checksum for all tables including the 'head' table and
       enter the value for each table into the corresponding record in the table directory.
    3. Calculate the checksum for the entire font.
    4. Subtract that value from 0xB1B0AFBA.
    5. Store the result in the 'head' table checksumAdjustment field.

    An application attempting to verify that the 'head' table has not changed should
    calculate the checksum for that table assuming that the checksumAdjustment value
    is zero, rather than the actual value in the font, before comparing the result with
    the 'head' table record in the table directory.

    Within a font collection file (see below), table checksums must reflect the tables as
    they are in the collection file. The checksumAdjustment field in the 'head' table is
    not used for collection files and may be set to zero.
  */

  head_table_be_to_host(table);

  return table;
}

static void head_table_be_to_host(head_table_t* table) {
  table->major_version = be16toh(table->major_version);
  table->minor_version = be16toh(table->minor_version);
  table->font_revision = be32toh(table->font_revision);
  table->checksum_adjustment = be32toh(table->checksum_adjustment);
  table->magic_number = be32toh(table->magic_number);
  table->flags = be16toh(table->flags);
  table->units_per_em = be16toh(table->units_per_em);
  table->created = be64toh(table->created);
  table->modified = be64toh(table->modified);
  table->x_min = be16toh(table->x_min);
  table->y_min = be16toh(table->y_min);
  table->x_max = be16toh(table->x_max);
  table->y_max = be16toh(table->y_max);
  table->mac_style = be16toh(table->mac_style);
  table->lowest_rec_ppem = be16toh(table->lowest_rec_ppem);
  table->font_direction_hint = be16toh(table->font_direction_hint);
  table->index_to_loc_format = be16toh(table->index_to_loc_format);
  table->glyph_data_format = be16toh(table->glyph_data_format);
}
