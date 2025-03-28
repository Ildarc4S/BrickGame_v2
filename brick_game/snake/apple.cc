/**
 * @file apple.cc
 * @brief Реализация класса Apple (яблоко в игре Змейка)
 */

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include "./include/apple.h"

namespace s21 {

// Конструктор с генерацией случайной позиции
Apple::Apple(const std::vector<Point>& snake_body) : position_() {
  srand(time(NULL));  // Инициализация генератора случайных чисел
  genRandPosition(snake_body);
}

// Генерация случайной позиции яблока
void Apple::genRandPosition(const std::vector<Point>& snake_body) {
  Point temp;
  do {
    // Генерация координат в диапазоне [1, FIELD_WIDTH/HEIGHT]
    temp = Point(rand() % FIELD_WIDTH + 1, rand() % FIELD_HEIGHT + 1);
  } while (std::find(snake_body.begin(), snake_body.end(), temp) != snake_body.end());
  position_ = temp;
}

// Получение текущей позиции яблока
Point Apple::getPosition() const {
  return position_;
}

// Установка позиции яблока вручную
void Apple::setPosition(const Point& position) {
  position_ = position;
}

}  // namespace s21
