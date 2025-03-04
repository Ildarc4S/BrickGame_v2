#include <cstdlib>
#include <algorithm>
#include <vector>

#include "./include/apple.h"

namespace s21 {

Apple::Apple(const std::vector<Point>& snake_body) : position_() {
  genRandPosition(snake_body);
}

void Apple::genRandPosition(const std::vector<Point>& snake_body) {
  Point temp;
  do {
    temp = Point(rand() % 10, rand() % 20);
  } while(std::find(snake_body.begin(), snake_body.end(), temp) != snake_body.end());
}

Point Apple::getPosition() {
  return position_;
}


}  // namespace s21

