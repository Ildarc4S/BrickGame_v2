#pragma once

#include <chrono>

namespace s21 {

class Timer {
 private:
  int interval_;
  std::chrono::time_point<std::chrono::steady_clock> last_time_;
 public:
  Timer(int interval);
  int getInterval();
  void setInterval(int interval);

  bool isExpired();
  void update();
};

}  // namespace s21
