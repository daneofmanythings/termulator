#include <stdlib.h>

#include "./src/ttf_loader.h"
#include "./src/ttf_loader/tables/font_directory.h"

static const char* FONT_PATH = "/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf";

int main(void) {

  FILE* font_file = fopen(FONT_PATH, "rb");
  if (font_file == NULL) {
    fprintf(stderr, "could not open file: %s\n", FONT_PATH);
    exit(1);
  }
  ttf_font_data_t* font_data = ttf_font_data_load_from_file(font_file);
  font_directory_print(font_data->font_directory);

  ttf_font_data_destroy(font_data);
  return EXIT_SUCCESS;
}
