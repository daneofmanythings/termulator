#include <string.h>

#include "../data_types.h"
#include "cmap.h"
#include "font_table.h"
#include "gasp.h"
#include "head.h"
#include "hhea.h"
#include "maxp.h"
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
  uint8_t tag_string[5] = {0};

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
    return os2_table_create(font_file, table_directory);
  case VDMX:
    break;
  case cmap:
    break;
    // return cmap_table_create(font_file, table_directory);
  case cvt:
    break;
  case fpgm:
    break;
  case gasp:
    return gasp_table_create(font_file, table_directory);
  case glyf:
    break;
  case hdmx:
    break;
  case head:
    return head_table_create(font_file, table_directory);
  case hhea:
    return hhea_table_create(font_file, table_directory);
  case hmtx:
    break;
  case kern:
    break;
  case loca:
    break;
  case maxp:
    return maxp_table_create(font_file, table_directory);
  case name:
    break;
  case post:
    return post_table_create(font_file, table_directory);
  case prep:
    break;
  default:
    tag_stringify(table_directory->tag, tag_string);
    printf("unknown table: %s (%u)\n", tag_string, table_directory->tag);
  }
  return NULL;
}
