#include "./level_manager.h"

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
    .score = 0,
    .score_converter = {100, 300, 700, 1500},
    .convertLineCountToScore = _convertLineCountToScore,
  };
}

Level_t initLevel() {
  return (Level_t){
    .score = initScore(),
    .level = 1,
    .max_level_score = 600,
    .max_level = 10,
    .updateLevel = _updateLevel};
}
