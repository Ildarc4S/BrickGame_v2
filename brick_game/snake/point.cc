/**
 * @file point.cc
 * @brief Реализация класса Point (точка в 2D пространстве)
 */

#include "./include/point.h"

namespace s21 {

/**
 * @brief Конструктор по умолчанию
 *
 * Инициализирует точку с начальными значениями (POINT_INIT_X, POINT_INIT_Y)
 */
Point::Point() : x_(POINT_INIT_X), y_(POINT_INIT_Y) {}

/**
 * @brief Конструктор с указанием координат
 * @param x Координата X
 * @param y Координата Y
 */
Point::Point(int x, int y) : x_(x), y_(y) {}

/**
 * @brief Получение координаты X
 * @return Текущее значение координаты X
 */
int Point::getX() const { return x_; }

/**
 * @brief Получение координаты Y
 * @return Текущее значение координаты Y
 */
int Point::getY() const { return y_; }

/**
 * @brief Получение ссылки на координату X для изменения
 * @return Ссылка на координату X
 *
 * @warning Изменение координаты через ссылку не проверяет допустимость
 * значений!
 */
int& Point::setX() { return x_; }

/**
 * @brief Получение ссылки на координату Y для изменения
 * @return Ссылка на координату Y
 *
 * @warning Изменение координаты через ссылку не проверяет допустимость
 * значений!
 */
int& Point::setY() { return y_; }

/**
 * @brief Оператор сравнения точек
 * @return true если координаты X и Y совпадают
 */
bool Point::operator==(const Point& other) const {
  return x_ == other.x_ && y_ == other.y_;
}

/**
 * @brief Оператор неравенства точек
 * @return true если координаты X или Y отличаются
 */
bool Point::operator!=(const Point& other) const { return !(*this == other); }

}  // namespace s21
