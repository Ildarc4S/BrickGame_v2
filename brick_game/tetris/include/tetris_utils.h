#ifndef TETRIS_UTILS_H
#define TETRIS_UTILS_H

#include "./tetris.h"

void getRealBrickSize(Tetramino_t *tetramino, int *min_x, int *max_x,
                      int *max_y);
int checkCollideOtherBreak(Tetris_t *tetris, Tetramino_t *tetramino);
void checkCollideSide(Tetris_t *tetris, Tetramino_t *tetramino, int min_x,
                      int max_x, int max_y, int *collide_left_x,
                      int *collide_right_x, int *collide_bottom_y);
void collideProcess(Tetris_t *tetris, Tetramino_t *tetramino,
                    int *collide_left_x, int *collide_right_x,
                    int *collide_bottom_y);
int isCollide(Tetris_t *tetris, Tetramino_t *tetramino);

void replaceTetramin(Tetris_t *tetris, Tetramino_t *tetramino);
void insertBrick(Tetris_t *tetris);
void copyBrick(int brick_one[TETRAMINO_HEIGHT][TETRAMINO_WIDTH],
               int brick_two[TETRAMINO_HEIGHT][TETRAMINO_WIDTH]);
void rotateTetramino(Tetramino_t *tetramino);

void shiftLines(Tetris_t *self, int *index);
void cleanLines(Tetris_t *self);

#endif  // TETRIS_UTILS_H
