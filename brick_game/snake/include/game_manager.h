/**
 * @file game_manager.h
 * @brief Заголовочный файл класса управления игрой Snake
 * 
 * Содержит объявление основного класса игры, управляющего всеми процессами:
 * - Состоянием игры
 * - Обработкой пользовательского ввода
 * - Логикой движения змейки
 * - Генерацией яблок
 * - Управлением таймером
 * - Работой с базой данных рекордов
 */

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "./../../spec/game_spec.h"
#include "./memory_utils.h"
#include "./point.h"
#include "./apple.h"
#include "./data_base.h"
#include "./timer.h"
#include "./snake.h"

namespace s21 {

#define INITIAL_TIMER 500     ///< Начальный интервал таймера (мс)
#define INITIAL_SPEED 10     ///< Начальная скорость игры
#define INITIAL_LEVEL 1      ///< Начальный уровень
#define INITIAL_SCORE 0      ///< Начальное количество очков
#define MAX_LEVEL 10         ///< Максимальный уровень
#define MAX_SCORE 200        ///< Максимальное количество очков
#define LEVEL_SCORE_THRESHOLD 5  ///< Порог очков для перехода на новый уровень
#define SCORE_INCREMENT 1    ///< Приращение очков за яблоко
#define SPEED_INCREMENT 1    ///< Приращение скорости за уровень
#define INTERVAL_DECREMENT 50  ///< Уменьшение интервала за уровень (мс)
#define BOOST_INTERVAL_DIVISOR 2  ///< Делитель интервала для ускоренного режима

/**
 * @class SnakeGame
 * @brief Основной класс управления игровым процессом
 * 
 * Реализует логику игры, обработку состояний и пользовательского ввода,
 * взаимодействие со всеми игровыми объектами.
 */
class SnakeGame {
 private:
  State state_;               ///< Текущее состояние игры
  UserAction_t action_;       ///< Последнее действие пользователя
  GameInfo_t game_info_;      ///< Структура с игровой информацией
  Timer timer_;              ///< Таймер для управления скоростью игры

  Snake snake_;              ///< Объект змейки
  Apple apple_;              ///< Объект яблока
  DataBase db_;              ///< База данных для хранения рекордов

  int max_level_score_;      ///< Макс. очки для перехода на след. уровень
  int max_level_;            ///< Максимально возможный уровень
  int max_score_;            ///< Максимально возможные очки
  int add_score_;            ///< Добавляемые очки за яблоко
  int add_speed_;            ///< Добавляемая скорость за уровень
  int interval_diff_;        ///< Разница интервалов между уровнями
  int interval_boost_diff_;  ///< Делитель интервала для ускоренного режима
  bool boost_time_;          ///< Флаг ускоренного режима

  /**
   * @brief Начало новой игры
   */
  void start();

  /**
   * @brief Генерация змейки и яблока
   */
  void spawn();

  /**
   * @brief Постановка игры на паузу
   */
  void pause();

  /**
   * @brief Выход из игры
   */
  void exit();

  /**
   * @brief Обработка съедания яблока
   */
  void eat();

  /**
   * @brief Обработка движения змейки
   * @param direction Направление движения
   * @param hold Флаг удержания клавиши
   */
  void moveHandle(Direction direction, bool hold);

  /**
   * @brief Проверка столкновения
   * @param head Позиция головы
   * @return true если есть столкновение
   */
  bool isCollision(const Point& head);

  /**
   * @brief Проверка столкновения с яблоком
   * @param head Позиция головы
   * @return true если голова достигла яблока
   */
  bool isAppleCollide(const Point& head);

  /**
   * @brief Проверка противоположного направления
   * @param direction Проверяемое направление
   * @return true если направление противоположно текущему
   */
  bool isOppositeDirection(const Direction& direction);

  /**
   * @brief Очистка игрового поля
   * @param width Ширина поля
   * @param height Высота поля
   */
  void clearField(int width, int height);

  /**
   * @brief Восстановление данных игры
   */
  void restoreGameInfoDate();

 public:
  /**
   * @brief Конструктор
   * 
   * Инициализирует игровое поле, таймер и начальные параметры игры.
   */
  SnakeGame();

  /**
   * @brief Деструктор
   * 
   * Освобождает память, занятую игровым полем.
   */
  ~SnakeGame();

  /**
   * @brief Переключение ускоренного режима
   */
  void toogleBoostTime();

  /**
   * @brief Обработчик начального состояния
   * @param action Действие пользователя
   */
  void startHandler(UserAction_t action);

  /**
   * @brief Обработчик движения
   * @param action Действие пользователя
   * @param hold Флаг удержания клавиши
   */
  void moveHandler(UserAction_t action, bool hold);

  /**
   * @brief Обработчик паузы
   * @param action Действие пользователя
   */
  void pauseHandler(UserAction_t action);

  /**
   * @brief Обработчик завершения игры
   * @param action Действие пользователя
   */
  void gameOverHandler(UserAction_t action);

  /**
   * @brief Обработка пользовательского ввода
   * @param action Действие пользователя
   * @param hold Флаг удержания клавиши
   */
  void userInput(UserAction_t action, bool hold);

  /**
   * @brief Получение текущего состояния игры
   * @return Структура с игровой информацией
   */
  GameInfo_t getGameInfo();

#ifdef SNAKE_TEST
  friend class SnakeGameTest;  ///< Дружественный класс для тестирования
#endif  // SNAKE_TEST
};

}  // namespace s21

#endif  // GAME_MANAGER_H

