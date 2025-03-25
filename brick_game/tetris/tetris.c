#include "./include/tetris.h"

#include "./include/memory_utils.h"
#include "./include/utils.h"
#include "./include/init_utils.h"

void _restoreInfo(Tetris_t *self) {
  clearField(self->game_info.field);

  self->timer.tick = TIMER_INITIAL_TICK_INTERVAL;
  self->level.level = LEVEL_MANAGER_INITIAL_LEVEL;
  self->level.score.score = LEVEL_MANAGER_INITIAL_SCORE;

  self->game_info.level = LEVEL_MANAGER_INITIAL_LEVEL;
  self->game_info.score = LEVEL_MANAGER_INITIAL_SCORE;

  self->game_info.speed = TETRIS_INITIAL_SPEED;
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

void _spawn(Tetris_t *self) {
  if (!self) {
    return;
  }

  if (!self->next_tetramino) {
    self->next_tetramino =
        self->collection.getRandomTetranimo(&self->collection);
  }

  copyTetraminoToCurrentTetramino(self, self->next_tetramino);
  self->curr_tetramino.y = TETRIS_TETRAMINO_SPAWN_Y;
  self->curr_tetramino.x = TETRIS_TETRAMINO_SPAWN_X;

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

  if (isCollide(self, &self->curr_tetramino)) {
    self->game_info.pause = PAUSE_MODE_GAME_OVER;
    self->db.write(&self->db, self->game_info.high_score);
    self->state = TETRIS_STATE_GAME_OVER;
  }
}


void _left(Tetris_t *self, bool hold) {
  if (!self) {
    return;
  }
  (void)hold;
  moveHorizontal(self, TETRIS_TETRAMINO_LEFT_DIRECTION);
}

void _right(Tetris_t *self, bool hold) {
  if (!self) {
    return;
  }
  (void)hold;

  moveHorizontal(self, TETRIS_TETRAMINO_RIGHT_DIRECTION);
}

void _up(Tetris_t *self, bool hold) {
  if (!self) {
    return;
  }
  (void)hold;
}

void _down(Tetris_t *self, bool hold) {
  if (!self) {
    return;
  }

  Tetramino_t *tetramino = &self->curr_tetramino;
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
  }
}

void _action(Tetris_t *tetris, bool hold) {
  if (!tetris) {
    return;
  }
  (void)hold;

  Tetramino_t *tetramino = &tetris->curr_tetramino;
  int temp_tetramino[TETRAMINO_HEIGHT][TETRAMINO_WIDTH];
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
  if (self->level.level > self->game_info.level &&
      tick >= self->timer.default_tick) {
    self->game_info.speed += self->speed_diff;
    self->timer.tick -= self->tick_diff;
  }
  self->game_info.level = self->level.level;
}

void _updateTetrisState(Tetris_t *self) {
  clearTetraminoFromField(self);
  if (self->state == TETRIS_STATE_MOVE) {
    if (self->timer.calcDiff(&self->timer) >= self->timer.tick) {
      self->down(self, true);
      self->timer.updateLastTime(&self->timer);
    }
  } 
  if (self->state == TETRIS_STATE_ATTACH) {
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

  freeField(&self->game_info.field, FIELD_HEIGHT + FIELD_BORDER);
  freeField(&self->game_info.next, TETRAMINO_HEIGHT);

  self->next_tetramino = NULL;
}

void assignFunctionPointers(Tetris_t *self) {
    self->start = _startGame;
    self->spawn = _spawn;
    self->action = _action;
    self->left = _left;
    self->right = _right;
    self->up = _up;
    self->down = _down;
    self->pause = _pauseGame;
    self->exit = _exitGame;
    self->restoreInfo = _restoreInfo;
    self->updateScore = _updateTetrisScore;
    self->updateLevel = _updateTetrisLevel;
    self->updateTetrisState = _updateTetrisState;
}

Tetris_t constructorTetris() {
    Tetris_t self = (Tetris_t){
        .state = TETRIS_STATE_START,
        .game_info = initGameInfo(),
        .curr_tetramino = initCurrentTetramino(),
        .next_tetramino = NULL,
        .collection = initTetraminoCollection(),
        .timer = initTimer(),
        .level = initLevel(),
        .db = initDataBase("tetris_db.txt"),
        .speed_diff = TETRIS_SPEED_INCREMENT,
        .tick_diff = TETRIS_TICK_DECREMENT
    };

    assignFunctionPointers(&self);
    clearField(self.game_info.field);
    return self;
}

Tetris_t *initTetris() {
  static Tetris_t tetris;
  static bool initialized = false;

  if (!initialized) {
    tetris = constructorTetris();
    initialized = true;
  }

  return &tetris;
}
