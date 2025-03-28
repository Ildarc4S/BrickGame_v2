/**
 * @file apple.cpp
 * @brief Реализация класса Apple (яблоко в игре Змейка)
 */

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include "./include/apple.h"

namespace s21 {

/**
 * @brief Конструктор с генерацией случайной позиции
 * @param snake_body Тело змейки для проверки коллизий
 * 
 * Инициализирует генератор случайных чисел и вызывает genRandPosition()
 * для установки начальной позиции яблока.
 */
Apple::Apple(const std::vector<Point>& snake_body) : position_() {
  srand(time(NULL));  // Инициализация генератора случайных чисел
  genRandPosition(snake_body);
}

/**
 * @brief Генерация случайной позиции яблока
 * @param snake_body Тело змейки для проверки коллизий
 * 
 * Алгоритм работы:
 * 1. Генерирует случайные координаты в пределах игрового поля
 * 2. Проверяет, не совпадает ли позиция с сегментами змейки
 * 3. Повторяет до тех пор, пока не найдется валидная позиция
 * 
 * @note Использует алгоритм std::find для проверки коллизий
 */
void Apple::genRandPosition(const std::vector<Point>& snake_body) {
  Point temp;
  do {
    // Генерация координат в диапазоне [1, FIELD_WIDTH/HEIGHT]
    temp = Point(rand() % FIELD_WIDTH + 1, rand() % FIELD_HEIGHT + 1);
  } while (std::find(snake_body.begin(), snake_body.end(), temp) != snake_body.end());
  position_ = temp;
}

/**
 * @brief Получение текущей позиции яблока
 * @return Точка с текущими координатами яблока
 */
Point Apple::getPosition() const {
  return position_;
}

/**
 * @brief Установка позиции яблока вручную
 * @param position Новая позиция яблока
 * 
 * @warning Не проверяет коллизии с телом змейки!
 * Для безопасной установки позиции следует использовать genRandPosition()
 */
void Apple::setPosition(const Point& position) {
  position_ = position;
}

}  // namespace s21
