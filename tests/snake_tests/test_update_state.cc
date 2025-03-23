#include "./tests.h"

namespace s21 {

TEST(SnakeGameTest, UpdateCurrState) {
    GameInfo_t game_info = updateCurrentState();

    const int expected_y = FIELD_HEIGHT / 2;
    const int start_x = FIELD_WIDTH / 2;

    for (int i = 0; i < 4; ++i) {
        int x = start_x + i;
        EXPECT_EQ(game_info.field[expected_y][x], static_cast<int>(FigureCode::SNAKE));
    }

    for (int i = 0; i < FIELD_HEIGHT + 2; ++i) {
        EXPECT_EQ(game_info.field[i][0], static_cast<int>(FigureCode::WALL));
        EXPECT_EQ(game_info.field[i][FIELD_WIDTH + 1], static_cast<int>(FigureCode::WALL));
    }

    for (int j = 0; j < FIELD_WIDTH + 2; ++j) {
        EXPECT_EQ(game_info.field[0][j], static_cast<int>(FigureCode::WALL));
        EXPECT_EQ(game_info.field[FIELD_HEIGHT + 1][j], static_cast<int>(FigureCode::WALL));
    }

    bool apple_exists = false;
    for (int i = 1; i <= FIELD_HEIGHT && !apple_exists; i++) {
      for (int j = 1; j <= FIELD_WIDTH && !apple_exists; j++) {
        if (game_info.field[i][j] == static_cast<int>(FigureCode::APPLE)) {
          apple_exists = true;
        }
      }
    }
    EXPECT_TRUE(apple_exists);

    userInput(UserAction_t::Terminate, false);
}
}  // namespace s21

