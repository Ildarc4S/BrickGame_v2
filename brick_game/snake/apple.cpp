#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

#include "./include/apple.h"


namespace s21 {

Apple::Apple(const std::vector<Point>& snake_body) : position_() {
  srand(time(NULL));
  genRandPosition(snake_body);
}

void Apple::genRandPosition(const std::vector<Point>& snake_body) {
  Point temp;
  do {
    temp = Point(rand() % FIELD_WIDTH + 1, rand() % FIELD_HEIGHT + 1);
  } while (std::find(snake_body.begin(), snake_body.end(), temp) != snake_body.end());
  position_ = temp;
}

Point Apple::getPosition() const {
  return position_;
}
void Apple::setPosition(const Point& position) {
  position_ = position;
}

}  // namespace s21

