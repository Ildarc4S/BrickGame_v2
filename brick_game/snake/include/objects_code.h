/**
 * @file objects_code.h
 * @brief Заголовочный файл с перечислениями состояний игры и объектов
 */

#ifndef SNAKE_OBJECTS_CODE_H
#define SNAKE_OBJECTS_CODE_H

namespace s21 {

/**
 * @enum State
 * @brief Состояния игры
 * 
 * Перечисление всех возможных состояний игрового процесса
 */
enum class State {
  kStart = 0,     ///< Начальное состояние игры
  kSpawn,         ///< Состояние появления объектов
  kMove,          ///< Состояние движения змейки
  kEat,           ///< Состояние поедания яблока
  kPause,         ///< Игра на паузе
  kGameOver,      ///< Конец игры (проигрыш)
  kExit           ///< Выход из игры
};

/**
 * @enum Direction
 * @brief Направления движения
 * 
 * Перечисление возможных направлений движения змейки
 */
enum class Direction {
  kUp,            ///< Движение вверх
  kDown,          ///< Движение вниз
  kLeft,          ///< Движение влево
  kRight          ///< Движение вправо
};

/**
 * @enum PauseMode
 * @brief Режимы паузы
 * 
 * Перечисление возможных режимов работы меню паузы
 */
enum class PauseMode {
  kPause = 1,         ///< Игра на паузе
  kGameContinue = 2,  ///< Продолжение игры
  kStart = 3,         ///< Начало новой игры
  kGameOver = 4,      ///< Конец игры
  kExit = 5,          ///< Выход из игры
  kWin = 6            ///< Победа в игре
};

/**
 * @enum FigureCode
 * @brief Коды объектов игры
 * 
 * Перечисление идентификаторов игровых объектов на карте
 */
enum class FigureCode {
  kAir = -2,      ///< Пустое пространство
  kWall = -1,     ///< Стена/препятствие
  kSnake = 10,    ///< Сегмент змейки
  kApple = 11     ///< Яблоко (еда)
};

}  // namespace s21

#endif  // SNAKE_OBJECTS_CODE_H

