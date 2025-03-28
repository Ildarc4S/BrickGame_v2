/**
 * @file timer.h
 * @brief Заголовочный файл класса Timer для работы с таймером
 */

#ifndef SNAKE_TIMER_H
#define SNAKE_TIMER_H

#include <chrono>

namespace s21 {

/**
 * @class Timer
 * @brief Класс для работы с таймером и измерения интервалов времени
 */
class Timer {
 private:
  int interval_;                              ///< Текущий интервал времени в миллисекундах
  int last_interval_;                         ///< Предыдущий интервал времени
  int default_interval_;                       ///< Интервал по умолчанию
  std::chrono::time_point<std::chrono::steady_clock> last_time_; ///< Время последнего обновления

 public:
  /**
   * @brief Конструктор класса Timer
   * @param interval Начальный интервал времени в миллисекундах
   */
  explicit Timer(int interval);

  /**
   * @brief Получить текущий интервал
   * @return Текущий интервал в миллисекундах
   */
  int getInterval();

  /**
   * @brief Получить последний сохраненный интервал
   * @return Последний сохраненный интервал в миллисекундах
   */
  int getLastInterval();

  /**
   * @brief Установить новый интервал
   * @param interval Новый интервал в миллисекундах
   * @param save Флаг сохранения текущего интервала перед изменением
   */
  void setInterval(int interval, bool save);

  /**
   * @brief Сохранить текущий интервал в last_interval_
   */
  void updateLastinterval();

  /**
   * @brief Сбросить интервалы к значениям по умолчанию
   */
  void resetInterval();

  /**
   * @brief Проверить, истек ли текущий интервал
   * @return true если интервал истек, false в противном случае
   */
  bool isExpired();

  /**
   * @brief Обновить время последнего отсчета
   */
  void update();
};

}  // namespace s21

#endif  // SNAKE_TIMER_H

