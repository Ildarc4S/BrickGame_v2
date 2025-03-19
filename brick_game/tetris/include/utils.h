#ifndef UTILS_H
#define UTILS_H

#include "./tetris.h"

void clearField(int** field);
void clearTetraminoFromField(Tetris_t* tetris);
int isCollide(Tetris_t *tetris, Tetramino_t *tetramino);

void replaceTetramino(Tetris_t *self, Tetramino_t *tetramino);
void insertTetraminoToField(Tetris_t *self);
void copyTetramino(int brick_one[TETRAMINO_WIDTH][TETRAMINO_HEIGHT],
                   int brick_two[TETRAMINO_WIDTH][TETRAMINO_HEIGHT]);
void rotateTetramino(Tetramino_t *tetramino);
void shiftLines(Tetris_t *self, int *index);
void clearLines(Tetris_t *self);

#endif  // UTILS_H

