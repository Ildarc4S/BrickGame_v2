#ifndef TETRIS_STATE_H
#define TETRIS_STATE_H

typedef enum {
  TETRIS_STATE_START,
  TETRIS_STATE_SPAWN,
  TETRIS_STATE_MOVE,
  TETRIS_STATE_PAUSE,
  TETRIS_STATE_GAME_OVER,
  TETRIS_STATE_EXIT,
  TETRIS_STATE_ATTACH
} TetrisState_t;

#endif  // TETRIS_STATE_H

