/**
 * @file apple.h
 * @brief Заголовочный файл класса Apple (яблоко в игре Змейка)
 */

#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

#include <vector>

#include "./point.h"
#include "./../../spec/game_spec.h"

namespace s21 {

/**
 * @class Apple
 * @brief Класс, представляющий яблоко в игре Змейка
 * 
 * Отвечает за генерацию и хранение позиции яблока на игровом поле.
 * Автоматически проверяет, чтобы яблоко не появлялось на теле змейки.
 */
class Apple {
 private:
  Point position_; ///< Текущая позиция яблока на поле

 public:
  /**
   * @brief Конструктор по умолчанию
   */
  Apple();

  /**
   * @brief Конструктор с генерацией случайной позиции
   * @param snake_body Ссылка на вектор точек тела змейки
   * 
   * Инициализирует яблоко и сразу генерирует случайную позицию,
   * гарантируя, что яблоко не появится на теле змейки.
   */
  Apple(const std::vector<Point>& snake_body);

  /**
   * @brief Получить текущую позицию яблока
   * @return Точка с координатами яблока
   */
  Point getPosition() const;

  /**
   * @brief Установить позицию яблока вручную
   * @param position Новая позиция яблока
   */
  void setPosition(const Point& position);

  /**
   * @brief Сгенерировать новую случайную позицию для яблока
   * @param snake_body Ссылка на вектор точек тела змейки
   * 
   * Генерирует случайные координаты в пределах игрового поля,
   * гарантируя что яблоко не появится на теле змейки.
   */
  void genRandPosition(const std::vector<Point>& snake_body);
};

}  // namespace s21

#endif  // SNAKE_APPLE_H
