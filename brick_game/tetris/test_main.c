#include "./include/tetris.h"

void printField(int** field) {
  for (int i = 0; i < FIELD_HEIGHT+2; i++) { 
    for (int j = 0; j < FIELD_WIDTH+2; j++) { 
      printf("%+d ", field[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int i = 0;
  userInput(Start, 0); 
  while (i < 40) {
    userInput(Down, 0); 
    printField(updateCurrentState().field);
    printf("State: %d\n", initTetris()->state);
    printf("Pause: %d\n", initTetris()->game_info.pause);
    i++;
  }
  return 0;
}
