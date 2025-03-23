#include "./tests.h"

namespace s21 {

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

}  // namespace 21
