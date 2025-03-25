#ifndef GAME_SINGLETON_H
#define GAME_SINGLETON_H

#include "./game_manager.h"

namespace s21 {

class SnakeGameSingleton {
 private:
  SnakeGameSingleton() = default;
  ~SnakeGameSingleton() = default;

  SnakeGameSingleton(const SnakeGameSingleton&) = delete;
  SnakeGameSingleton& operator=(const SnakeGameSingleton&) = delete;

 public:
  static SnakeGame& getSnakeGame() {
    static SnakeGame snake_game;
    return snake_game;
  }
};

}  // namespace s21

#endif  // GAME_SINGLETON_H

