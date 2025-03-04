#include "./include/point.h"

namespace s21 {

Point::Point() : x(-1), y(-1) {}
Point::Point(int x, int y) : x(x), y(y) {}

bool Point::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
  return !(*this == other);
}

}  // namespace s21

