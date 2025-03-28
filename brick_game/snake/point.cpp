#include "./include/point.h"

namespace s21 {

Point::Point() : x_(POINT_INIT_X), y_(POINT_INIT_Y) {}
Point::Point(int x_, int y_) : x_(x_), y_(y_) {}

int Point::getX() const {
    return x_;
}

int Point::getY() const {
    return y_;
}

int&  Point::setX() {
    return x_;
}

int&  Point::setY() {
    return y_;
}

bool Point::operator==(const Point& other) const {
  return x_ == other.x_ && y_ == other.y_;
}

bool Point::operator!=(const Point& other) const {
  return !(*this == other);
}

}  // namespace s21

