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

void* font_table_create(FILE* font_file, table_directory_t* table_directory) {
  if (table_directory->tag == hhea || table_directory->tag == hmtx) {
    return NULL;
  }
  uint8_t tag_string[5] = {0};
  tag_stringify(table_directory->tag, tag_string);
  printf("%s\n", tag_string);

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
    return_table = os2_table_create(table_data, table_directory);
    break;
  case VDMX:
    break;
  case cmap:
    return_table = cmap_table_create(font_file, table_directory);
    break;
  case cvt:
    break;
  case fpgm:
    break;
  case gasp:
    return_table = gasp_table_create(font_file, table_directory);
    break;
  case glyf:
    break;
  case hdmx:
    break;
  case head:
    return_table = head_table_create(font_file, table_directory);
    break;
  case hhea:
    return_table = hhea_table_create(table_data, table_directory);
    break;
  case hmtx:
    break;
  case kern:
    break;
  case loca:
    break;
  case maxp:
    return_table = maxp_table_create(font_file, table_directory);
    break;
  case name:
    return_table = name_table_create(font_file, table_directory);
    break;
  case post:
    return_table = post_table_create(font_file, table_directory);
    break;
  case prep:
    break;
  default:
    printf("unknown table: %s (%u)\n", tag_string, table_directory->tag);
  }

END:
  free(table_data);
  table_data = NULL;

  return return_table;
}
