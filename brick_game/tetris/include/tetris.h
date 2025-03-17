#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdlib.h>

#include "./data_base.h"
#include "./level_manager.h"
#include "./tetramino_collection.h"
#include "./tetris_info.h"
#include "./timer.h"
#include "./utils.h"

#define FIELD_WIDTH 10  /**< Width of the game field (in blocks) */
#define FIELD_HEIGHT 20 /**< Height of the game field (in blocks) */

typedef enum {
  START,     /**< Game is in the start state */
  SPAWN,     /**< A new Tetramino is spawned */
  MOVE,      /**< Game is in the move state, waiting for user input */
  PAUSE,     /**< Game is paused */
  GAME_OVER, /**< Game is over */
  EXIT,      /**< Game has exited */
  ATTACH     /**< A Tetramino has attached to the game field */
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

#endif /* TETRIS_H */
