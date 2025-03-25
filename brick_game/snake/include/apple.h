#ifndef APPLE_H
#define APPLE_H

#include <vector>

#include "./point.h"
#include "./../../spec/game_spec.h"

namespace s21 {

class Apple {
 private:
  Point position_;
 public:
  Apple();
  Apple(const std::vector<Point>& snake_body);

  Point getPosition() const;
  void setPosition(const Point& position);
  void genRandPosition(const std::vector<Point>& snake_body);
};

}  // namespace s21

#endif  // APPLE_H

