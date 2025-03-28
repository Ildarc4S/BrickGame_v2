#include "./include/game_singleton.h"

namespace s21 {
SnakeGame& SnakeGameSingleton::getSnakeGame() {
    static SnakeGame snake_game;
    return snake_game;
  }

}  // namespace s21

