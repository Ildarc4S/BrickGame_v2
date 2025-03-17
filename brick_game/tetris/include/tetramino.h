#ifndef TETRAMINO_H
#define TETRAMINO_H

#include <stdlib.h>

#define TETRAMINO_WIDTH 4
#define TETRAMINO_HEIGHT 4

typedef enum {
  TETRAMINO_COLOR_RED = 2, /**< Red color for Tetramino */
  TETRAMINO_COLOR_YELLOW,  /**< Yellow color for Tetramino */
  TETRAMINO_COLOR_CYAN,    /**< Cyan color for Tetramino */
  TETRAMINO_COLOR_BLUE,    /**< Blue color for Tetramino */
  TETRAMINO_COLOR_GREEN,   /**< Green color for Tetramino */
  TETRAMINO_COLOR_MAGNETA, /**< Magenta color for Tetramino */
} Color;

typedef struct {
  int x;
  int y;
  Color color;
  int brick[TETRAMINO_HEIGHT][TETRAMINO_WIDTH];
} Tetramino_t;

#endif  // TETRAMINO_H
