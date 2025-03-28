/**
 * @file snake.h 
 * @brief Заголовочный файл класса Snake
 * 
 * Содержит объявление класса змейки для игры, включая методы управления
 * и данные о положении, направлении и скорости.
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "./../../spec/game_spec.h"
#include "./objects_code.h"
#include "./point.h"

namespace s21 {

#define SNAKE_SIZE 4          ///< Начальный размер змейки
#define MID_SIZE_DIVISOR 2    ///< Делитель для вычисления центра поля
#define SNAKE_DEFAULT_SPEED 1  ///< Скорость змейки по умолчанию

/**
 * @class Snake
 * @brief Класс, реализующий логику змейки в игре
 * 
 * Управляет перемещением, изменением направления и ростом змейки.
 * Содержит информацию о текущем положении всех сегментов тела.
 */
class Snake {
 private:
  Direction direction_;       ///< Текущее направление движения
  std::vector<Point> body_;  ///< Вектор точек, составляющих тело змейки
  int speed_;                ///< Текущая скорость перемещения

 public:
  /**
   * @brief Конструктор по умолчанию
   * 
   * Создает змейку начального размера в центре игрового поля,
   * направленную вправо.
   */
  Snake();

  /**
   * @brief Конструктор копирования
   * @param other Змейка для копирования
   */
  Snake(const Snake& other);

  /**
   * @brief Конструктор перемещения
   * @param other Змейка для перемещения
   */
  Snake(Snake&& other);

  /**
   * @brief Оператор присваивания копированием
   * @param other Змейка для копирования
   * @return Ссылка на текущий объект
   */
  Snake& operator=(const Snake& other);

  /**
   * @brief Оператор присваивания перемещением
   * @param other Змейка для перемещения
   * @return Ссылка на текущий объект
   */
  Snake& operator=(Snake&& other);

  /**
   * @brief Установить направление движения
   * @param direction Новое направление
   */
  void setDirection(Direction direction);

  /**
   * @brief Получить текущее направление
   * @return Текущее направление движения
   */
  Direction getDirection();

  /**
   * @brief Получить текущую скорость
   * @return Значение скорости
   */
  int getSpeed();

  /**
   * @brief Получить константную ссылку на тело змейки
   * @return Константная ссылка на вектор точек тела
   */
  const std::vector<Point>& getBody() const;

  /**
   * @brief Переместить змейку
   * @param apple_eat Флаг съедения яблока (true если змейка должна увеличиться)
   */
  void move(bool apple_eat = false);

  /**
   * @brief Вычислить новую позицию головы
   * @return Точка с новыми координатами головы
   */
  Point calcAndGetNewHeadPos();

  friend class SnakeGameTest; ///< Дружественный класс для тестирования
};

}  // namespace s21

#endif  // SNAKE_H

