#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "./../../spec/game_spec.h"

#include "./memory_utils.h"
#include "./point.h"
#include "./apple.h"
#include "./data_base.h"
#include "./timer.h"
#include "./snake.h"

namespace s21 {

class SnakeGame {
 private:
  State state_;
  UserAction_t action_;
  GameInfo_t game_info_;
  Timer timer_;

  Snake snake_;
  Apple apple_;
  DataBase db_;

  int max_level_score_;
  int max_level_;
  int max_score_;
  int add_score_;
  int add_speed_;
  int interval_diff_;
  int interval_boost_diff_;
  bool boost_time_;

  void start();
  void spawn();
  void pause();
  void exit();
  void eat();
  void speedBoost();
  void moveHandle(Direction direction, bool hold);

  bool isCollision(const Point& head);
  bool isAppleCollide(const Point& head);
  bool isOppositeDirection(const Direction& direction);

  void clearField(int width, int height);
  void restoreGameInfoDate();

 public:
  SnakeGame();
  ~SnakeGame();


  void toogleBoostTime();
  void startHandler(UserAction_t action);
  void moveHandler(UserAction_t action, bool hold);
  void pauseHandler(UserAction_t action);
  void gameOverHandler(UserAction_t action);

  void userInput(UserAction_t action, bool hold);
  GameInfo_t getGameInfo();

  friend class SnakeGameTest;
};
}  // namespace s21

#endif  // GAME_MANAGER_H

