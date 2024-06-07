#include "../lib.h"

void tl_fread(void* dest, size_t size, size_t num, FILE* file_ptr) {
  size_t result = fread(dest, size, 1, file_ptr);
  if (result != 1) {
    if (feof(file_ptr)) {
      fprintf(stderr, "unexpected end of file\n");
    } else if (ferror(file_ptr)) {
      fprintf(stderr, "error reading from file\n");
    }
    fclose(file_ptr);
    exit(1);
  }
}

void tl_fseek(const char* name, FILE* file, size_t offset) {
  int result = fseek(file, offset, SEEK_SET);
  if (result != 0) {
    fprintf(stderr, "error seeking in file with offset=%zu, in process='%s'", offset, name);
    exit(1);
  }
}
