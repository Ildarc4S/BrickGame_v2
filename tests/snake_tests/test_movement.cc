#include "./tests.h"

namespace s21 {

TEST(SnakeGameTest, MoveHandleEatApple) {
  SnakeGame game;
  SnakeGameTest tester;

  tester.setSnakeDirection(game, Direction::kUp);
  std::vector<Point> begin_body = tester.getSnakeBody(game);

  Point apple_pos(FIELD_WIDTH / 2 + begin_body.size(), FIELD_HEIGHT / 2);
  tester.setApplePosition(game, apple_pos);

  int initial_score = tester.getGameScore(game);
  tester.setGameState(game, State::kMove);
  game.userInput(UserAction_t::Right, false);

  EXPECT_EQ(tester.getGameScore(game),
            initial_score + tester.getAddScore(game));
  EXPECT_NE(tester.getApplePosition(game), Point(5, 4));

  EXPECT_EQ(tester.getSnakeBody(game).size(), begin_body.size() + 1);
}

TEST(SnakeGameTest, MoveHandleCollideWithBody) {
  SnakeGame game;
  SnakeGameTest tester;

  tester.setGameState(game, State::kMove);
  game.userInput(UserAction_t::Down, false);
  game.userInput(UserAction_t::Left, false);
  game.userInput(UserAction_t::Up, false);

  EXPECT_EQ(tester.getGameState(game), State::kGameOver);
}

TEST(SnakeGameTest, MoveHandleCollisionWithWalls) {
  SnakeGame game;
  SnakeGameTest tester;

  tester.setGameState(game, State::kMove);
  game.userInput(UserAction_t::Right, false);
  game.userInput(UserAction_t::Right, false);
  game.userInput(UserAction_t::Right, false);

  EXPECT_EQ(tester.getGameState(game), State::kGameOver);
}

TEST(SnakeGameTest, MoveHandleOppositeDirection) {
  SnakeGame game;
  SnakeGameTest tester;

  tester.setGameState(game, State::kMove);
  game.userInput(UserAction_t::Left, false);

  EXPECT_EQ(tester.getGameState(game), State::kMove);
}

TEST(SnakeGameTest, SnakeMovesAfterTimerExpirationRealTime) {
  SnakeGame game;
  SnakeGameTest tester;

  game.userInput(UserAction_t::Start, false);
  game.userInput(UserAction_t::Down, false);
  Point initial_head = tester.getSnakeBody(game).back();
  tester.setTimerInterval(game, -1);

  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  game.getGameInfo();

  Point new_head = tester.getSnakeBody(game).back();
  EXPECT_NE(initial_head, new_head);
}

}  // namespace s21
