#include <vector>

#include "./tests.h"

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

void SnakeGameTest::speedBoostGame(SnakeGame &game) { game.toogleBoostTime(); }

void SnakeGameTest::setApplePosition(SnakeGame &game, Point &pos) {
  game.apple_.setPosition(pos);
}

void SnakeGameTest::snakeCopyConstructor() {
  Snake default_snake_;
  Snake copied_snake(default_snake_);

  EXPECT_EQ(copied_snake.getDirection(), default_snake_.getDirection());
  EXPECT_EQ(copied_snake.getSpeed(), default_snake_.getSpeed());
  EXPECT_EQ(copied_snake.getBody(), default_snake_.getBody());

  copied_snake.move(false);
  EXPECT_NE(copied_snake.getBody(), default_snake_.getBody());
}

void SnakeGameTest::snakeMoveConstructor() {
  Snake default_snake_;
  auto original_dir = default_snake_.getDirection();
  auto original_speed = default_snake_.getSpeed();
  auto original_body = default_snake_.getBody();

  Snake moved_snake(std::move(default_snake_));

  EXPECT_EQ(moved_snake.getDirection(), original_dir);
  EXPECT_EQ(moved_snake.getSpeed(), original_speed);
  EXPECT_EQ(moved_snake.getBody(), original_body);

  EXPECT_TRUE(default_snake_.getBody().empty());
}

void SnakeGameTest::snakeCopyAssignment() {
  Snake default_snake_;
  Snake another_snake;
  another_snake.move(false);
  another_snake = default_snake_;

  EXPECT_EQ(another_snake.getDirection(), default_snake_.getDirection());
  EXPECT_EQ(another_snake.getSpeed(), default_snake_.getSpeed());
  EXPECT_EQ(another_snake.getBody(), default_snake_.getBody());

  another_snake = another_snake;
  EXPECT_EQ(another_snake.getDirection(), default_snake_.getDirection());
}

void SnakeGameTest::snakeMoveAssignment() {
  Snake default_snake_;
  Snake another_snake;
  another_snake.move(false);

  auto original_dir = default_snake_.getDirection();
  auto original_speed = default_snake_.getSpeed();
  auto original_body = default_snake_.getBody();

  another_snake = std::move(default_snake_);

  EXPECT_EQ(another_snake.getDirection(), original_dir);
  EXPECT_EQ(another_snake.getSpeed(), original_speed);
  EXPECT_EQ(another_snake.getBody(), original_body);

  EXPECT_TRUE(default_snake_.getBody().empty());
}

};  // namespace s21
