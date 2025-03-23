#include "./include/utils.h"

#include "./include/tetris.h"

void clearField(int **field) {
  if (!field) return;

  for (int i = 0; i < FIELD_HEIGHT + 2; i++) {
    for (int j = 0; j < FIELD_WIDTH + 2; j++) {
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

  for (int i = 0; i < FIELD_HEIGHT + 2; i++) {
    for (int j = 0; j < FIELD_WIDTH + 2; j++) {
      if (tetris->game_info.field[i][j] != OBJECT_CODE_AIR &&
          tetris->game_info.field[i][j] != OBJECT_CODE_WALL) {
        tetris->game_info.field[i][j] = OBJECT_CODE_AIR;
      }
    }
  }
}
/*
int checkCollideWithWall(int x, int y) {
  return (x < 1 || x >= FIELD_WIDTH + 1 ||
          y < 1 || y >= FIELD_HEIGHT + 1);
}

int checkCollideWithBlock(Tetris_t* tetris, int x, int y) {
  return (tetris->game_info.field[y][x] != OBJECT_CODE_AIR);
}

int isCollide(Tetris_t *self, Tetramino_t *tetramino) {
  if (!tetramino || !self->game_info.field) return -1;

  int result = 0;

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
*/

int isCollide(Tetris_t *self, Tetramino_t *tetramino) {
  if (!tetramino || !self->game_info.field) {
    return -1; // Ошибка: некорректные входные данные
  }

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      if (tetramino->brick[i][j]) {
        int global_x = tetramino->x + j;
        int global_y = tetramino->y + i;

        // Проверка столкновения с границами поля
        if (global_x < 1 || global_x >= FIELD_WIDTH + 1 || global_y >= FIELD_HEIGHT + 1) {
          return 1; // Столкновение с границей
        }

        // Проверка столкновения с другими блоками
        if (global_y >= 1 && self->game_info.field[global_y][global_x] != OBJECT_CODE_AIR) {
          return 1; // Столкновение с блоком
        }
      }
    }
  }

  return 0; // Нет столкновений
}
void replaceTetramino(Tetris_t *self, Tetramino_t *tetramino) {
  if (!tetramino || !self->game_info.field) return;

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      self->curr_tetramino.brick[i][j] = tetramino->brick[i][j];
    }
  }
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

void copyTetramino(int brick_one[TETRAMINO_WIDTH][TETRAMINO_HEIGHT],
                   int brick_two[TETRAMINO_WIDTH][TETRAMINO_HEIGHT]) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      brick_one[i][j] = brick_two[i][j];
    }
  }
}

void copyTetraminoToCurr(Tetris_t *tetris, Tetramino_t *tetramino) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      tetris->curr_tetramino.brick[i][j] = tetramino->brick[i][j];
    }
  }
  tetris->curr_tetramino.x = tetramino->x;
  tetris->curr_tetramino.y = tetramino->y;
  tetris->curr_tetramino.color = tetramino->color;
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

void shiftLines(Tetris_t *self, int *index) {
  for (int k = *index; k > 1; k--) {
    for (int j = 1; j <= FIELD_WIDTH+1; j++) {
      self->game_info.field[k][j] = self->game_info.field[k - 1][j];
    }
  }
  *index += 1;
}

void clearLines(Tetris_t *self) {
  int erase_line_count = 0;
  for (int i = FIELD_HEIGHT; i > 0; i--) {
    bool erase_line = true;
    for (int j = 1; j < FIELD_WIDTH + 1; j++) {
      if (self->game_info.field[i][j] == OBJECT_CODE_AIR) {
        erase_line = false;
      }
    }
    if (erase_line) {
      erase_line_count++;
      shiftLines(self, &i);
    }
  }

  Score_t score = initScore();
  score.convertLineCountToScore(&score, erase_line_count);

  self->level.score.score += score.score;
  self->level.updateLevel(&self->level);

  self->updateScore(self);
  self->updateLevel(self);
}
