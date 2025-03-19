#ifndef GAME_SCPEC_H
#define GAME_SCPEC_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

#include <stdbool.h>

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

#ifdef __cplusplus
extern "C" {
#endif

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#ifdef __cplusplus
}
#endif

#endif  // GAME_SCPEC_H

