#ifndef SRC_LIB_H
#define SRC_LIB_H

#include <stdio.h>
#include <stdlib.h>

void tl_fread(void* dest, size_t size, size_t num, FILE* file_ptr);
void tl_fseek(const char* name, FILE* file, size_t offset);

#endif // !DEBUG
