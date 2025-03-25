#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TIMER_MILLISECONDS_PER_SECOND 1000
#define TIMER_MICROSECONDS_PER_MILLISECOND 1000
#define TIMER_INITIAL_TICK_INTERVAL 1000

typedef struct _timer {
  struct timeval current_time;
  struct timeval last_time;
  long tick;
  long default_tick;

  void (*updateCurrenTime)(struct _timer *timer);
  void (*updateLastTime)(struct _timer *timer);
  long (*calcDiff)(struct _timer *timer);
} Timer_t;

Timer_t initTimer();

#endif  // TIMER_H
