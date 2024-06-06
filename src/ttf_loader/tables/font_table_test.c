#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <stdint.h>

#include "font_table.h"

Test(intify_tag, compare_two) {
  uint8_t a[4] = {'a', 'b', 'a', 'a'};
  uint8_t b[4] = {'b', 'b', 'b', 'b'};
  cr_assert(intify_tag(a) < intify_tag(b));
}

Test(intify_tag, is_exact) {
  uint8_t a[4] = {'D', 'S', 'I', 'G'};
  uint64_t a_intified = 68083073071;
  cr_assert(intify_tag(a) == a_intified);
}
