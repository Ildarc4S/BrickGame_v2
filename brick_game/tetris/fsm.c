#include "./include/fsm.h"

#include <ncurses.h>

void updateFSM(UserAction_t action, bool hold) {
  Tetris_t *tetris = initTetris();
  clearTetraminoFromField(tetris);

  switch (tetris->state) {
    case TETRIS_STATE_START:
      startHandler(tetris, action);
      break;
    case TETRIS_STATE_MOVE:
      moveHandler(tetris, action, hold);
      break;
    case TETRIS_STATE_PAUSE:
      pauseHandler(tetris, action);
      break;
    case TETRIS_STATE_GAME_OVER:
      gameOverHandler(tetris, action);
      break;

    default:
      break;
  };
}

void startHandler(Tetris_t *tetris, UserAction_t action) {
  switch (action) {
    case Terminate:
      tetris->exit(tetris);
      break;
    case Start:
      tetris->start(tetris);
      break;
    default:
      break;
  };
}

void moveHandler(Tetris_t *tetris, UserAction_t action, bool hold) {
  switch (action) {
    case Terminate:
      tetris->exit(tetris);
      break;
    case Pause:
      tetris->pause(tetris);
      break;
    case Left:
      tetris->left(tetris, hold);
      break;
    case Right:
      tetris->right(tetris, hold);
      break;
    case Up:
      tetris->up(tetris, hold);
      break;
    case Down:
      tetris->down(tetris, hold);
      break;
    case Action:
      tetris->action(tetris, hold);
      break;

    default:
      break;
  };
}

void pauseHandler(Tetris_t *tetris, UserAction_t action) {
  switch (action) {
    case Terminate:
      tetris->exit(tetris);
      break;
    case Start:
      tetris->start(tetris);
      break;
    case Pause:
      tetris->pause(tetris);
      break;

    default:
      break;
  };
}

void gameOverHandler(Tetris_t *tetris, UserAction_t action) {
  switch (action) {
    case Start:
      tetris->start(tetris);
      break;
    case Terminate:
      tetris->exit(tetris);
      break;

    default:
      break;
  };
}
