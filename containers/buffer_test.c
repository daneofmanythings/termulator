#include "../containers.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/logging.h>

static const char* s = "0123456789";

Test(buffer, create_sizes) {
  Buffer* buf = containers_buffer_create(8);
  cr_assert_eq(buf->min_capacity, 8);
  cr_assert_eq(buf->capacity, 8);
  cr_assert_eq(buf->size, 0);
  containers_buffer_cleanup(buf);
}

Test(buffer, push) {
  Buffer* buf = containers_buffer_create(8);
  for (uint i = 0; i < 10; ++i) {
    containers_buffer_push(buf, &s[i]);
    cr_assert(buf->data[i] == s[i]);
  }
  cr_assert_eq(buf->size, 10);
  cr_assert_eq(buf->capacity, 12); // WARN: fragile. depends on grow coeff
  containers_buffer_cleanup(buf);
}

Test(buffer, pop) {
  Buffer* buf = containers_buffer_create(4);
  for (uint i = 0; i < 10; ++i) {
    containers_buffer_push(buf, &s[i]);
  }
  for (uint i = 0; i < 10; ++i) {
    char got = containers_buffer_pop(buf);
    char expected = s[10 - i - 1]; // WARN: fragile
    cr_assert(got == expected);
  }
  containers_buffer_cleanup(buf);
}

Test(buffer, peek) {
  Buffer* buf = containers_buffer_create(10);
  cr_assert(containers_buffer_peek(buf) == '\0');
  for (uint i = 0; i < 10; ++i) {
    containers_buffer_push(buf, &s[i]);
    cr_assert(containers_buffer_peek(buf) == s[i]);
  }
  containers_buffer_cleanup(buf);
}
