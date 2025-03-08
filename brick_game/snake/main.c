#include <ncurses.h>
#include "../spec/game_spec.h"

enum class FigureCode {
  AIR = 0,
  WALL,
  SNAKE,
  APPLE
};

void printField(GameInfo_t game_info) {
  clear();
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (game_info.field[i][j] == static_cast<int>(FigureCode::SNAKE)
          || game_info.field[i][j] == static_cast<int>(FigureCode::WALL)) {
        mvprintw(i, j * 2, "[]");
      } else if (game_info.field[i][j] == static_cast<int>(FigureCode::APPLE)) {
        mvprintw(i, j * 2, "()");
      } else {
        mvprintw(i, j * 2, "  ");
      }
    }
  }
  refresh();
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int i = 0;
    userInput(UserAction_t::Start, false);
    userInput(UserAction_t::Right, false);
    while (true) {
      printField(updateCurrentState());
      userInput(UserAction_t::Down, false);
      i++;
      napms(500);
    }

    endwin();
    return 0;
}
