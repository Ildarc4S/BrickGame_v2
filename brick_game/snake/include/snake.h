#pragma once

#include <vector>

#include "./../../spec/game_spec.h"
#include "./point.h"
#include "./apple.h"

namespace s21 {

enum class State {
  START = 0,
  SPAWN,
  MOVE,
  EAT,
  PAUSE,
  GAME_OVER,
  EXIT
};

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Snake {
 private:
  State state_;
  Direction direction_;
  UserAction_t action_;
  std::vector<Point> body_;
  
  Apple apple_;
  int speed_;
  int score_;
  int pause_;

 public:
  Snake();
};

}  // namespace s21
