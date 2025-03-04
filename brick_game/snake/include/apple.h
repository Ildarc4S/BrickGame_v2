#pragma once

#include <vector>

#include "./point.h"

namespace s21 {

class Apple {
 private:
  Point position_;
 public:
  Apple(const std::vector<Point>& snake_body); 

  Point getPosition();
  void genRandPosition(const std::vector<Point>& snake_body);
};

}  // namespace s21
