#pragma once

#include <chrono>

namespace s21 {

class Timer {
 private:
  int interval_;
  int last_interval_;
  int default_interval_;
  std::chrono::time_point<std::chrono::steady_clock> last_time_;

 public:
  explicit Timer(int interval);
  int getInterval();
  int getLastInterval();
  int getDefaultInterval();

  void setInterval(int interval, bool save);
  void updateLastinterval();
  void resetInterval();

  bool isExpired();
  void update();
};

}  // namespace s21
