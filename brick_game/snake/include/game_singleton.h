/**
 * @file game_singleton.h
 * @brief Заголовочный файл класса-одиночки для игры Snake
 */

#ifndef SNAKE_GAME_SINGLETON_H
#define SNAKE_GAME_SINGLETON_H

#include "./game_manager.h"

namespace s21 {

/**
 * @class SnakeGameSingleton
 * @brief Класс-одиночка для управления экземпляром игры Snake
 * 
 * Реализует шаблон Singleton для обеспечения единственного экземпляра игры.
 * Запрещает копирование и присваивание. Предоставляет глобальную точку доступа
 * к единственному экземпляру игры.
 */
class SnakeGameSingleton {
 private:
  SnakeGameSingleton() = default;      ///< Приватный конструктор по умолчанию
  ~SnakeGameSingleton() = default;    ///< Приватный деструктор

  /**
   * @brief Запрет копирования
   */
  SnakeGameSingleton(const SnakeGameSingleton&) = delete;

  /**
   * @brief Запрет присваивания
   */
  SnakeGameSingleton& operator=(const SnakeGameSingleton&) = delete;

 public:
  /**
   * @brief Получить ссылку на единственный экземпляр игры
   * @return Ссылка на экземпляр SnakeGame
   * 
   * Реализует отложенную инициализацию при первом вызове.
   * Гарантирует создание только одного экземпляра на протяжении работы программы.
   */
  static SnakeGame& getSnakeGame();
};

}  // namespace s21

#endif  // SNAKE_GAME_SINGLETON_H

