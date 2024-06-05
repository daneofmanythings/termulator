#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./tables/font_directory.h"

const char* UBUNTU_FONT_PATH = "/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf";

int main(void) {

  FILE* font_ptr = fopen(UBUNTU_FONT_PATH, "rb");
  if (font_ptr == NULL) {
    fprintf(stderr, "could not open file: %s\n", UBUNTU_FONT_PATH);
    exit(1);
  }

  font_directory_t* font_directory = font_directory_create(font_ptr);
  font_directory_print(font_directory);

  fclose(font_ptr);
  font_directory_destroy(font_directory);
  return EXIT_SUCCESS;
}
