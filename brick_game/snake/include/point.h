/**
 * @file point.h
 * @brief Заголовочный файл класса Point (точка в 2D пространстве)
 */

#ifndef SNAKE_POINT_H
#define SNAKE_POINT_H

namespace s21 {

/**
 * @def Начальная координата X по умолчанию
 */
#define POINT_INIT_X -1

/**
 * @def Начальная координата Y по умолчанию
 */
#define POINT_INIT_Y -1

/**
 * @class Point
 * @brief Класс, представляющий точку в двумерном пространстве
 * 
 * Используется для хранения координат объектов в игре.
 * Поддерживает основные операции сравнения точек.
 */
class Point {
 private:
  int x_;  ///< Координата X точки
  int y_;  ///< Координата Y точки

 public:
  /**
   * @brief Конструктор по умолчанию
   * 
   * Инициализирует точку значениями (POINT_INIT_X, POINT_INIT_Y)
   */
  Point();

  /**
   * @brief Конструктор с указанием координат
   * @param x Координата X
   * @param y Координата Y
   */
  Point(int x, int y);

  /**
   * @brief Оператор сравнения точек
   * @param other Сравниваемая точка
   * @return true если точки равны, false иначе
   */
  bool operator==(const Point& other) const;

  /**
   * @brief Оператор неравенства точек
   * @param other Сравниваемая точка
   * @return true если точки не равны, false иначе
   */
  bool operator!=(const Point& other) const;

  /**
   * @brief Получить координату X
   * @return Значение координаты X
   */
  int getX() const;

  /**
   * @brief Получить координату Y
   * @return Значение координаты Y
   */
  int getY() const;

  /**
   * @brief Получить ссылку на координату X для изменения
   * @return Ссылка на координату X
   */
  int& setX();

  /**
   * @brief Получить ссылку на координату Y для изменения
   * @return Ссылка на координату Y
   */
  int& setY();
};

}  // namespace s21

#endif  // SNAKE_POINT_H

