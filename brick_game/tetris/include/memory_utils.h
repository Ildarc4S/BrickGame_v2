#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdlib.h>

#define MEMORY_UTIL_ERROR 1
#define MEMORY_UTIL_OK 0

int **newField(int width, int height);
void freeField(int ***field, int height);

#endif  // MEMORY_UTILS_H
