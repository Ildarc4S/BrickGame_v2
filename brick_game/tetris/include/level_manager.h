#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#define LEVEL_MANAGER_SCORE_CONVERTER_SIZE 4
#define LEVEL_MANAGER_INITIAL_SCORE 0
#define LEVEL_MANAGER_SCORE_FOR_ONE_LINE 100
#define LEVEL_MANAGER_SCORE_FOR_TWO_LINES 300
#define LEVEL_MANAGER_SCORE_FOR_THREE_LINES 700
#define LEVEL_MANAGER_SCORE_FOR_FOUR_LINES 1500

#define LEVEL_MANAGER_INITIAL_LEVEL 1
#define LEVEL_MANAGER_MAX_LEVEL_SCORE 600
#define LEVEL_MANAGER_MAX_LEVEL 10

typedef struct _score {
  int score;
  int score_converter[LEVEL_MANAGER_SCORE_CONVERTER_SIZE];
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
