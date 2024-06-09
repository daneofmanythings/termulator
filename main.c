#include <stdlib.h>

#include "./src/ttf_loader.h"

// static const char* FONT_PATH = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf";
static const char* FONT_PATH = "/home/dane/.local/share/fonts/JetBrainsMonoNLNerdFont-Regular.ttf";

int main(void) {

  FILE* font_file = fopen(FONT_PATH, "rb");
  if (font_file == NULL) {
    fprintf(stderr, "could not open file: %s\n", FONT_PATH);
    exit(1);
  }
  ttf_font_data_t* font_data = ttf_font_data_load_from_file(font_file);

  ttf_font_data_destroy(font_data);
  return EXIT_SUCCESS;
}
