#pragma once

namespace s21 {

enum class ObjectCode {
  kAir = -2,
  kWall = -1,
  kTetraminoI = 1,
  kTetraminoO = 2,
  kTetraminoT = 3,
  kTetraminoS = 4,
  kTetraminoZ = 5,
  kTetraminoJ = 6,
  kTetraminoL = 7,

  kSnake = 10,
  kApple = 11
};

enum class PauseMode {
  kPause = 1,
  kGameContinue = 2,
  kStart = 3,
  kGameOver = 4,
  kExit = 5,
  kWin = 6
};

} // namespace s21
