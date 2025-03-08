#pragma once

#include <vector>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#include "./../../spec/game_spec.h"

#ifdef __cplusplus
}
#endif

#include "./point.h"
#include "./apple.h"
#include "./data_base.h"
#include "./timer.h"

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

enum class PauseMode {
  PAUSE = 1,
  GAME_CONTINUE = 2,
  START = 3,
  GAME_OVER = 4,
  EXIT = 5
};

enum class FigureCode {
  AIR = 0,
  WALL,
  SNAKE,
  APPLE
};

class Snake {
 private:
  Direction direction_;
  std::vector<Point> body_;
  int speed_;
 public:
  Snake();
  Snake(const Snake& other);
  Snake(Snake&& other);

  Snake& operator=(const Snake& other);
  Snake& operator=(Snake&& other);

  void setDirection(Direction direction) {
    direction_ = direction;
  }

  Direction getDirection();
  const std::vector<Point>& getBody() const;

  void move(bool apple_eat = false);
  Point calcAndGetNewHeadPos();
};



class SnakeGame {
 private:
  State state_;
  UserAction_t action_;
  GameInfo_t game_info_;
  Timer timer_;

  Snake snake_;
  Apple apple_;
  DataBase db_;

  int score_;
  int pause_;

  void start();
  void spawn();
  void pause();
  void exit();
  void eat();

  void moveHandle(Direction direction, bool hold);

  bool isCollision(const Point& head);
  bool isAppleCollide(const Point& head);
  bool isOppositeDirection(const Direction& direction);

  int** fillField(int width, int height);
  void clearField(int width, int height);

 public:
  SnakeGame();
  void userInput(UserAction_t action, bool hold);
  GameInfo_t getGameInfo();

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
