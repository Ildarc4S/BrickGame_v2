#include "./tests.h"

namespace s21 {

TEST(SnakeGameTest, SpeedBoostTogglesState) {
    SnakeGame game;
    SnakeGameTest tester;

    const bool initial_boost = tester.getGameBoostTime(game);
    tester.speedBoostGame(game);
    EXPECT_NE(tester.getGameBoostTime(game), initial_boost);

    tester.speedBoostGame(game);
    EXPECT_EQ(tester.getGameBoostTime(game), initial_boost);

}

TEST(SnakeGameTest, SpeedBoostModifiesTimer) {
    SnakeGame game;
    SnakeGameTest tester;

    const int initial_interval = tester.getTimerInterval(game);
    tester.speedBoostGame(game);
    EXPECT_EQ(tester.getTimerInterval(game), initial_interval - 80);

    tester.speedBoostGame(game);
    EXPECT_EQ(tester.getTimerInterval(game), initial_interval);
}

TEST(SnakeGameTest, SpeedBoostSavesOriginalInterval) {
    SnakeGame game;
    SnakeGameTest tester;

    const int original_interval = tester.getOriginalTimerInterval(game);

    tester.speedBoostGame(game);
    tester.speedBoostGame(game);
    EXPECT_EQ(tester.getTimerInterval(game), original_interval);
}
}  // namespace s21

