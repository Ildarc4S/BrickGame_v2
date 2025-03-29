/**
 * @file game_singleton.cc
 * @brief Реализация класса-одиночки для игры Snake
 */

#include "./include/game_singleton.h"

namespace s21 {

/**
 * @brief Реализация метода получения экземпляра игры
 * @return Ссылка на единственный экземпляр SnakeGame
 *
 * Использует статическую переменную внутри функции для реализации:
 * - Отложенной инициализации
 * - Гарантированного уничтожения при завершении программы
 *
 */
SnakeGame& SnakeGameSingleton::getSnakeGame() {
  static SnakeGame snake_game;  // Инициализируется при первом вызове
  return snake_game;
}

}  // namespace s21
