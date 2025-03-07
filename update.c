#include "./brick_game/spec/game_spec.h"
#include <stdlib.h>

GameInfo_t updateCurrentState() {
  return (GameInfo_t) {
    .field = NULL,
    .next = NULL,
    .high_score = 0,
    .score = 0,
    .level = 0,
    .pause = 2,
    .speed = 10
  };
}

void userInput(UserAction_t action, bool hold) {

}
