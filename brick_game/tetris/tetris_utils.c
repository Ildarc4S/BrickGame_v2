/**
 * @file tetris_collisions.c
 * @brief Functions for handling Tetramino collisions, line clearing, and
 * related processes in Tetris.
 *
 * This file contains the logic to detect collisions of Tetraminoes with the
 * game field, check for line completions, and handle the insertion and rotation
 * of Tetraminoes.
 *
 * @author Major Sweet
 * @date 2025-02-12
 */

#include "./include/tetris.h"

/**
 * @brief Gets the real brick size (minimum and maximum X, maximum Y) of a
 * Tetramino.
 *
 * This function iterates through the Tetramino's brick array and finds the
 * minimum and maximum x and y coordinates where the Tetramino has its active
 * bricks. These values are used to detect boundary collisions with the game
 * field.
 *
 * @param tetramino A pointer to the Tetramino structure.
 * @param min_x The minimum x-coordinate of the Tetramino (output).
 * @param max_x The maximum x-coordinate of the Tetramino (output).
 * @param max_y The maximum y-coordinate of the Tetramino (output).
 */
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

/**
 * @brief Checks if a Tetramino collides with other blocks on the game field.
 *
 * This function checks if the current Tetramino overlaps with any already
 * placed bricks on the game field, returning 1 (collision detected) or 0 (no
 * collision).
 *
 * @param tetris A pointer to the Tetris game state.
 * @param tetramino A pointer to the Tetramino that is being checked for
 * collisions.
 * @return 1 if a collision is detected, 0 otherwise.
 */
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

/**
 * @brief Checks for potential collisions on the sides and bottom of the
 * Tetramino.
 *
 * This function checks if the Tetramino is too close to the sides of the field
 * (left or right) or if it has reached the bottom of the field or collided with
 * another brick.
 *
 * @param tetris A pointer to the Tetris game state.
 * @param tetramino A pointer to the Tetramino to check for collisions.
 * @param min_x The minimum X coordinate of the Tetramino.
 * @param max_x The maximum X coordinate of the Tetramino.
 * @param max_y The maximum Y coordinate of the Tetramino.
 * @param collide_left_x The flag indicating if a left collision occurred
 * (output).
 * @param collide_right_x The flag indicating if a right collision occurred
 * (output).
 * @param collide_bottom_y The flag indicating if a bottom collision occurred
 * (output).
 */
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

/**
 * @brief Processes collision checks for the Tetramino.
 *
 * This function combines the results of the various collision checks (sides and
 * bottom) to determine if the Tetramino has collided with the field boundaries
 * or other blocks.
 *
 * @param tetris A pointer to the Tetris game state.
 * @param tetramino A pointer to the Tetramino being checked.
 * @param collide_left_x The left collision flag (output).
 * @param collide_right_x The right collision flag (output).
 * @param collide_bottom_y The bottom collision flag (output).
 */
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

/**
 * @brief Checks if the Tetramino collides with the game field or other bricks.
 *
 * This function determines if a Tetramino is colliding with the sides or bottom
 * of the game field or with already placed bricks. Returns 1 if there is a
 * collision, 0 otherwise.
 *
 * @param tetris A pointer to the Tetris game state.
 * @param tetramino A pointer to the Tetramino to check.
 * @return 1 if a collision is detected, 0 otherwise.
 */
int isCollide(Tetris_t *tetris, Tetramino_t *tetramino) {
  int collide_left_x = 0;
  int collide_right_x = 0;
  int collide_bottom_y = 0;
  collideProcess(tetris, tetramino, &collide_left_x, &collide_right_x,
                 &collide_bottom_y);

  return collide_left_x || collide_right_x || collide_bottom_y;
}

/**
 * @brief Replaces the current Tetramino with a new one.
 *
 * This function updates the current Tetramino in the game state with the
 * properties of a new Tetramino. This is used to update the position and shape
 * of the Tetramino after movement or rotation.
 *
 * @param tetris A pointer to the Tetris game state.
 * @param tetramino A pointer to the new Tetramino to replace the current one.
 */
void replaceTetramin(Tetris_t *tetris, Tetramino_t *tetramino) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_HEIGHT; j++) {
      tetris->info.curr_tetramino->brick[i][j] = tetramino->brick[i][j];
    }
  }
  tetris->info.curr_tetramino->x = tetramino->x;
  tetris->info.curr_tetramino->y = tetramino->y;
}

/**
 * @brief Inserts the current Tetramino into the game field.
 *
 * This function "locks" the current Tetramino into its position on the game
 * field. It places the Tetramino's bricks into the corresponding positions in
 * the game field matrix.
 *
 * @param tetris A pointer to the Tetris game state.
 */
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

/**
 * @brief Copies the brick array from one Tetramino to another.
 *
 * This function copies the brick structure of one Tetramino to another,
 * preserving its shape and layout.
 *
 * @param brick_one A 4x4 array to store the copied brick data.
 * @param brick_two A 4x4 array to copy from.
 */
void copyBrick(int brick_one[TETRAMINO_WIDTH][TETRAMINO_HEIGHT],
               int brick_two[TETRAMINO_WIDTH][TETRAMINO_HEIGHT]) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      brick_one[i][j] = brick_two[i][j];
    }
  }
}

/**
 * @brief Rotates a Tetramino 90 degrees clockwise.
 *
 * This function rotates the Tetramino's brick array by 90 degrees, transforming
 * its shape accordingly. It uses a temporary array to store the rotated version
 * of the brick structure.
 *
 * @param tetramino A pointer to the Tetramino to rotate.
 */
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

/**
 * @brief Shifts lines in the Tetris game field after clearing a line.
 *
 * This function shifts all the rows above a cleared line one step downward to
 * fill in the gap created by the cleared line. It also updates the line index.
 *
 * @param this A pointer to the Tetris game state.
 * @param index A pointer to the index of the line to shift.
 */
void shiftLines(Tetris_t *this, int *index) {
  for (int k = *index; k > 1; k--) {
    for (int j = 1; j <= FIELD_WIDTH; j++) {
      this->info.game_info.field[k][j] = this->info.game_info.field[k - 1][j];
    }
  }
  *index += 1;
}

/**
 * @brief Clears completed lines from the Tetris game field.
 *
 * This function checks for completed lines (lines fully filled with bricks) and
 * clears them. After clearing, it shifts all lines above downward. It also
 * updates the score based on the number of lines cleared.
 *
 * @param this A pointer to the Tetris game state.
 */
void cleanLines(Tetris_t *this) {
  int erase_line_count = 0;
  for (int i = FIELD_HEIGHT; i > 0; i--) {
    int erase_line = 1;
    for (int j = 1; j < FIELD_WIDTH + 1; j++) {
      if (this->info.game_info.field[i][j] == 0) {
        erase_line =
            0;  ///< If any empty space is found, the line is not complete.
      }
    }
    if (erase_line) {
      erase_line_count++;
      shiftLines(this, &i);
    }
  }

  Score_t score = constructorScore();
  score.convertLineCountToScore(&score, erase_line_count);

  this->level.setScore(&this->level, &score);
  this->level.updateLevel(&this->level);

  this->updateScore(this);
  this->updateLevel(this);
}
