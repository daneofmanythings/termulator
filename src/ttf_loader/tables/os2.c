#include "os2.h"
#include "../../lib.h"
#include "font_table.h"

#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void os2_table_be_to_host(os2_table_t* table);

// TODO: implement orrer handling
os2_table_t* os2_table_create(FILE* font_file, table_directory_t* table_directory) {
  // check that the correct table_directory was passed in.
  //
  // allocate memory
  os2_table_t* table = (os2_table_t*)malloc(table_directory->length);
  if (table == NULL) {
    return NULL;
  }

  // copy the file over
  tl_fseek("OS/2", font_file, table_directory->offset);
  tl_fread(table, table_directory->length, 1, font_file);
  // compare checksums
  if (!font_table_verify_checksum("OS/2", table_directory->checksum, (uint32_t*)table,
                                  sizeof(*table))) {
    // TODO: error handling
  }

  // correct the endianess
  os2_table_be_to_host(table);

  // Not supporting versions less than 3
  if (table->version < 3) {
    return NULL;
  }
  // blank out last two fields for vertion 3 and 4
  if (table->version < 5) {
    table->us_lower_optical_point_size = 0;
    table->us_upper_optical_point_size = 0;
  }

  // return the table
  return table;
}

static void os2_table_be_to_host(os2_table_t* table) {
  table->version = be16toh(table->version);
  table->x_avg_char_width = be16toh(table->x_avg_char_width);
  table->us_weight_class = be16toh(table->us_weight_class);
  table->us_width_class = be16toh(table->us_width_class);
  table->fs_type = be16toh(table->fs_type);
  table->y_subscript_x_size = be16toh(table->y_subscript_x_size);
  table->y_subscript_y_size = be16toh(table->y_subscript_y_size);
  table->y_subscript_x_offset = be16toh(table->y_subscript_x_offset);
  table->y_subscript_y_offset = be16toh(table->y_subscript_y_offset);
  table->y_superscript_x_size = be16toh(table->y_superscript_x_size);
  table->y_superscript_y_size = be16toh(table->y_superscript_y_size);
  table->y_superscript_x_offset = be16toh(table->y_superscript_x_offset);
  table->y_superscript_y_offset = be16toh(table->y_superscript_y_offset);
  table->y_strikeout_size = be16toh(table->y_strikeout_size);
  table->y_strikeout_position = be16toh(table->y_strikeout_position);
  table->s_family_class = be16toh(table->s_family_class);
  //
  // TODO: figure out what to do about the panose.
  //
  table->ul_unicode_range[0] = be32toh(table->ul_unicode_range[0]);
  table->ul_unicode_range[1] = be32toh(table->ul_unicode_range[1]);
  table->ul_unicode_range[2] = be32toh(table->ul_unicode_range[2]);
  table->ul_unicode_range[3] = be32toh(table->ul_unicode_range[3]);
  table->ach_vend_id = be32toh(table->ach_vend_id);
  table->fs_selection = be16toh(table->fs_selection);
  table->us_first_char_index = be16toh(table->us_first_char_index);
  table->us_last_char_index = be16toh(table->us_last_char_index);
  table->s_typo_ascender = be16toh(table->s_typo_ascender);
  table->s_typo_descender = be16toh(table->s_typo_descender);
  table->s_typo_line_gap = be16toh(table->s_typo_line_gap);
  table->us_win_ascent = be16toh(table->us_win_ascent);
  table->us_win_descent = be16toh(table->us_win_descent);
  table->ul_code_page_range[0] = be32toh(table->ul_code_page_range[0]);
  table->ul_code_page_range[1] = be32toh(table->ul_code_page_range[1]);
  table->sx_height = be16toh(table->sx_height);
  table->s_cap_height = be16toh(table->s_cap_height);
  table->us_default_char = be16toh(table->us_default_char);
  table->us_break_char = be16toh(table->us_break_char);
  table->us_max_context = be16toh(table->us_max_context);
  table->us_lower_optical_point_size = be16toh(table->us_lower_optical_point_size);
  table->us_upper_optical_point_size = be16toh(table->us_upper_optical_point_size);
}
