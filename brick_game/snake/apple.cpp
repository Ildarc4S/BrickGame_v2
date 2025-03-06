#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

#include "./include/apple.h"

namespace s21 {

Apple::Apple() {}

Apple::Apple(const std::vector<Point>& snake_body) : position_() {
  genRandPosition(snake_body);
}

void Apple::genRandPosition(const std::vector<Point>& snake_body) {
  Point temp;
  srand(time(NULL));
  do {
    temp = Point(rand() % 8 + 1, rand() % 18 + 1);
  } while(std::find(snake_body.begin(), snake_body.end(), temp) != snake_body.end());
  temp.setX() = 5;
  temp.setY() = 5;
  position_ = temp;
}

Point Apple::getPosition() const {
  return position_;
}


}  // namespace s21

