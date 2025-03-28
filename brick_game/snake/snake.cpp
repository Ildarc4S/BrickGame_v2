#include "./include/snake.h"

namespace s21 {

Snake::Snake()
  : direction_(Direction::kRight),
    body_(),
    speed_(SNAKE_DEFAULT_SPEED) {
  int mid_x = FIELD_WIDTH / MID_SIZE_DIVISOR;
  int mid_y = FIELD_HEIGHT / MID_SIZE_DIVISOR;

  for (int i = 0; i < SNAKE_SIZE; i++) {
    body_.emplace_back(mid_x + i, mid_y);
  }
}

Snake::Snake(const Snake& other)
  : direction_(other.direction_),
    body_(other.body_),
    speed_(other.speed_)
{}

Snake::Snake(Snake&& other)
  : direction_(std::move(other.direction_)),
    body_(std::move(other.body_)),
    speed_(std::move(other.speed_))
{}

Snake& Snake::operator=(const Snake& other) {
  if (this != &other) {
    direction_ = other.direction_;
    speed_ = other.speed_;
    body_ = other.body_;
  }
  return *this;
}

Snake& Snake::operator=(Snake&& other) {
  if (this != &other) {
    direction_ = std::move(other.direction_);
    speed_ = std::move(other.speed_);
    body_ = std::move(other.body_);
  }
  return *this;
}

Direction Snake::getDirection() {
    return direction_;
}

int Snake::getSpeed() {
  return speed_;
}

const std::vector<Point>& Snake::getBody() const {
    return body_;
}
void Snake::setDirection(Direction direction) {
    direction_ = direction;
}

Point Snake::calcAndGetNewHeadPos() {
  Point new_head = body_.back();
  switch (direction_) {
    case Direction::kRight:
      new_head.setX()++;
      break;
    case Direction::kDown:
      new_head.setY()++;
      break;
    case Direction::kLeft:
      new_head.setX()--;
      break;
    case Direction::kUp:
      new_head.setY()--;
      break;
  }

  return new_head;
}

void Snake::move(bool apple_eat) {
  Point new_head = calcAndGetNewHeadPos();

  body_.push_back(new_head);

  if (!apple_eat) {
    body_.erase(body_.begin());
  }
}

}  // namespace s21

