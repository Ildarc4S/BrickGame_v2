#include "./include/fsm.h"
#include "./include/tetris.h"

void userInput(UserAction_t action, bool hold) { updateFSM(action, hold); }

GameInfo_t updateCurrentState() {
  Tetris_t *tetris = initTetris();
  tetris->updateTetrisState(tetris);
  return tetris->game_info;
}
