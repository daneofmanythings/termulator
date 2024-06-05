#ifndef SRC_TTFLOADER_TABLES_OS2_H
#define SRC_TTFLOADER_TABLES_OS2_H

#include "../data_types.h"

typedef struct os2_table_v3 {
  uint16_t version;
  FWORD x_avg_char_width;
  uint16_t us_weight_class;
  uint16_t us_width_class;
  uint16_t fs_type;
  FWORD y_subscript_x_size;
  FWORD y_subscript_y_size;
  FWORD y_subscript_x_offset;
  FWORD y_subscript_y_offset;
  FWORD y_superscript_x_size;
  FWORD y_superscript_y_size;
  FWORD y_superscript_x_offset;
  FWORD y_superscript_y_offset;
  FWORD y_strikeout_size;
  FWORD y_strikeout_position;
  int16_t s_family_class;
  uint8_t panose[10];
  uint32_t ul_unicode_range[4];
  TAG ach_vend_id;
  uint16_t fs_selection;
  uint16_t fs_first_char_index;
  uint16_t fs_last_char_index;
  FWORD s_typo_ascender;
  FWORD s_typo_descender;
  FWORD s_typo_line_gap;
  UFWORD us_win_ascent;
  UFWORD us_win_descent;
  uint32_t ul_code_page_range[2];
  FWORD sx_height;
  FWORD s_cap_height;
  uint16_t us_default_char;
  uint16_t us_break_char;
  uint16_t us_max_content;
} os2_table_v3_t;

#endif // !DEBUG
