#include "./include/utils.h"
#include "./include/tetris.h"

void clearField(int **field) {
  if (!field) return;

  for (int i = 0; i < FIELD_HEIGHT + FIELD_BORDER; i++) {
    for (int j = 0; j < FIELD_WIDTH + FIELD_BORDER; j++) {
      if (i == 0 || j == 0 || i == FIELD_HEIGHT + 1 || j == FIELD_WIDTH + 1) {
        field[i][j] = OBJECT_CODE_WALL;
      } else {
        field[i][j] = OBJECT_CODE_AIR;
      }
    }
  }
}

void clearTetraminoFromField(Tetris_t *tetris) {
  if (!tetris->game_info.field) return;

  for (int i = 0; i < FIELD_HEIGHT + FIELD_BORDER; i++) {
    for (int j = 0; j < FIELD_WIDTH + FIELD_BORDER; j++) {
      if (tetris->game_info.field[i][j] != OBJECT_CODE_AIR &&
          tetris->game_info.field[i][j] != OBJECT_CODE_WALL) {
        tetris->game_info.field[i][j] = OBJECT_CODE_AIR;
      }
    }
  }
}

int checkCollideWithWall(int x, int y) {
  return (x < 1 || x >= FIELD_WIDTH + 1 || y >= FIELD_HEIGHT + 1);
}

static int checkCollideWithBlock(Tetris_t *self, int x, int y) {
  if (y < 1 || !self || !self->game_info.field) return UTILS_NOT_COLLIDE;
  return (self->game_info.field[y][x] != OBJECT_CODE_AIR);
}

int isCollide(Tetris_t *self, Tetramino_t *tetramino) {
  if (!tetramino || !self || !self->game_info.field) return UTILS_ERROR;
  
  int result = UTILS_NOT_COLLIDE;
  for (int i = 0; i < TETRAMINO_HEIGHT && !result; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH && !result; j++) {
      if (tetramino->brick[i][j]) {
        int global_x = tetramino->x + j;
        int global_y = tetramino->y + i;
        result = checkCollideWithWall(global_x, global_y) || checkCollideWithBlock(self, global_x, global_y);
      }
    }
  }
  return result;
}

void copyBrick(int dest[TETRAMINO_HEIGHT][TETRAMINO_WIDTH],
               int src[TETRAMINO_HEIGHT][TETRAMINO_WIDTH]) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

void copyTetramino(int brick_one[TETRAMINO_HEIGHT][TETRAMINO_WIDTH],
                   int brick_two[TETRAMINO_HEIGHT][TETRAMINO_WIDTH]) {
  copyBrick(brick_one, brick_two);
}

void copyTetraminoToCurrentTetramino(Tetris_t *tetris, Tetramino_t *tetramino) {
  if (!tetramino) return;

  copyBrick(tetris->curr_tetramino.brick, tetramino->brick);
  tetris->curr_tetramino.x = tetramino->x;
  tetris->curr_tetramino.y = tetramino->y;
  tetris->curr_tetramino.color = tetramino->color;
}

void replaceTetramino(Tetris_t *self, Tetramino_t *tetramino) {
  if (!tetramino || !self->game_info.field) return;

  copyBrick(self->curr_tetramino.brick, tetramino->brick);
  self->curr_tetramino.x = tetramino->x;
  self->curr_tetramino.y = tetramino->y;
}

void insertTetraminoToField(Tetris_t *self) {
  if (!self->game_info.field) return;

  int x = self->curr_tetramino.x;
  int y = self->curr_tetramino.y;

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      if (self->curr_tetramino.brick[i][j]) {
        self->game_info.field[y + i][x + j] = OBJECT_CODE_WALL;
      }
    }
  }
}

void rotateTetramino(Tetramino_t *tetramino) {
  int temp[TETRAMINO_WIDTH][TETRAMINO_HEIGHT];
  copyTetramino(temp, tetramino->brick);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      temp[j][TETRAMINO_WIDTH - i - 1] = tetramino->brick[i][j];
    }
  }
  copyTetramino(tetramino->brick, temp);
}

void shiftLines(Tetris_t *tetris, int *index) {
  for (int k = *index; k > 1; k--) {
    for (int j = 1; j <= FIELD_WIDTH+1; j++) {
      tetris->game_info.field[k][j] = tetris->game_info.field[k - 1][j];
    }
  }
  *index += 1;
}

#include <ncurses.h>

int countEraseLines(Tetris_t* tetris) {
  int erase_line_count = 0;
  for (int i = FIELD_HEIGHT; i > 0; i--) {
    bool erase_line = true;
    for (int j = 1; j < FIELD_WIDTH + 1; j++) {
      if (tetris->game_info.field[i][j] == OBJECT_CODE_AIR) {
        erase_line = false;
      }
    }
    if (erase_line) {
      mvprintw(25, 15, "Da");
      erase_line_count++;
      shiftLines(tetris, &i);
    }
  }
  return erase_line_count;
}

void updateScoreAndLeve(Tetris_t* tetris, int erase_line_count) {
  tetris->level.score.convertLineCountToScore(&tetris->level.score, erase_line_count);
  tetris->level.updateLevel(&tetris->level);

  tetris->updateScore(tetris);
  tetris->updateLevel(tetris);
}

void clearLines(Tetris_t *self) {
  int erase_line_count = countEraseLines(self);
  if (erase_line_count) {
    updateScoreAndLeve(self, erase_line_count);
  }
}

void moveHorizontal(Tetris_t* tetris, int direction) {
    if (!tetris) {
      return; 
    }

  Tetramino_t *tetramino = &tetris->curr_tetramino;
  tetramino->x += direction;
  if (isCollide(tetris, tetramino)) {
    tetramino->x -=direction;
  }
  replaceTetramino(tetris, tetramino);
}

void insertTetraminoToFieldWithColor(Tetris_t *self) {
  if (!self->game_info.field) return;

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      if (self->curr_tetramino.brick[i][j]) {
        int x = self->curr_tetramino.x + j;
        int y = self->curr_tetramino.y + i;
        if (x >= 1 && x < FIELD_WIDTH + 1 && y >= 1 && y < FIELD_HEIGHT + 1) {
          self->game_info.field[y][x] = self->curr_tetramino.color;
        }
      }
    }
  }
}

