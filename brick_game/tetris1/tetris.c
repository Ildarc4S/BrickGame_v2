#include "./include/tetris.h"

#include "./include/tetris_utils.h"

void _startGame(Tetris_t *tetris) {
  if (tetris->state == TETRIS_STATE_START) {
    tetris->spawn(tetris);
    tetris->info.game_info.high_score = tetris->db.read(&tetris->db);
  } else if (tetris->state == TETRIS_STATE_PAUSE) {
    tetris->state = TETRIS_STATE_MOVE;
  } else if (tetris->state == TETRIS_STATE_GAME_OVER) {
    cleanField(tetris->info.game_info.field);

    tetris->timer.tick = 1000;
    tetris->level.level = 1;
    tetris->level.score.score = 0;

    tetris->info.game_info.level = 1;
    tetris->info.game_info.score = 0;

    tetris->info.game_info.speed = 10;
    tetris->spawn(tetris);
  }
  tetris->info.game_info.pause = 0;
}

void _spawn(Tetris_t *self) {
  if (!self) {
    return;
  }

  if (!self->info.next_tetramino) {
    self->info.next_tetramino = self->collection.getRandomTetranimo(&self->collection);
  }

  self->info.curr_tetramino = self->info.next_tetramino;
  self->info.curr_tetramino->x = FIELD_WIDTH / 2;
  self->info.curr_tetramino->y = 1;

  self->info.next_tetramino = self->collection.getRandomTetranimo(&self->collection);

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      self->info.game_info.next[i][j] = 0;
      if (self->info.next_tetramino->brick[i][j]) {
        self->info.game_info.next[i][j] = self->info.next_tetramino->color;
      }
    }
  }

  self->state = TETRIS_STATE_MOVE;

  if (checkCollideOtherBreak(self, self->info.curr_tetramino)) {
    self->info.game_info.pause = -1;
    self->db.write(&self->db, self->info.game_info.high_score);
    self->state = TETRIS_STATE_GAME_OVER;
  }
}

void _pauseGame(Tetris_t *tetris) {
  tetris->info.game_info.pause = 1;
  tetris->state = TETRIS_STATE_PAUSE;
}

void _exitGame(Tetris_t *self) {
  self->db.write(&self->db, self->info.game_info.high_score);
  self->state = TETRIS_STATE_EXIT;
}

void _left(Tetris_t *tetris, bool hold) {
  if (!tetris) {
    return;
  }
  (void)hold;

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  tetramino->x--;
  if (isCollide(tetris, tetramino)) {
    tetramino->x++;
  }
  replaceTetramin(tetris, tetramino);
}

void _right(Tetris_t *tetris, bool hold) {
  if (!tetris) {
    return;
  }
  (void)hold;

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  tetramino->x++;
  if (isCollide(tetris, tetramino)) {
    tetramino->x--;
  }
  replaceTetramin(tetris, tetramino);
}

void _up(Tetris_t *self, bool hold) {
  if (!self) {
    return;
  }
  (void)hold;
}

void _down(Tetris_t *tetris, bool hold) {
  if (!tetris) {
    return;
  }

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  int is_collide = 0;

  if (hold == 0) {
    tetramino->y++;
    if (isCollide(tetris, tetramino)) {
      is_collide = 1;
      tetramino->y--;
    }
  } else {
    while (!isCollide(tetris, tetramino)) {
      tetramino->y++;
    }
    tetramino->y--;
    is_collide = 1;
  }
  replaceTetramin(tetris, tetramino);
  if (is_collide) {
    tetris->state = TETRIS_STATE_ATTACH;
    insertBrick(tetris);
    tetris->info.curr_tetramino = NULL;
  }
}

void _action(Tetris_t *tetris, bool hold) {
  if (!tetris) {
    return;
  }
  (void)hold;

  Tetramino_t *tetramino = tetris->info.curr_tetramino;
  int temp[TETRAMINO_WIDTH][TETRAMINO_HEIGHT];
  copyBrick(temp, tetramino->brick);
  rotateTetramino(tetramino);

  if (isCollide(tetris, tetramino)) {
    copyBrick(tetramino->brick, temp);
  }
}

void _updateTetrisScore(Tetris_t *self) {
  self->info.game_info.score = self->level.score.score;
  if (self->info.game_info.score >= self->info.game_info.high_score) {
    self->info.game_info.high_score = self->info.game_info.score;
  }
}

void _updateTetrisLevel(Tetris_t *self) {
  long tick = self->timer.tick;
  if (self->level.level > self->info.game_info.level && tick >= 80) {
    self->info.game_info.speed += 10;
    self->timer.tick -= 70;
  }
  self->info.game_info.level = self->level.level;
}

void _updateTetrisState(Tetris_t* self) {
  if (self->state == TETRIS_STATE_MOVE) {
    if (self->timer.calcDiff(&self->timer) >= self->timer.tick) {
      self->down(self, 1);
      self->timer.updateLastTime(&self->timer);
    }
  } else if (self->state == TETRIS_STATE_ATTACH) {
    self->spawn(self);
    cleanLines(self);
  }
  
  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      if (self->info.curr_tetramino && self->info.curr_tetramino->brick[i][j]) {
        int x = self->info.curr_tetramino->x + j;
        int y = self->info.curr_tetramino->y + i;
        if (x >= 0 && x < FIELD_WIDTH + 2 && y >= 0 && y < FIELD_HEIGHT + 2) {
          self->info.game_info.field[y][x] = self->info.curr_tetramino->color;
         }
      }
    }
  }
 
}

Tetris_t constructorTetris() {
  Tetris_t tetris_self;
  tetris_self.state = TETRIS_STATE_START;
  tetris_self.info = (TetrisInfo_t){
      .game_info = {.field = newField(FIELD_WIDTH + 2, FIELD_HEIGHT + 2),
                    .next = newField(TETRAMINO_WIDTH, TETRAMINO_HEIGHT),
                    .score = 0,
                    .high_score = 0,
                    .level = 1,
                    .speed = 0,
                    .pause = 2},
      .curr_tetramino = NULL,
      .next_tetramino = NULL};
  cleanField(tetris_self.info.game_info.field);

  tetris_self.db = initDatabase("./brick_game/db/tetris_db.txt");
  tetris_self.level = initLevel();
  tetris_self.timer = initTimer(),

  tetris_self.left = _left;
  tetris_self.right = _right;
  tetris_self.down = _down;
  tetris_self.up = _up;
  tetris_self.action = _action;
  tetris_self.start = _startGame;
  tetris_self.spawn = _spawn;
  tetris_self.exit = _exitGame;
  tetris_self.pause = _pauseGame;

  tetris_self.updateLevel = _updateTetrisLevel;
  tetris_self.updateScore = _updateTetrisScore;
  tetris_self.updateTetrisState = _updateTetrisState;

  tetris_self.collection = initTetraminoCollection();
  return tetris_self;
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
