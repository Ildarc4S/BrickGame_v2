#include "./include/tetris.h"
#include "./include/fsm.h"

void userInput(UserAction_t action, bool hold) {
  updateFSM(action, hold);
}

GameInfo_t updateCurrentState() {
  
  Tetris_t* tetris = initTetris(); 
  tetris->updateTetrisState(tetris);
  return tetris->game_info;

}
