#ifndef TETRAMINO_COLLECTION_H
#define TETRAMINO_COLLECTION_H

#include "./tetramino.h"

#define TETRAMINO_COLLCECTION_SIZE 7

typedef struct _tetramino_collection {
  Tetramino_t tetraminos[TETRAMINO_COLLCECTION_SIZE];
  int size;
  Tetramino_t *(*getRandomTetranimo)(struct _tetramino_collection *);
} TetraminoCollection_t;

TetraminoCollection_t initTetraminoCollection();

#endif  // TETRAMINO_COLLECTION_H
