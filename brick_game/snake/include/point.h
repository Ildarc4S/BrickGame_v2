#ifndef POINT_H
#define POINT_H

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

  int getX() const {
    return x;
  }

  int getY() const {
    return y;
  }

  int& setX() {
    return x;
  }

  int& setY() {
    return y;
  }
};

}  // namespace s21

#endif  // POINT_H
