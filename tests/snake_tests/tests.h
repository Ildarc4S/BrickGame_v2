#ifndef SNAKE_TESTS
#define SNAKE_TESTS

#include "./../../brick_game/snake/include/game_manager.h"
#include "./../../brick_game/spec/game_spec.h"

#include <gtest/gtest.h>
#include <thread>

namespace s21 {

class SnakeGameTest {
 public:
  void testUserInputAutomaton(SnakeGame &game, UserAction_t action,
                              State initial_state, State expected_state);
  void testUserInputAutomatonDirection(SnakeGame &game, UserAction_t action,
                                       State initial_state,
                                       Direction expected_direction,
                                       State expected_state);
  bool isTimerExpired(SnakeGame &game);
  void setGameState(SnakeGame &game, State state);
  void setTimerInterval(SnakeGame &game, int interval);
  void setSnakeDirection(SnakeGame &game, Direction dir);
  void setSnakeBody(SnakeGame &game, std::vector<Point> &new_body);
  std::vector<Point> getSnakeBody(SnakeGame &game);
  State getGameState(SnakeGame &game);
  int getMaxScore(SnakeGame &game);
  int getMaxLevelScore(SnakeGame &game);
  int getAddScore(SnakeGame &game);
  GameInfo_t getGmaeInfo(SnakeGame &game);
  bool getGameBoostTime(SnakeGame &game);
  Direction getSnakeDirection(SnakeGame &game);
  void setGameScore(SnakeGame &game, int score);
  Point getApplePosition(SnakeGame &game);
  int getTimerInterval(SnakeGame &game);
  int getOriginalTimerInterval(SnakeGame &game);
  int getGameScore(SnakeGame &game);
  int getGameLevel(SnakeGame &game);
  void eatGame(SnakeGame &game);
  void speedBoostGame(SnakeGame &game);
  void setApplePosition(SnakeGame &game, Point &pos);
  void snakeCopyConstructor();
  void snakeMoveConstructor();
  void snakeCopyAssignment();
  void snakeMoveAssignment();
};

}  // namespace s21
#endif  // SNAKE_TESTS
