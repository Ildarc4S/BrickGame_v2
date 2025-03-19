#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#define SCORE_CONVERTER_SIZE 4

typedef struct _score {
  int score;
  int score_converter[SCORE_CONVERTER_SIZE];
  void (*convertLineCountToScore)(struct _score *, int);
} Score_t;

typedef struct _level {
  Score_t score;
  int level;
  int max_level_score;
  int max_level;
  void (*updateLevel)(struct _level *);
} Level_t;

Level_t initLevel();
Score_t initScore();

#endif  // LEVEL_MANAGER_H
