#include <string.h>

#include "../../lib.h"
#include "../data_types.h"
#include "cmap.h"
#include "font_table.h"
#include "gasp.h"
#include "head.h"
#include "hhea.h"
#include "maxp.h"
#include "name.h"
#include "os2.h"
#include "post.h"

enum {
  DSIG = 1146308935,
  FFTM = 1195656518,
  GDEF = 1,
  GPOS = 1196445523,
  GSUB = 1196643650,
  LTSH = 1280594760,
  OS2 = 1330851634,
  VDMX = 1447316824,
  cmap = 1668112752,
  cvt = 1668707360,
  fpgm = 1718642541,
  gasp = 1734439792,
  glyf = 1735162214,
  hdmx = 1751412088,
  head = 1751474532,
  hhea = 1751672161,
  hmtx = 1752003704,
  kern = 1801810542,
  loca = 1819239265,
  maxp = 1835104368,
  name = 1851878757,
  post = 1886352244,
  prep = 1886545264,
};
static uint32_t font_table_calculate_checksum(uint32_t* table, uint32_t length);
static bool font_table_verify_checksum(const char* name, uint32_t checksum, uint32_t* table,
                                       uint32_t length);

void* font_table_create(FILE* font_file, table_directory_t* table_directory) {
  uint8_t tag_string[5] = {0};
  tag_stringify(table_directory->tag, tag_string);

  void* return_table = NULL;
  uint32_t* table_data = (uint32_t*)calloc(1, table_directory->length); // slow
  if (table_data == NULL) {
    return NULL; // TODO: error handling
  }
  tl_fseek((const char*)tag_string, font_file, table_directory->offset);
  tl_fread(table_data, table_directory->length, 1, font_file);
  if (!font_table_verify_checksum((const char*)tag_string, table_directory->checksum, table_data,
                                  table_directory->length)) {
    // goto END; // TODO: error handling
    ;
  }

  switch (table_directory->tag) {
  case DSIG:
    break;
  case FFTM:
    break;
  case GSUB:
    break;
  case GDEF:
    break;
  case GPOS:
    break;
  case LTSH:
    break;
  case OS2:
    return_table = os2_table_create((uint8_t*)table_data, table_directory);
    break;
  case VDMX:
    break;
  case cmap:
    return_table = cmap_table_create((uint8_t*)table_data, table_directory);
    break;
  case cvt:
    break;
  case fpgm:
    break;
  case gasp:
    return_table = gasp_table_create((uint8_t*)table_data, table_directory);
    break;
  case glyf:
    break;
  case hdmx:
    break;
  case head:
    return_table = head_table_create((uint8_t*)table_data, table_directory);
    break;
  case hhea:
    return_table = hhea_table_create((uint8_t*)table_data, table_directory);
    break;
  case hmtx:
    break;
  case kern:
    break;
  case loca:
    break;
  case maxp:
    return_table = maxp_table_create((uint8_t*)table_data, table_directory);
    break;
  case name:
    return_table = name_table_create((uint8_t*)table_data, table_directory);
    break;
  case post:
    return_table = post_table_create((uint8_t*)table_data, table_directory);
    break;
  case prep:
    break;
  default:
    fprintf(stderr, "unknown table: %s (%u)\n", tag_string, table_directory->tag);
  }

  // END:
  free(table_data);
  table_data = NULL;

  return return_table;
}

/* NOTE:

This function assumes that the length of any table is a multiple of four bytes,
or that tables are padded with zero to four-byte aligned offsets. Actual table lengths
recorded in the table directory should not include padding, however. To accommodate
data with a length that is not a multiple of four, the below algorithm must be modified
to treat the data as though it contains zero padding to a length that is a multiple of four.

*/
static uint32_t font_table_calculate_checksum(uint32_t* table, uint32_t length) {
  uint32_t sum = 0L;
  uint32_t* end_ptr = table + ((length + 3) & ~3) / sizeof(uint32_t);
  while (table < end_ptr) {
    sum += be32toh(*table);
    table++;
  }
  return sum;
}

static bool font_table_verify_checksum(const char* name, uint32_t checksum, uint32_t* table,
                                       uint32_t length) {
  uint32_t calculated_checksum = font_table_calculate_checksum(table, length);
  if (checksum != calculated_checksum) {
    fprintf(stderr, "'%s' INVALID CHECKSUM. %u != %u\n", name, checksum, calculated_checksum);
    return false;
  }
  return true;
}
//
// TODO: implement the special checksum verification for the head table.
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
