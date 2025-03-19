#include "./timer.h"

void _updateCurrentTime(Timer_t *self) {
  struct timeval time = {0};
  gettimeofday(&time, NULL);
  self->current_time = time;
}

void _updateLastTime(Timer_t *self) {
  self->last_time = self->current_time;
}

long _calcTimeDiff(Timer_t *self) {
  self->updateCurrenTime(self);
  return (self->current_time.tv_sec - self->last_time.tv_sec) * 1000 +
         (self->current_time.tv_usec - self->last_time.tv_usec) / 1000;
}

Timer_t initTimer() {
  struct timeval time = {0};
  gettimeofday(&time, NULL);

  return (Timer_t) {
    .current_time = time,
    .last_time = time,
    .tick = 1000,
    .updateCurrenTime = _updateCurrentTime,
    .updateLastTime = _updateLastTime,
    .calcDiff = _calcTimeDiff,
  };
}
