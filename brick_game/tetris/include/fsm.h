#ifndef FSM_H
#define FSM_H

#include "./tetris.h"
#include "./utils.h"

void updateFSM(UserAction_t action, bool hold);

void startHandler(Tetris_t *tetris, UserAction_t action);
void moveHandler(Tetris_t *tetris, UserAction_t action, bool hold);
void pauseHandler(Tetris_t *tetris, UserAction_t action);
void gameOverHandler(Tetris_t *tetris, UserAction_t action);

#endif  // FSM_H

