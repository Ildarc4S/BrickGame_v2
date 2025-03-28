/**
 * @file snake.cpp
 * @brief Реализация методов класса Snake
 */

#include "./include/snake.h"

namespace s21 {

/**
 * @brief Конструктор по умолчанию
 * 
 * Инициализирует змейку в центре поля, состоящую из SNAKE_SIZE сегментов,
 * направленную вправо, со скоростью по умолчанию.
 */
Snake::Snake()
  : direction_(Direction::kRight),
    body_(),
    speed_(SNAKE_DEFAULT_SPEED) {
  int mid_x = FIELD_WIDTH / MID_SIZE_DIVISOR;
  int mid_y = FIELD_HEIGHT / MID_SIZE_DIVISOR;

  for (int i = 0; i < SNAKE_SIZE; i++) {
    body_.emplace_back(mid_x + i, mid_y);
  }
}

/**
 * @brief Конструктор копирования
 * @param other Змейка для копирования
 */
Snake::Snake(const Snake& other)
  : direction_(other.direction_),
    body_(other.body_),
    speed_(other.speed_)
{}

/**
 * @brief Конструктор перемещения
 * @param other Змейка для перемещения
 */
Snake::Snake(Snake&& other)
  : direction_(std::move(other.direction_)),
    body_(std::move(other.body_)),
    speed_(std::move(other.speed_))
{}

/**
 * @brief Оператор присваивания копированием
 * @param other Змейка для копирования
 * @return Ссылка на текущий объект
 */
Snake& Snake::operator=(const Snake& other) {
  if (this != &other) {
    direction_ = other.direction_;
    speed_ = other.speed_;
    body_ = other.body_;
  }
  return *this;
}

/**
 * @brief Оператор присваивания перемещением
 * @param other Змейка для перемещения
 * @return Ссылка на текущий объект
 */
Snake& Snake::operator=(Snake&& other) {
  if (this != &other) {
    direction_ = std::move(other.direction_);
    speed_ = std::move(other.speed_);
    body_ = std::move(other.body_);
  }
  return *this;
}

/**
 * @brief Получить текущее направление
 * @return Текущее направление движения
 */
Direction Snake::getDirection() {
    return direction_;
}

/**
 * @brief Получить текущую скорость
 * @return Значение скорости
 */
int Snake::getSpeed() {
  return speed_;
}

/**
 * @brief Получить константную ссылку на тело змейки
 * @return Константная ссылка на вектор точек тела
 */
const std::vector<Point>& Snake::getBody() const {
    return body_;
}

/**
 * @brief Установить направление движения
 * @param direction Новое направление
 */
void Snake::setDirection(Direction direction) {
    direction_ = direction;
}

/**
 * @brief Вычислить новую позицию головы
 * @return Точка с новыми координатами головы
 * 
 * На основе текущего направления вычисляет координаты головы на следующем шаге.
 */
Point Snake::calcAndGetNewHeadPos() {
  Point new_head = body_.back();
  switch (direction_) {
    case Direction::kRight:
      new_head.setX()++;
      break;
    case Direction::kDown:
      new_head.setY()++;
      break;
    case Direction::kLeft:
      new_head.setX()--;
      break;
    case Direction::kUp:
      new_head.setY()--;
      break;
  }

  return new_head;
}

/**
 * @brief Переместить змейку
 * @param apple_eat Флаг съедения яблока (true если змейка должна увеличиться)
 * 
 * Добавляет новую голову в текущем направлении и при необходимости удаляет хвост.
 */
void Snake::move(bool apple_eat) {
  Point new_head = calcAndGetNewHeadPos();
  body_.push_back(new_head);

  if (!apple_eat) {
    body_.erase(body_.begin());
  }
}

}  // namespace s21
