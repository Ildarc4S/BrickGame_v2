#include "./include/tetramino_collection.h"
#include <stdlib.h>

void initAllTetraminoCollectionBricks(TetraminoCollection_t *self) {
  Tetramino_t tetramino_i = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_RED,
      .brick = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_o = {
      .x = 0,
      .y = 0,
      .color = (Color_t)OBJECT_CODE_TETRAMINO_O,
      .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_t = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_BLUE,
      .brick = {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_s = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_GREEN,
      .brick = {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_z = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_DARK_MAGNETA,
      .brick = {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_j = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_DARK_YELLOW,
      .brick = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};

  Tetramino_t tetramino_l = {
      .x = 0,
      .y = 0,
      .color = TETRAMINO_COLOR_YELLOW,
      .brick = {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};
  
  self->tetraminos[0] = tetramino_i;
  self->tetraminos[1] = tetramino_o;
  self->tetraminos[2] = tetramino_t;
  self->tetraminos[3] = tetramino_s;
  self->tetraminos[4] = tetramino_z;
  self->tetraminos[5] = tetramino_j;
  self->tetraminos[6] = tetramino_l;
}

Tetramino_t* _getRandomTetramino(TetraminoCollection_t *self) {
  int rand_index = rand() % self->size;
  return &self->tetraminos[rand_index];
}

TetraminoCollection_t initTetraminoCollection() {
  TetraminoCollection_t collection =  {
    .size = TETRAMINO_COLLCECTION_SIZE,
    .getRandomTetranimo = _getRandomTetramino
  };

  initAllTetraminoCollectionBricks(&collection);
  return collection;
}

