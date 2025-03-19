#ifndef TETRAMINO_COLLCECTION
#define TETRAMINO_COLLCECTION

#include "./tetramino.h"
#include <stdlib.h>

#define TETRAMINO_COLLCECTION_SIZE 7

typedef struct _tetramino_collection {
  Tetramino_t tetraminos[TETRAMINO_COLLCECTION_SIZE];
  int size_;
  Tetramino_t *(*getRandomTetranimo)(struct _tetramino_collection *);
} TetraminoCollection_t;

TetraminoCollection_t initTetraminoCollection();

#endif  // TETRAMINO_COLLCECTION
