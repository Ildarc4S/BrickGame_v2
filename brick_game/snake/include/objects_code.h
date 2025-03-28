#ifndef SNAKE_OBJECTS_CODE_H
#define SNAKE_OBJECTS_CODE_H

namespace s21 {

enum class State {
  kStart = 0,
  kSpawn,
  kMove,
  kEat,
  kPause,
  kGameOver,
  kExit
};

enum class Direction {
  kUp,
  kDown,
  kLeft,
  kRight
};

enum class PauseMode {
  kPause = 1,
  kGameContinue = 2,
  kStart = 3,
  kGameOver = 4,
  kExit = 5,
  kWin = 6
};

enum class FigureCode {
  kAir = -2,
  kWall = -1,
  kSnake = 10,
  kApple = 11
};

}  // namespace s21

#endif  // SNAKE_OBJECTS_CODE_H

