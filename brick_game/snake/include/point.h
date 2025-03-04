#pragma once

namespace s21 {

class Point {
 private:
  int x;
  int y;

 public:
  Point();
  Point(int x, int y);

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
};

}  // namespace s21
