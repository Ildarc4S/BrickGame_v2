#include "./include/timer.h"

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
  return (self->current_time.tv_sec - self->last_time.tv_sec) * TIMER_MILLISECONDS_PER_SECOND +
         (self->current_time.tv_usec - self->last_time.tv_usec) / TIMER_MICROSECONDS_PER_MILLISECOND;
}

Timer_t initTimer() {
  struct timeval time = {0};
  gettimeofday(&time, NULL);

  return (Timer_t){
      .current_time = time,
      .last_time = time,
      .tick = TIMER_INITIAL_TICK_INTERVAL,
      .updateCurrenTime = _updateCurrentTime,
      .updateLastTime = _updateLastTime,
      .calcDiff = _calcTimeDiff,
  };
}
