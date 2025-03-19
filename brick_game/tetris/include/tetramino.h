#ifndef TETRAMINO_H
#define TETRAMINO_H

#include "./color.h"

#define TETRAMINO_WIDTH 4
#define TETRAMINO_HEIGHT 4

typedef struct {
  int x;
  int y;
  Color_t color;
  int brick[TETRAMINO_HEIGHT][TETRAMINO_WIDTH];
} Tetramino_t;

#endif  // TETRAMINO_H
