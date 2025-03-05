#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "./include/snake.h"
#include "./include/point.h"

void printField(const std::vector<s21::Point>& vec, const s21::Apple& apple) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (std::find(vec.begin(), vec.end(), s21::Point(j, i)) != vec.end()) {
        std::cout << "[]";
      } else {
        std::cout << "  ";
      }

      if (i == apple.getPosition().setY() && j == apple.getPosition().setX()) {
        std::cout << "()";
      }
    }
    std::cout << std::endl;
  }
}

int main() {
  s21::SnakeGame game;
  int i = 0;
  while (i < 3) {
    i++;
    printField(game.getSnake().getBody(), game.getApple());
    if (i == 1) {
      game.update(s21::Direction::DOWN);
    } else {
      game.update(s21::Direction::RIGHT);
    }
  }
}
