#include "./include/tetris.h"

void getRealBrickSize(Tetramino_t *tetramino, int *min_x, int *max_x,
                      int *max_y) {
  *min_x = TETRAMINO_WIDTH;  ///< Initialize minimum X to 4 (the highest
                             ///< possible value in the Tetramino).
  *max_x = -1;  ///< Initialize maximum X to -1 (the lowest possible value in
                ///< the Tetramino).
  *max_y = -1;  ///< Initialize maximum Y to -1 (the lowest possible value in
                ///< the Tetramino).

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      if (tetramino->brick[i][j]) {  // If the current cell contains a part of
                                     // the brick
        if (j < *min_x) *min_x = j;  // Find the leftmost x-coordinate
        if (j > *max_x) *max_x = j;  // Find the rightmost x-coordinate
        if (i > *max_y) *max_y = i;  // Find the bottommost y-coordinate
      }
    }
  }
}

int checkCollideOtherBreak(Tetris_t *tetris, Tetramino_t *tetramino) {
  int result_code = 0;
  int x = tetramino->x;
  int y = tetramino->y;

  // Loop through the brick array of the Tetramino and check if any of its
  // blocks collide
  for (int i = 0; i < TETRAMINO_HEIGHT && !result_code; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH && !result_code; j++) {
      if (tetramino->brick[i][j]) {
        int field_x = x + j;
        int field_y = y + i;

        // If a brick from the Tetramino overlaps a filled position on the
        // field, it's a collision
        if (tetris->info.game_info.field[field_y][field_x]) {
          result_code = 1;  ///< Set result to 1 (collision detected).
        }
      }
    }
  }
  return result_code;
}

void checkCollideSide(Tetris_t *tetris, Tetramino_t *tetramino, int min_x,
                      int max_x, int max_y, int *collide_left_x,
                      int *collide_right_x, int *collide_bottom_y) {
  if (min_x <= 0) {
    *collide_left_x = 1;  ///< Set left collision flag if Tetramino is at or
                          ///< beyond the left edge.
  }

  if (max_x >= FIELD_WIDTH + 1) {
    *collide_right_x = 1;  ///< Set right collision flag if Tetramino is at or
                           ///< beyond the right edge.
  }

  if (max_y >= FIELD_HEIGHT + 1 || checkCollideOtherBreak(tetris, tetramino)) {
    *collide_bottom_y =
        1;  ///< Set bottom collision flag if Tetramino is at or beyond the
            ///< bottom edge or collides with another block.
  }
}

void collideProcess(Tetris_t *tetris, Tetramino_t *tetramino,
                    int *collide_left_x, int *collide_right_x,
                    int *collide_bottom_y) {
  int min_x = 0;
  int max_x = 0;
  int max_y = 0;

  getRealBrickSize(tetramino, &min_x, &max_x, &max_y);

  max_x = tetramino->x + max_x;  ///< Adjust max_x to reflect the Tetramino's
                                 ///< position on the field.
  min_x = tetramino->x + min_x;  ///< Adjust min_x similarly.
  max_y = tetramino->y + max_y;  ///< Adjust max_y similarly.

  checkCollideSide(tetris, tetramino, min_x, max_x, max_y, collide_left_x,
                   collide_right_x, collide_bottom_y);
}


int isCollide(Tetris_t *tetris, Tetramino_t *tetramino) {
  int collide_left_x = 0;
  int collide_right_x = 0;
  int collide_bottom_y = 0;
  collideProcess(tetris, tetramino, &collide_left_x, &collide_right_x,
                 &collide_bottom_y);

  return collide_left_x || collide_right_x || collide_bottom_y;
}

void replaceTetramin(Tetris_t *tetris, Tetramino_t *tetramino) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      tetris->info.curr_tetramino->brick[i][j] = tetramino->brick[i][j];
    }
  }
  tetris->info.curr_tetramino->x = tetramino->x;
  tetris->info.curr_tetramino->y = tetramino->y;
}

void insertBrick(Tetris_t *tetris) {
  int x = tetris->info.curr_tetramino->x;
  int y = tetris->info.curr_tetramino->y;

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      if (tetris->info.curr_tetramino->brick[i][j]) {
        tetris->info.game_info.field[y + i][x + j] =
            tetris->info.curr_tetramino->brick[i][j];
      }
    }
  }
}

void copyBrick(int brick_one[TETRAMINO_WIDTH][TETRAMINO_HEIGHT],
               int brick_two[TETRAMINO_WIDTH][TETRAMINO_HEIGHT]) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      brick_one[i][j] = brick_two[i][j];
    }
  }
}

void rotateTetramino(Tetramino_t *tetramino) {
  int temp[TETRAMINO_WIDTH][TETRAMINO_HEIGHT];
  copyBrick(temp, tetramino->brick);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      temp[j][TETRAMINO_WIDTH - i - 1] = tetramino->brick[i][j];
    }
  }
  copyBrick(tetramino->brick, temp);
}

void shiftLines(Tetris_t *self, int *index) {
  for (int k = *index; k > 1; k--) {
    for (int j = 1; j <= FIELD_WIDTH; j++) {
      self->info.game_info.field[k][j] = self->info.game_info.field[k - 1][j];
    }
  }
  *index += 1;
}

void cleanLines(Tetris_t *self) {
  int erase_line_count = 0;
  for (int i = FIELD_HEIGHT; i > 0; i--) {
    int erase_line = 1;
    for (int j = 1; j < FIELD_WIDTH + 1; j++) {
      if (self->info.game_info.field[i][j] == 0) {
        erase_line =
            0;  ///< If any empty space is found, the line is not complete.
      }
    }
    if (erase_line) {
      erase_line_count++;
      shiftLines(self, &i);
    }
  }

  Score_t score = initScore();
  score.convertLineCountToScore(&score, erase_line_count);

  self->level.score = score;
  self->level.updateLevel(&self->level);

  self->updateScore(self);
  self->updateLevel(self);
}
