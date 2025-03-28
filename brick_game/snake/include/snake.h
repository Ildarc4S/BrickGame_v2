#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "./../../spec/game_spec.h"

#include "./objects_code.h"
#include "./point.h"

namespace s21 {

#define SNAKE_SIZE 4
#define MID_SIZE_DIVISOR 2
#define SNAKE_DEFAULT_SPEED 1

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

  void setDirection(Direction direction);

  Direction getDirection();
  int getSpeed();
  const std::vector<Point>& getBody() const;

  void move(bool apple_eat = false);
  Point calcAndGetNewHeadPos();
  friend class SnakeGameTest;
};

}  // namespace s21

#endif  // SNAKE_H

