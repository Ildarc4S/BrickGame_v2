#pragma once

#include <vector>
#include <iostream>

#include "./../../spec/game_spec.h"
#include "./point.h"
#include "./apple.h"
#include "./data_base.h"

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

enum class PauseState {
  PAUSE,
  GAME_OVER,
  EXIT
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
  DataBase db_;

  int score_;
  int pause_;

  void start();
  void spawn();
  void pause();
  void exit();

  void moveHandle(Direction direction, bool hold);
  bool isCollide();

 public:
  SnakeGame()
    : state_(State::START),
      action_(UserAction_t::Start),
      snake_(),
      score_(0),
      db_("./brick_game/snake/db/score.txt"),
      pause_(false){
    apple_.genRandPosition(snake_.getBody());
  }
  
  void userInput(UserAction_t action, bool hold);

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
