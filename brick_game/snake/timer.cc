/**
 * @file timer.cc
 * @brief Реализация класса Timer для работы с таймером
 */

#include "./include/timer.h"

namespace s21 {

/**
 * @brief Конструктор класса Timer
 * @param interval Начальный интервал времени в миллисекундах
 */
Timer::Timer(int interval)
    : interval_(interval),
      last_interval_(interval_),
      default_interval_(interval_),
      last_time_(std::chrono::steady_clock::now()) {}

/**
 * @brief Получить текущий интервал
 * @return Текущий интервал в миллисекундах
 */
int Timer::getInterval() { return interval_; }

/**
 * @brief Получить последний сохраненный интервал
 * @return Последний сохраненный интервал в миллисекундах
 */
int Timer::getLastInterval() { return last_interval_; }

/**
 * @brief Установить новый интервал
 * @param interval Новый интервал в миллисекундах
 * @param save Флаг сохранения текущего интервала перед изменением
 */
void Timer::setInterval(int interval, bool save) {
  if (save) {
    updateLastinterval();
  }
  interval_ = interval;
}

/**
 * @brief Сохранить текущий интервал в last_interval_
 */
void Timer::updateLastinterval() { last_interval_ = interval_; }

/**
 * @brief Сбросить интервалы к значениям по умолчанию
 */
void Timer::resetInterval() {
  last_interval_ = default_interval_;
  interval_ = default_interval_;
}

/**
 * @brief Проверить, истек ли текущий интервал
 * @return true если интервал истек, false в противном случае
 */
bool Timer::isExpired() {
  auto curr_time = std::chrono::steady_clock::now();
  auto diff_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                       curr_time - last_time_)
                       .count();
  return diff_time > interval_;
}

/**
 * @brief Обновить время последнего отсчета
 */
void Timer::update() { last_time_ = std::chrono::steady_clock::now(); }

}  // namespace s21
