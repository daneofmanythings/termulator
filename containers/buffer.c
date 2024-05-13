#include "../containers.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <criterion/criterion.h>

static const float BUFFER_RESIZE_COEF = 1.5;

static bool _buffer_grow(Buffer* buf) {
  // check if cap will overflow
  if (buf->capacity * BUFFER_RESIZE_COEF > UINT_MAX) {
    fprintf(stderr, "Buffer grow failed. overflow\n");
    return false;
  }

  buf->capacity *= BUFFER_RESIZE_COEF;
  char* temp = (char*)realloc(buf->data, buf->capacity * sizeof(char));
  if (temp) {
    // free(buf->data);
    buf->data = temp;
    return true;
  }
  return false;
}

static inline uint _new_shrink_capacity(Buffer* buf) {
  uint new_capacity = buf->size * BUFFER_RESIZE_COEF;
  new_capacity = new_capacity < buf->min_capacity ? buf->min_capacity : new_capacity;
  return new_capacity < buf->capacity ? new_capacity : buf->capacity;
}

static bool _buffer_shrink(Buffer* buf) {
  // min val for shrinkage
  if (buf->capacity <= buf->min_capacity) {
    return false;
  }

  buf->capacity = _new_shrink_capacity(buf);
  char* temp = (char*)realloc(buf->data, buf->capacity * sizeof(char));
  if (temp) {
    // free(buf->data);
    buf->data = temp;
    return true;
  }
  return false;
}

Buffer* containers_buffer_create(const uint capacity) {
  if (capacity > UINT_MAX) {
    printf("buffer creation, capacity overflow");
    return NULL;
  }

  Buffer* buf = (Buffer*)calloc(1, sizeof(Buffer));
  if (!buf) {
    printf("buffer allocation failed\n");
    return NULL;
  }
  char* data = (char*)calloc(capacity, sizeof(char));
  if (!data) {
    printf("buffer data allocation failed\n");
  }

  buf->data = data;
  buf->size = 0;
  buf->capacity = capacity;
  *((uint*)&buf->min_capacity) = capacity;

  return buf;
}

void containers_buffer_cleanup(Buffer* buf) {
  free(buf->data);
  buf->data = NULL;
  free(buf);
  buf = NULL;
}

const char* containers_buffer_push(Buffer* buf, const char* ch) {
  if (buf->size >= UINT_MAX) {
    return NULL;
  }
  if (buf->size == buf->capacity) {
    bool success = _buffer_grow(buf);
    if (!success) {
      fprintf(stderr, "Could not push to buffer\n");
      return NULL;
    }
  }
  buf->data[buf->size] = *ch;
  buf->size++;
  return ch;
}

char containers_buffer_pop(Buffer* buf) {
  if (buf->size == 0) {
    return '\0'; // TODO: have this failed more deliberately?
  }
  uint idx = buf->size - 1;
  char ch = buf->data[idx];
  buf->size--;

  if (buf->size < buf->capacity / 2) {
    _buffer_shrink(buf);
  }

  return ch;
}

char containers_buffer_peek(const Buffer* buf) {
  if (buf->size == 0) {
    return '\0';
  }
  return buf->data[buf->size - 1];
}

const char* containers_buffer_read(const Buffer* buf) {
  //
  return NULL;
}

Test(buffer_static, _shrink_capacity_num) {
  struct test_cases {
    uint size;
    uint capacity;
    uint min_capacity;
    uint expected;
  };
  struct test_cases tc[] = {
      { 0,  8, 8,  8},
      {20, 50, 8, 30},
      {20, 25, 8, 25},
  };
  const uint num_test_cases = 3;

  uint got;
  for (uint i = 0; i < num_test_cases; ++i) {
    Buffer* buf = containers_buffer_create(tc[i].min_capacity);
    buf->size = tc[i].size;
    buf->capacity = tc[i].capacity;

    got = _new_shrink_capacity(buf);
    // cr_log_warn("%d\n", got);
    cr_assert(got == tc[i].expected);

    containers_buffer_cleanup(buf);
  }
}
