#include "./tests.h"

namespace s21 {

TEST(SnakeTest, CopyConstructor) {
  SnakeGameTest tester;
  tester.snakeCopyConstructor();
}

TEST(SnakeTest, MoveConstructor) {
  SnakeGameTest tester;
  tester.snakeMoveConstructor();
}

TEST(SnakeTest, CopyAssignment) {
  SnakeGameTest tester;
  tester.snakeCopyAssignment();
}

TEST(SnakeTest, MoveAssignment) {
  SnakeGameTest tester;
  tester.snakeMoveAssignment();
}

}  // namespace s21
