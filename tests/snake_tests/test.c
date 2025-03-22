#include "./../../brick_game/snake/include/snake.h"
#include <gtest/gtest.h>

namespace s21 {

class SnakeGameTest {
public:
  void testUserInputAutomaton(SnakeGame& game, UserAction_t action, State initial_state, State expected_state) {
    game.state_ = initial_state;
    game.userInput(action, false);
    EXPECT_EQ(game.state_, expected_state);
  }
  
  void testUserInputAutomatonDirection(SnakeGame& game, UserAction_t action, State initial_state, Direction expected_direction, State expected_state) {
    game.state_ = initial_state;
    game.userInput(action, false);

    EXPECT_EQ(game.snake_.getDirection(), expected_direction);
    EXPECT_EQ(game.state_, expected_state);
  }
  
  Snake getGameSnake(SnakeGame& game) {
    return game.snake_; 
  }

  
  void setGameState(SnakeGame& game, State state) {
    game.state_ = state;
  }
    
  void setSnakeDirection(SnakeGame& game, Direction dir) {
    game.snake_.direction_ = dir;
  }

  void setSnakeBody(SnakeGame& game, std::vector<Point>& new_body) {
    game.snake_.body_ = new_body; 
  }

  std::vector<Point> getSnakeBody(SnakeGame& game) {
    return game.snake_.body_; 
  }

  State getGameState(SnakeGame& game) {
    return game.state_;
  }

  int getMaxScore(SnakeGame& game) {
    return game.max_score_;
  }

  int getMaxLevelScore(SnakeGame& game) {
    return game.max_level_score_;
  }

  int getAddScore(SnakeGame& game) {
    return game.add_score_;
  }

  GameInfo_t getGmaeInfo(SnakeGame& game) {
    return game.game_info_;
  }

  bool getGameBoostTime(SnakeGame& game) {
    return game.boost_time_;
  }

  Direction getSnakeDirection(SnakeGame& game) {
    return game.snake_.getDirection();
  }

  void setGameScore(SnakeGame& game, int score) {
        game.game_info_.score = score;
  }
  
  Point getApplePosition(SnakeGame& game) {
      return game.apple_.getPosition();
  }
  
  int getTimerInterval(SnakeGame& game) {
      return game.timer_.getInterval();
  }
  
  int getOriginalTimerInterval(SnakeGame& game) {
      return game.timer_.getLastInterval();
  }
    int getGameScore(SnakeGame& game) {
        return game.game_info_.score;
    }

    int getGameLevel(SnakeGame& game) {
        return game.game_info_.level;
    }

    void eatGame(SnakeGame& game) {
      game.eat(); 
    } 

    void speedBoostGame(SnakeGame& game) {
      game.speedBoost();
    }

    void setApplePosition(SnakeGame& game, Point& pos) {
       game.apple_.setPosition(pos);
    }
};

TEST(SnakeGameTest, UserInputStartFromStartState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Start, State::START, State::MOVE);
}

TEST(SnakeGameTest, UserInputTerminateFromStartState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Terminate, State::START, State::EXIT);
}

TEST(SnakeGameTest, UserInputPauseFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Pause, State::MOVE, State::PAUSE);
}

TEST(SnakeGameTest, UserInputTerminateFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Terminate, State::MOVE, State::EXIT);
}

TEST(SnakeGameTest, UserInputLeftFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    
    std::vector<Point> new_body = {
        Point(5, 8),
        Point(5, 7),
        Point(5, 6),
        Point(5, 5)
    };

    tester.setSnakeBody(game, new_body);
    tester.setSnakeDirection(game, Direction::UP);
    tester.testUserInputAutomatonDirection(game, UserAction_t::Left, State::MOVE, Direction::LEFT, State::MOVE);
}

TEST(SnakeGameTest, UserInputRightFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Right, State::MOVE, Direction::RIGHT, State::MOVE);
}

TEST(SnakeGameTest, UserInputUpFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Up, State::MOVE, Direction::UP, State::MOVE);
}

TEST(SnakeGameTest, UserInputDownFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Down, State::MOVE, Direction::DOWN, State::MOVE);
}

TEST(SnakeGameTest, UserInputActionFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.setGameState(game, State::MOVE);
    game.userInput(UserAction_t::Action, false);
    EXPECT_TRUE(tester.getGameBoostTime(game));
    game.userInput(UserAction_t::Action, false);
    EXPECT_FALSE(tester.getGameBoostTime(game));
}

TEST(SnakeGameTest, UserInputStartFromPauseState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Start, State::PAUSE, tester.getSnakeDirection(game), State::MOVE);
}

TEST(SnakeGameTest, UserInputTerminateFromPauseState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Terminate, State::PAUSE, tester.getSnakeDirection(game), State::EXIT);
}
TEST(SnakeGameTest, UserInputStartFromGameOverState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Start, State::GAME_OVER, State::MOVE);
}

TEST(SnakeGameTest, UserInputTerminateFromGameOverState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Terminate, State::GAME_OVER, State::EXIT);
}

TEST(SnakeGameTest, UserInputInvalidActionFromStartState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::START, State::START);
}

TEST(SnakeGameTest, UserInputInvalidActionFromPauseState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::PAUSE, State::PAUSE);  
}

TEST(SnakeGameTest, UserInputInvalidActionFromGameOverState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::GAME_OVER, State::GAME_OVER);
}

TEST(SnakeGameTest, UserInput) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::GAME_OVER, State::GAME_OVER);
}

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

    EXPECT_EQ(tester.getGameState(game), State::GAME_OVER);
    EXPECT_EQ(tester.getGmaeInfo(game).pause, static_cast<int>(PauseMode::WIN));
}

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
TEST(SnakeGameTest, MoveHandleEatApple) {
    SnakeGame game;
    SnakeGameTest tester;

    tester.setSnakeDirection(game, Direction::UP);
    std::vector<Point> begin_body = tester.getSnakeBody(game); 

    Point apple_pos(FIELD_WIDTH / 2 + begin_body.size(), FIELD_HEIGHT / 2);
    tester.setApplePosition(game, apple_pos);

    int initial_score = tester.getGameScore(game);
    game.userInput(UserAction_t::Right, false);

    EXPECT_EQ(tester.getGameScore(game), initial_score + tester.getAddScore(game));
    EXPECT_NE(tester.getApplePosition(game), Point(5, 4));
       
    EXPECT_EQ(tester.getSnakeBody(game).size(), begin_body.size() + 1);
}

}  // namespace s21

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
