#include <endian.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

const char* UBUNTU_FONT_PATH = "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf";

typedef struct be_ttf_header {
  uint32_t scalar_type;
  uint16_t num_tables;
  uint16_t search_range;
  uint16_t entry_selector;
  uint16_t range_shift;
} be_ttf_header_t;

typedef struct ttf_header {
  uint32_t scalar_type;
  uint16_t num_tables;
  uint16_t search_range;
  uint16_t entry_selector;
  uint16_t range_shift;
} ttf_header_t;

static ttf_header_t* be_to_host_ttf_header(be_ttf_header_t* be_header) {
  ttf_header_t* header = (ttf_header_t*)malloc(sizeof(ttf_header_t));
  if (header == NULL) {
    fprintf(stderr, "be_to_host_ttf_header::malloc::header\n");
    return NULL;
  }

  header->scalar_type = be32toh(be_header->scalar_type);
  header->num_tables = be16toh(be_header->num_tables);
  header->search_range = be16toh(be_header->search_range);
  header->entry_selector = be16toh(be_header->entry_selector);
  header->range_shift = be16toh(be_header->range_shift);

  return header;
}

void print_bits(uint32_t num) {
  u_char bit_count = sizeof(num) * 8;
  for (size_t i = 0; i < bit_count; i++) {
    if (i % 8 == 0) {
      printf("|");
    }
    printf("%d", (num >> (bit_count - i - 1)) & 1);
  }
  printf("|\n");
}

int main(void) {
  // uint32_t a = 0;
  //
  // a |= 31;
  // a <<= 24;
  //
  // print_bits(a);
  // a = be32toh(a);
  // print_bits(a);

  FILE* font_ptr = fopen(UBUNTU_FONT_PATH, "rb");
  if (font_ptr == NULL) {
    errno = ENOENT;
    fprintf(stderr, "could not open file\n");
    return EXIT_FAILURE;
  }

  be_ttf_header_t be_header;
  size_t result = fread(&be_header, sizeof(be_ttf_header_t), 1, font_ptr);
  if (result != 1) {
    if (feof(font_ptr)) {
      fprintf(stderr, "unexpected end of file\n");
    } else if (ferror(font_ptr)) {
      fprintf(stderr, "error reading from file\n");
    }
    fclose(font_ptr);
    return EXIT_FAILURE;
  }

  ttf_header_t* header = be_to_host_ttf_header(&be_header);
  printf("scalar_type: 0x%08x\n", header->scalar_type);
  printf("num_tables: %d\n", header->num_tables);
  printf("search_range: %d\n", header->search_range);
  printf("entry_selector: %d\n", header->entry_selector);
  printf("range_shift: %d\n", header->range_shift);

  free(header);
  fclose(font_ptr);
  return EXIT_SUCCESS;
}
