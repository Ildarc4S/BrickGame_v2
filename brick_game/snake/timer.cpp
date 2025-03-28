#include "./include/timer.h"

namespace s21 {

Timer::Timer(int interval)
  : interval_(interval),
    last_interval_(interval_),
    default_interval_(interval_),
    last_time_(std::chrono::steady_clock::now()) {}

int Timer::getInterval() {
  return interval_;
}

int Timer::getLastInterval() {
  return last_interval_;
}

void Timer::setInterval(int interval, bool save) {
  if (save) {
    updateLastinterval();
  }
  interval_ = interval;
}

void Timer::updateLastinterval() {
  last_interval_ = interval_;
}

void Timer::resetInterval() {
  last_interval_ = default_interval_;
  interval_ = default_interval_;
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
