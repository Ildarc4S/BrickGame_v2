#include "./include/level_manager.h"

void _convertLineCountToScore(Score_t *self, int line_count) {
  self->score += self->score_converter[line_count - 1];
}

void _updateLevel(Level_t *self) {
  self->level = self->score.score / self->max_level_score + 1;
  if (self->level > self->max_level) {
    self->level = self->max_level;
  }
}

Score_t initScore() {
  return (Score_t){
      .score = LEVEL_MANAGER_INITIAL_SCORE,
      .score_converter = {
        LEVEL_MANAGER_SCORE_FOR_ONE_LINE, 
        LEVEL_MANAGER_SCORE_FOR_TWO_LINES, 
        LEVEL_MANAGER_SCORE_FOR_THREE_LINES, 
        LEVEL_MANAGER_SCORE_FOR_FOUR_LINES},
      .convertLineCountToScore = _convertLineCountToScore,
  };
}

Level_t initLevel() {
  return (Level_t){
      .score = initScore(),
      .level = LEVEL_MANAGER_INITIAL_LEVEL,
      .max_level_score = LEVEL_MANAGER_MAX_LEVEL_SCORE,
      .max_level = LEVEL_MANAGER_MAX_LEVEL,
      .updateLevel = _updateLevel
  };
}
