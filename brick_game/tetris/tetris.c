#include "./include/tetris.h"
#include "./include/utils.h"
#include "./include/memory_utils.h"

void _restoreInfo(Tetris_t* self) {
  clearField(self->game_info.field);

  self->timer.tick = 1000;
  self->level.level = 1;
  self->level.score.score = 0;

  self->game_info.level = 1;
  self->game_info.score = 0;

  self->game_info.speed = 10;
}

void _startGame(Tetris_t *self) {
  if (self->state == TETRIS_STATE_START) {
    self->spawn(self);
    self->game_info.high_score = self->db.read(&self->db);
  } else if (self->state == TETRIS_STATE_PAUSE) {
    self->state = TETRIS_STATE_MOVE;
  } else if (self->state == TETRIS_STATE_GAME_OVER) {
    self->restoreInfo(self);
    self->spawn(self);
  }
  self->game_info.pause = PAUSE_MODE_CONTINUE;
}

void printF(int** field) {
  if(!field) return;
  for (int i = 0; i < FIELD_HEIGHT+2; i++) { 
    for (int j = 0; j < FIELD_WIDTH+2; j++) { 
      printf("%+d ", field[i][j]);
    }
    printf("\n");
  }
}

void printT(Tetramino_t* t) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) { 
    for (int j = 0; j < TETRAMINO_WIDTH; j++) { 
      printf("%+d ", t->brick[i][j]);
    }
    printf("\n");
  }
  printf("Coord: (%d, %d)\n", t->x, t->y);
}

void _spawn(Tetris_t *self) {
  if (!self) {
    return;
  }

  if (!self->next_tetramino) {
    self->next_tetramino = self->collection.getRandomTetranimo(&self->collection);
  }

  self->curr_tetramino = self->next_tetramino;
  self->curr_tetramino->x = FIELD_WIDTH / 2;
  self->curr_tetramino->y = 1;

  self->next_tetramino = self->collection.getRandomTetranimo(&self->collection);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      self->game_info.next[i][j] = OBJECT_CODE_AIR;
      if (self->next_tetramino->brick[i][j]) {
        self->game_info.next[i][j] = self->next_tetramino->color;
      }
    }
  }

  self->state = TETRIS_STATE_MOVE;

  if (isCollide(self, self->curr_tetramino)) {
    self->game_info.pause = PAUSE_MODE_GAME_OVER;
    self->db.write(&self->db, self->game_info.high_score);
    self->state = TETRIS_STATE_GAME_OVER;
  }

}

void _left(Tetris_t* self, bool hold) {
  if (!self) {
    return;
  }
  (void)hold;

  Tetramino_t *tetramino = self->curr_tetramino;
  tetramino->x--;
  if (isCollide(self, tetramino)) {
    tetramino->x++;
  }
  replaceTetramino(self, tetramino);

}

void _right(Tetris_t *tetris, bool hold) {
  if (!tetris) {
    return;
  }
  (void)hold;

  Tetramino_t *tetramino = tetris->curr_tetramino;
  tetramino->x++;
  if (isCollide(tetris, tetramino)) {
    tetramino->x--;
  }
  replaceTetramino(tetris, tetramino);
}

void _up(Tetris_t *self, bool hold) {
  if (!self) {
    return;
  }
  (void)hold;
}

void _down(Tetris_t *self, bool hold) {
  if (!self || !self->curr_tetramino) {
    return;
  }

  Tetramino_t *tetramino = self->curr_tetramino;
  bool is_collide = false;

  if (hold) {
    tetramino->y++;
    if (isCollide(self, tetramino)) {
      is_collide = true;
      tetramino->y--;
    }
  } else {
    while (!isCollide(self, tetramino)) {
      tetramino->y++;
    }
    tetramino->y--;
    is_collide = true;
  }

  replaceTetramino(self, tetramino);

  if (is_collide) {
    self->state = TETRIS_STATE_ATTACH;
    insertTetraminoToField(self);
    self->curr_tetramino = NULL;
  }
}

