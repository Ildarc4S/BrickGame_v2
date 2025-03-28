#ifndef SNAKE_POINT_H
#define SNAKE_POINT_H

namespace s21 {

#define POINT_INIT_X -1
#define POINT_INIT_Y -1

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

#endif  // SNAKE_POINT_H

