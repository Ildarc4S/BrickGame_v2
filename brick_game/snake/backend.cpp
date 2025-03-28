#include "./include/game_singleton.h"

extern "C" {
  void userInput(UserAction_t action, bool hold) {
    s21::SnakeGameSingleton::getSnakeGame().userInput(action, hold);
  }

  GameInfo_t updateCurrentState() {
    return s21::SnakeGameSingleton::getSnakeGame().getGameInfo();
  }
}

