#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "./../../spec/game_spec.h"

#include "./objects_code.h"
#include "./point.h"

#define SNAKE_SIZE 4

namespace s21 {

class Snake {
 private:
  Direction direction_;
  std::vector<Point> body_;
  int speed_;

 public:
  Snake();
  Snake(const Snake& other);
  Snake(Snake&& other);

  Snake& operator=(const Snake& other);
  Snake& operator=(Snake&& other);

  void setDirection(Direction direction) {
    direction_ = direction;
  }

  Direction getDirection();
  const std::vector<Point>& getBody() const;

  void move(bool apple_eat = false);
  Point calcAndGetNewHeadPos();
  friend class SnakeGameTest;
};

}  // namespace s21

#endif  // SNAKE_H

