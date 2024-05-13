#include <sys/types.h>

typedef struct {
  char* data;
  uint size;
  uint capacity;
  const uint min_capacity;
} Buffer;

Buffer* containers_buffer_create(const uint capacity);
void containers_buffer_cleanup(Buffer* buf);
const char* containers_buffer_push(Buffer* buf, const char* ch);
char containers_buffer_pop(Buffer* buf);
char containers_buffer_peek(const Buffer* buf);
const char* containers_buffer_read(const Buffer* buf);
