#ifndef SNAKE_GAME_SINGLETON_H
#define SNAKE_GAME_SINGLETON_H

#include "./game_manager.h"

namespace s21 {

class SnakeGameSingleton {
 private:
  SnakeGameSingleton() = default;
  ~SnakeGameSingleton() = default;

  SnakeGameSingleton(const SnakeGameSingleton&) = delete;
  SnakeGameSingleton& operator=(const SnakeGameSingleton&) = delete;

 public:
  static SnakeGame& getSnakeGame();
};

}  // namespace s21

#endif  // SNAKE_GAME_SINGLETON_H

