#ifndef TETRIS_H
#define TETRIS_H

#include "./tetris_state.h"
#include "./tetramino_collection.h"
#include "./../../spec/game_spec.h"
#include "./timer.h"
#include "./data_base.h"
#include "./level_manager.h"

#define TETRIS_TETRAMINO_SPAWN_X (FIELD_WIDTH / 2)
#define TETRIS_TETRAMINO_SPAWN_Y -1

#define TETRIS_TETRAMINO_RIGHT_DIRECTION 1
#define TETRIS_TETRAMINO_LEFT_DIRECTION -1

#define TETRIS_INITIAL_SPEED 10
#define TETRIS_INITIAL_HIGH_SCORE 0
#define TETRIS_TICK_DECREMENT 70
#define TETRIS_SPEED_INCREMENT 10

typedef struct _tetris {
  TetrisState_t state;
  GameInfo_t game_info;
  Tetramino_t curr_tetramino;
  Tetramino_t* next_tetramino;
  TetraminoCollection_t collection;

  Timer_t timer;
  Level_t level;
  DataBase_t db;
  int speed_diff;
  long tick_diff;

  void (*start)(struct _tetris *);
  void (*spawn)(struct _tetris *);
  void (*action)(struct _tetris *, bool);
  void (*left)(struct _tetris *, bool);
  void (*right)(struct _tetris *, bool);
  void (*up)(struct _tetris *, bool);
  void (*down)(struct _tetris *, bool);
  void (*pause)(struct _tetris *);
  void (*exit)(struct _tetris *);
  void (*restoreInfo)(struct _tetris *);

  void (*updateScore)(struct _tetris *);
  void (*updateLevel)(struct _tetris *);
  void (*updateTetrisState)(struct _tetris *);
} Tetris_t;

Tetris_t* initTetris();

#endif  // TETRIS_H
