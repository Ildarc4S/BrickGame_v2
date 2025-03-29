/**
 * @file backend.cc
 * @brief Интерфейсный слой для взаимодействия с игрой на языке C
 * @details Предоставляет C-совместимые функции для управления игровым процессом
 */

#include "./include/game_singleton.h"

/**
 * @brief Обрабатывает пользовательский ввод
 *
 * Функция передает пользовательский ввод в игровой движок.
 * Пример использования:
 * @code
 * userInput(Up, false); // Одиночное нажатие вверх
 * userInput(Action, true); // Удержание функциональной клавиши
 * @endcode
 */
extern "C" void userInput(UserAction_t action, bool hold) {
  s21::SnakeGameSingleton::getSnakeGame().userInput(action, hold);
}

/**
 * @brief Получает текущее состояние игры
 * @return Структура GameInfo_t с актуальным состоянием игры
 *
 * Функция обновляет и возвращает текущее состояние игрового поля.
 * Содержит:
 * - Позиции всех объектов
 * - Текущий счет
 * - Уровень и скорость
 * - Состояние паузы/игры
 *
 * Пример использования:
 * @code
 * GameInfo_t info = updateCurrentState();
 * int score = info.score; // Получение текущего счета
 * @endcode
 */
extern "C" GameInfo_t updateCurrentState() {
  return s21::SnakeGameSingleton::getSnakeGame().getGameInfo();
}
