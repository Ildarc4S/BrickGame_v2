#include "./tests.h"

namespace s21 {

TEST(SnakeGameTest, UserInputStartFromStartState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Start, State::kStart, State::kMove);
}

TEST(SnakeGameTest, UserInputTerminateFromStartState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Terminate, State::kStart, State::kExit);
}

TEST(SnakeGameTest, UserInputPauseFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Pause, State::kMove, State::kPause);
}

TEST(SnakeGameTest, UserInputTerminateFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Terminate, State::kMove, State::kExit);
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
    tester.setSnakeDirection(game, Direction::kUp);
    tester.testUserInputAutomatonDirection(game, UserAction_t::Left, State::kMove, Direction::kLeft, State::kMove);
}

TEST(SnakeGameTest, UserInputRightFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Right, State::kMove, Direction::kRight, State::kMove);
}

TEST(SnakeGameTest, UserInputUpFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Up, State::kMove, Direction::kUp, State::kMove);
}

TEST(SnakeGameTest, UserInputDownFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Down, State::kMove, Direction::kDown, State::kMove);
}

TEST(SnakeGameTest, UserInputActionFromMoveState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.setGameState(game, State::kMove);
    game.userInput(UserAction_t::Action, false);
    EXPECT_TRUE(tester.getGameBoostTime(game));
    game.userInput(UserAction_t::Action, false);
    EXPECT_FALSE(tester.getGameBoostTime(game));
    
}

TEST(SnakeGameTest, UserInputStartFromPauseState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Start, State::kPause, tester.getSnakeDirection(game), State::kMove);
}

TEST(SnakeGameTest, UserInputTerminateFromPauseState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomatonDirection(game, UserAction_t::Terminate, State::kPause, tester.getSnakeDirection(game), State::kExit);
}
TEST(SnakeGameTest, UserInputStartFromGameOverState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Start, State::kGameOver, State::kMove);
}

TEST(SnakeGameTest, UserInputTerminateFromGameOverState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Terminate, State::kGameOver, State::kExit);
}

TEST(SnakeGameTest, UserInputInvalidActionFromStartState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::kStart, State::kStart);
}

TEST(SnakeGameTest, UserInputInvalidActionFromPauseState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::kPause, State::kPause);  
}

TEST(SnakeGameTest, UserInputInvalidActionFromGameOverState) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::kGameOver, State::kGameOver);
}

TEST(SnakeGameTest, UserInput) {
    SnakeGame game;
    SnakeGameTest tester;
    tester.testUserInputAutomaton(game, UserAction_t::Left, State::kGameOver, State::kGameOver);
}

}  // namespace 21
