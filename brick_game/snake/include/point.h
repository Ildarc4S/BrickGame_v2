#ifndef POINT_H
#define POINT_H

namespace s21 {

class Point {
 private:
  int x_;
  int y_;

 public:
  Point();
  Point(int x, int y);

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;

  int getX() const;
  int getY() const;
  int& setX();
  int& setY();
};

}  // namespace s21

#endif  // POINT_H
