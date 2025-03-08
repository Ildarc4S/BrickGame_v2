#include "./include/timer.h"

namespace s21 {

Timer::Timer(int interval) 
  : interval_(interval),
    last_time_(std::chrono::steady_clock::now()) {}

int Timer::getInterval() {
  return interval_;
}

void Timer::setInterval(int interval) {
  interval_ = interval;
}

bool Timer::isExpired() {
  auto curr_time = std::chrono::steady_clock::now();
  auto diff_time = std::chrono::duration_cast<std::chrono::milliseconds>(curr_time - last_time_).count();
  return diff_time > interval_;
}

void Timer::update() {
  last_time_ = std::chrono::steady_clock::now();
}

}  // namespace s21
