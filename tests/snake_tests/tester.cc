#include "./tests.h"
#include <vector>

namespace s21 {

void SnakeGameTest::testUserInputAutomaton(SnakeGame &game, UserAction_t action,
                                           State initial_state,
                                           State expected_state) {
  game.state_ = initial_state;
  game.userInput(action, false);
  EXPECT_EQ(game.state_, expected_state);
}

void SnakeGameTest::testUserInputAutomatonDirection(
    SnakeGame &game, UserAction_t action, State initial_state,
    Direction expected_direction, State expected_state) {
  game.state_ = initial_state;
  game.userInput(action, false);

  EXPECT_EQ(game.snake_.getDirection(), expected_direction);
  EXPECT_EQ(game.state_, expected_state);
}

void SnakeGameTest::exitGame(SnakeGame &game) { game.exit(); }

Snake SnakeGameTest::getGameSnake(SnakeGame &game) { return game.snake_; }

bool SnakeGameTest::isTimerExpired(SnakeGame &game) {
  return game.timer_.isExpired();
}

void SnakeGameTest::setGameState(SnakeGame &game, State state) {
  game.state_ = state;
}

void SnakeGameTest::setTimerInterval(SnakeGame &game, int interval) {
  game.timer_.setInterval(interval, false);
}

void SnakeGameTest::setSnakeDirection(SnakeGame &game, Direction dir) {
  game.snake_.direction_ = dir;
}

void SnakeGameTest::setSnakeBody(SnakeGame &game,
                                 std::vector<Point> &new_body) {
  game.snake_.body_ = new_body;
}

std::vector<Point> SnakeGameTest::getSnakeBody(SnakeGame &game) {
  return game.snake_.body_;
}

State SnakeGameTest::getGameState(SnakeGame &game) { return game.state_; }

int SnakeGameTest::getMaxScore(SnakeGame &game) { return game.max_score_; }

int SnakeGameTest::getMaxLevelScore(SnakeGame &game) {
  return game.max_level_score_;
}

int SnakeGameTest::getAddScore(SnakeGame &game) { return game.add_score_; }

GameInfo_t SnakeGameTest::getGmaeInfo(SnakeGame &game) {
  return game.game_info_;
}

bool SnakeGameTest::getGameBoostTime(SnakeGame &game) {
  return game.boost_time_;
}

Direction SnakeGameTest::getSnakeDirection(SnakeGame &game) {
  return game.snake_.getDirection();
}

void SnakeGameTest::setGameScore(SnakeGame &game, int score) {
  game.game_info_.score = score;
}

Point SnakeGameTest::getApplePosition(SnakeGame &game) {
  return game.apple_.getPosition();
}

int SnakeGameTest::getTimerInterval(SnakeGame &game) {
  return game.timer_.getInterval();
}

int SnakeGameTest::getOriginalTimerInterval(SnakeGame &game) {
  return game.timer_.getLastInterval();
}
int SnakeGameTest::getGameScore(SnakeGame &game) {
  return game.game_info_.score;
}

int SnakeGameTest::getGameLevel(SnakeGame &game) {
  return game.game_info_.level;
}

void SnakeGameTest::eatGame(SnakeGame &game) { game.eat(); }

void SnakeGameTest::speedBoostGame(SnakeGame &game) { game.speedBoost(); }

void SnakeGameTest::setApplePosition(SnakeGame &game, Point &pos) {
  game.apple_.setPosition(pos);
}
};  // namespace s21
