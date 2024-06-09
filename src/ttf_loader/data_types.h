#ifndef SRC_TTFLOADER_DATATYPES_H
#define SRC_TTFLOADER_DATATYPES_H

#include <stddef.h>
#include <stdint.h>

typedef int16_t FWORD;
typedef uint16_t UFWORD;
typedef uint32_t TAG;
typedef int32_t FIXED;
typedef int16_t F2DOT14;
typedef int64_t LONGDATETIME;
typedef uint32_t OFFSET32;
typedef uint32_t VERSION16DOT16;

static inline void tag_stringify(TAG tag, uint8_t tag_string[5]) {
  tag_string[4] = '\0';
  for (size_t shift_amount = 0; shift_amount < 4; shift_amount++) {
    tag_string[3 - shift_amount] = (tag >> (8 * shift_amount)) & UINT8_MAX;
  }
}

#endif // !DEBUG
