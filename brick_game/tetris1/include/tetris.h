#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdlib.h>

#include "./data_base.h"
#include "./level_manager.h"
#include "./tetris_info.h"
#include "./timer.h"
#include "./utils.h"

#define FIELD_WIDTH 10  /**< Width of the game field (in blocks) */
#define FIELD_HEIGHT 20 /**< Height of the game field (in blocks) */

typedef enum {
  TETRIS_STATE_START,
  TETRIS_STATE_SPAWN,
  TETRIS_STATE_MOVE,
  TETRIS_STATE_PAUSE,
  TETRIS_STATE_GAME_OVER,
  TETRIS_STATE_EXIT,
  TETRIS_STATE_ATTACH
} TetrisState_t;

typedef struct _tetris {
  TetrisState_t state;
  TetrisInfo_t info;

  TetraminoCollection_t collection;

  Timer_t timer;
  Level_t level;
  DataBase_t db;

  void (*start)(struct _tetris *tetris);
  void (*spawn)(struct _tetris *tetris);
  void (*left)(struct _tetris *tetris, bool hard);
  void (*action)(struct _tetris *tetris, bool hard);
  void (*right)(struct _tetris *tetris, bool hard);
  void (*up)(struct _tetris *tetris, bool hard);
  void (*down)(struct _tetris *tetris, bool hard);
  void (*pause)(struct _tetris *tetris);
  void (*gameOver)(struct _tetris *tetris);
  void (*exit)(struct _tetris *tetris);

  void (*updateScore)(struct _tetris *);
  void (*updateLevel)(struct _tetris *);
  void (*updateTetrisState)(struct _tetris *);
} Tetris_t;

Tetris_t* initTetris();

#endif  // TETRIS_H 
