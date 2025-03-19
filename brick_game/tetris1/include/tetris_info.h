#ifndef TETRIS_INFO_H
#define TETRIS_INFO_H

#include "./tetramino.h"
#include "./tetramino_collection.h"
#include "./../../spec/game_spec.h"

typedef struct _tetris_info {
  GameInfo_t game_info;
  Tetramino_t *curr_tetramino;
  Tetramino_t *next_tetramino;
} TetrisInfo_t;

#endif  // TETRIS_INFO_H
