#include "./include/snake.h"

namespace s21 {
Snake::Snake()
  : direction_(Direction::RIGHT),
  speed_(1) {
    for (int i = 0; i < 4; ++i) {
      body_.emplace_back(i, 0);
    }
}

Direction Snake::getDirection() {
    return direction_;
}

const std::vector<Point>& Snake::getBody() const {
    return body_;
}

void Snake::move() {
  Point temp = body_.back();

  switch (direction_) {
    case Direction::RIGHT:
      temp.setX()++;
      break;
    case Direction::DOWN:
      temp.setY()++;
      break;
  }

  body_.push_back(temp);
  body_.erase(body_.begin());
}

}  // namespace s21


