#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

int **newField(int width, int height);


void freeField(int **field, int height);
void cleanField(int **field);

#endif /* UTILS_H */
