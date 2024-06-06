#include <string.h>

#include "font_table.h"
#include "os2.h"

enum { // int encoded table names
  DSIG = 68083073071,
  GDEF = 71068069070,
  GPOS = 71080079083,
  GSUB = 71083085066,
  OS2 = 79083047050,
  VDMX = 86068077088,
  cmap = 99109097112,
  cvt = 99118116032,
  fpgm = 102112103109,
  gasp = 103097115112,
  glyf = 103108121102,
  head = 104101097100,
  hhea = 104104101097,
  hmtx = 104109116120,
  kern = 107101114110,
  loca = 108111099097,
  maxp = 109097120112,
  name = 110097109101,
  post = 112111115116,
  prep = 112114101112,
};

void* font_table_create(FILE* font_file, table_directory_t* table_directory) {
  uint64_t intified_tag = intify_tag(table_directory->tag);
  uint8_t tag_string[5] = {0};

  switch (intified_tag) {
  case DSIG:
    break;
  case GSUB:
    break;
  case GDEF:
    break;
  case GPOS:
    break;
  case OS2:
    return os2_table_create(font_file, table_directory);
  case VDMX:
    break;
  case cmap:
    break;
  case cvt:
    break;
  case fpgm:
    break;
  case gasp:
    break;
  case glyf:
    break;
  case head:
    break;
  case hhea:
    break;
  case hmtx:
    break;
  case kern:
    break;
  case loca:
    break;
  case maxp:
    break;
  case name:
    break;
  case post:
    break;
  case prep:
    break;
  default:
    memcpy(tag_string, table_directory->tag, 4);
    tag_string[4] = '\0';
    printf("unknown table: %s (%lu)\n", tag_string, intified_tag);
  }
  return NULL;
}
