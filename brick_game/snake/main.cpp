#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "./include/snake.h"
#include "./include/point.h"

void printField(GameInfo_t game_info) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (game_info.field[i][j] == 2) {
        std::cout << "[]";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }
}



int main() {
  int i = 0;
  while (i < 3) {
    if (i == 0) {
      userInput(UserAction_t::Start, false);
    }
    printField(updateCurrentState());
    userInput(UserAction_t::Right, false);
    i++;
  }
}
