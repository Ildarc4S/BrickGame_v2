#include "./tests.h"

namespace s21 {

TEST(SnakeGameTest, EatIncreasesScore) {
    SnakeGame game;
    SnakeGameTest tester;

    const int initial_score = 10;
    tester.setGameScore(game, initial_score);
    tester.eatGame(game);

    EXPECT_EQ(tester.getGameScore(game), initial_score + tester.getAddScore(game));
}

TEST(SnakeGameTest, EatGeneratesNewApplePosition) {
    SnakeGame game;
    SnakeGameTest tester;
 
    const Point initial_apple = tester.getApplePosition(game);
    tester.eatGame(game);

    EXPECT_NE(tester.getApplePosition(game), initial_apple);
 
}

TEST(SnakeGameTest, EatIncreasesLevelWhenThresholdReached) {
    SnakeGame game;
    SnakeGameTest tester;

    const int target_score = tester.getMaxLevelScore(game) - 1;
    tester.setGameScore(game, target_score);

    tester.eatGame(game);

    EXPECT_EQ(tester.getGameLevel(game), 2);

}

TEST(SnakeGameTest, EatTriggersGameOverOnMaxScore) {
    SnakeGame game;
    SnakeGameTest tester;

    tester.setGameScore(game, tester.getMaxScore(game) - 1);
    tester.eatGame(game);

    EXPECT_EQ(tester.getGameState(game), State::kGameOver);
    EXPECT_EQ(tester.getGmaeInfo(game).pause, static_cast<int>(PauseMode::kWin));
}
}  // namespace s21

