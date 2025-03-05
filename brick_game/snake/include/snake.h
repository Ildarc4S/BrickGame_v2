#pragma once

#include <vector>
#include <iostream>

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
  Direction direction_;
  std::vector<Point> body_;
  int speed_;
 public:
  Snake();

  void setDirection(Direction direction) {
    direction_ = direction;
  }

  Direction getDirection();
  const std::vector<Point>& getBody() const;

  void move();
};

class SnakeGame {
 private:
  State state_;
  UserAction_t action_;
  GameInfo_t game_info_;

  Snake snake_;
  Apple apple_;

  int score_;
  int pause_;

 public:
  SnakeGame()
    : state_(State::START),
      action_(UserAction_t::Start),
      snake_(),
      score_(0),
      pause_(false) {
    apple_.genRandPosition(snake_.getBody());
    std:: cout << "(" << apple_.getPosition().setX() << ", " << apple_.getPosition().setY() << ")\n";
  }

  void update(Direction direction) {
      snake_.setDirection(direction);
      snake_.move();
  }

  const Snake& getSnake() {
    return snake_;
  }

  const Apple& getApple() {
    return apple_;
  }
};

}  // namespace s21
