#ifndef MEMORY_UTILS_H 
#define MEMORY_UTILS_H 

#include "./tetris.h"
#include <stdlib.h>

int **newField(int width, int height);
void freeField(int ***field, int height);

#endif  // MEMORY_UTILS_H 