void _action(Tetris_t *tetris, bool hold) {
  if (!tetris) {
    return;
  }
  (void)hold;

  Tetramino_t *tetramino = tetris->curr_tetramino;
  int temp_tetramino[TETRAMINO_WIDTH][TETRAMINO_HEIGHT];
  copyTetramino(temp_tetramino, tetramino->brick);
  rotateTetramino(tetramino);

  if (isCollide(tetris, tetramino)) {
    copyTetramino(tetramino->brick, temp_tetramino);
  }
}

void _updateTetrisScore(Tetris_t *self) {
  self->game_info.score = self->level.score.score;
  if (self->game_info.score >= self->game_info.high_score) {
    self->game_info.high_score = self->game_info.score;
  }
}

void _updateTetrisLevel(Tetris_t *self) {
  long tick = self->timer.tick;
  if (self->level.level > self->game_info.level && tick >= self->timer.default_tick /*80*/) {
    self->game_info.speed += self->speed_diff;
    self->timer.tick -= self->tick_diff;
  }
  self->game_info.level = self->level.level;
}

void insertTetraminoToFieldWithColor(Tetris_t* self) {
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      if (self->curr_tetramino && self->curr_tetramino->brick[i][j]) {
        int x = self->curr_tetramino->x + j;
        int y = self->curr_tetramino->y + i;
        self->game_info.field[y][x] = self->curr_tetramino->color;
      }
    }
  }
}

void _updateTetrisState(Tetris_t* self) {
  clearTetraminoFromField(self);
  if (self->state == TETRIS_STATE_MOVE) {
    if (self->timer.calcDiff(&self->timer) >= self->timer.tick) {
      self->down(self, true);
      self->timer.updateLastTime(&self->timer);
    }
  } else if (self->state == TETRIS_STATE_ATTACH) {
    clearLines(self);
    self->spawn(self);
  }
  
  insertTetraminoToFieldWithColor(self);
}

void _pauseGame(Tetris_t *tetris) {
  tetris->game_info.pause = PAUSE_MODE_Pause;
  tetris->state = TETRIS_STATE_PAUSE;
}

void _exitGame(Tetris_t *self) {
  self->db.write(&self->db, self->game_info.high_score);
  self->game_info.pause = PAUSE_MODE_EXIT;
  self->state = TETRIS_STATE_EXIT;
}


Tetris_t constructorTetris() {
  Tetris_t self = (Tetris_t) {
    .state = TETRIS_STATE_START,
    .game_info = {.field = newField(FIELD_WIDTH + 2, FIELD_HEIGHT + 2),
                    .next = newField(TETRAMINO_WIDTH, TETRAMINO_HEIGHT),
                    .score = 0,
                    .high_score = 0,
                    .level = 1,
                    .speed = 0,
                    .pause = PAUSE_MODE_START},
    .curr_tetramino = NULL,
    .next_tetramino = NULL,
    .collection = initTetraminoCollection(),
   
    .timer = initTimer(),
    .level = initLevel(),
    .db = initDataBase("tetris_db.txt"),
    .speed_diff = 10,
    .tick_diff = 70,

    .start = _startGame,
    .spawn = _spawn,
    .action = _action,
    .left = _left,
    .right = _right,
    .up = _up,
    .down = _down,
    .pause = _pauseGame,
    .exit = _exitGame,
    .restoreInfo = _restoreInfo,
    .updateScore = _updateTetrisScore,
    .updateLevel = _updateTetrisLevel,
    .updateTetrisState = _updateTetrisState};
  _restoreInfo(&self);
  clearField(self.game_info.field);
  return self;
}

Tetris_t* initTetris() {
    static Tetris_t tetris;
    static bool initialized = false;

    if (!initialized) {
        tetris = constructorTetris();
        initialized = true;
    }

    return &tetris;
}
