#include "./include/window.h"

void _drawPanelHead(Panel_t *this) {
  attron(COLOR_PAIR(this->color));
  mvprintw(this->y - 1, (this->x) * 2, "%s", this->head_text);
  attroff(COLOR_PAIR(this->color));
}

void drawFigure(Panel_t *this, GameInfo_t game_info) {
  if (!this || !game_info.next) return;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvprintw(this->y + i + 1, (this->x + j + 1) * 2, "  ");
      if (game_info.next[i][j]) {
        attron(COLOR_PAIR(game_info.next[i][j]));
        mvprintw(this->y + i + 1, (this->x + j + 1) * 2, "[]");
        attroff(COLOR_PAIR(game_info.next[i][j]));
      }
    }
  }
}

void _drawPanel(Panel_t *this) {
  GameInfo_t game_info = updateCurrentState();
  _drawPanelHead(this);

  mvprintw(this->y, (this->x) * 2, "       ");  // Clean Field
  if (this->size != 0) {
    for (int i = 0; i < this->size; i++) {
      mvprintw(this->y + i, this->x * 2, "%s", this->text[i]);
    }
  } else if (this->mode == -2 || this->mode == -3 || this->mode == -4 ||
             this->mode == -5) {
    if (this->mode == -3) {
      this->value = game_info.speed;
    } else if (this->mode == -2) {
      this->value = game_info.high_score;
    } else if (this->mode == -5) {
      this->value = game_info.score;
    } else if (this->mode == -4) {
      this->value = game_info.level;
    }
    mvprintw(this->y, this->x * 2, "%d", this->value);
  } else {
    drawFigure(this, game_info);
  }
}

void _drawWindow(Window_t *this) {
  this->game_field.drawField(&this->game_field);
  this->game_field.drawTetramino(&this->game_field);

  this->helpPanel.draw(&this->helpPanel);
  this->scorePanel.draw(&this->scorePanel);
  this->high_score_panel.draw(&this->high_score_panel);
  this->levelPanel.draw(&this->levelPanel);
  this->nextFigurePanel.draw(&this->nextFigurePanel);
  this->speed_panel.draw(&this->speed_panel);
}

void drawCleanField(GameField_t *this) {
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      if (i == this->height - 1 || j == this->width - 1 || i == 0 || j == 0) {
        mvprintw(this->y + i, (this->x + j) * 2, "[]");
      } else {
        mvprintw(this->y + i, (this->x + j) * 2, "  ");
      }
    }
  }
}

bool isTetraminoCode(int field_code) {
  return field_code == OBJECT_CODE_TETRAMINO_I
         || field_code == OBJECT_CODE_TETRAMINO_O
         || field_code == OBJECT_CODE_TETRAMINO_T
         || field_code == OBJECT_CODE_TETRAMINO_S
         || field_code == OBJECT_CODE_TETRAMINO_Z
         || field_code == OBJECT_CODE_TETRAMINO_J
         || field_code == OBJECT_CODE_TETRAMINO_L;
}

void _drawField(GameField_t *this) {
  GameInfo_t game = updateCurrentState();
  if (game.pause == 0) {
    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        if (game.field[i][j] == WALL) {
          mvprintw(this->y + i, (this->x + j) * 2, "[]");
        } else if (isTetraminoCode(game.field[i][j]))
          attron(COLOR_PAIR(game.field[i][j]));
          mvprintw(this->y + i, (this->x + j) * 2, "[]");
          attroff(COLOR_PAIR(game.field[i][j]));
        else {
          mvprintw(this->y + i, (this->x + j) * 2, "  ");
        }
      }
    }
  } else if (game.pause == PAUSE_MODE_START) {
    drawCleanField(this);
    mvprintw(this->height / 2, ((this->width - 1) / 2) * 2, "START");
  } else if (game.pause == PAUSE_MODE_PAUSE) {
    drawCleanField(this);
    mvprintw(this->height / 2, ((this->width - 1) / 2) * 2, "PAUSE");
  } else if (game.pause == PAUSE_MODE_GAME_OVER) {
    drawCleanField(this);
    mvprintw(this->height / 2, ((this->width - 1) / 2) * 2, "GAME_OVER");
  }
}


Panel_t createPanel(int x, int y, const char *head_text, const char *text[],
                    int size, Color_t color, int value, int mode,
                    void (*drawFunc)(Panel_t *)) {
  Panel_t panel = {
      .x = x,
      .y = y,
      .head_text = "",
      .size = size,
      .color = color,
      .value = value,
      .mode = mode,
      .draw = drawFunc,
  };
  strncpy(panel.head_text, head_text, sizeof(panel.head_text) - 1);

  for (int i = 0; i < size && i < 50; i++) {
    strncpy(panel.text[i], text[i], sizeof(panel.text[i]) - 1);
  }
  return panel;
}

GameField_t createGameField(Tetris_t *tetris, int width, int height,
                            void (*drawFieldFunc)(GameField_t *),
                            void (*drawTetraminoFunc)(GameField_t *)) {
  return (GameField_t){
      .x = 0,
      .y = 0,
      .width = width,
      .height = height,
      .tetris = tetris,
      .drawField = drawFieldFunc,
      .drawTetramino = drawTetraminoFunc,
  };
}

Window_t initWindow(Tetris_t *tetris) {
  return (Window_t){
      .helpPanel =
          createPanel(15, 16, "Help:",
                      (const char *[]){"Press q to quit", "Press p to pause",
                                       "Press left/right to move figure",
                                       "Press double down to move figure down",
                                       "Press s to start",
                                       "Press space to rotate figure"},
                      5, PANEL_COLOR_GREEN, -1, -1, _drawPanel),
      .nextFigurePanel = createPanel(15, 1, "Next figure:", NULL, 0,
                                     PANEL_COLOR_BLUE, -1, -1, _drawPanel),
      .scorePanel = createPanel(15, 8, "Score:", NULL, 0, PANEL_COLOR_GREEN, 0,
                                -5, _drawPanel),
      .high_score_panel = createPanel(20, 8, "High value:", NULL, 0,
                                      PANEL_COLOR_RED, 0, -2, _drawPanel),
      .levelPanel = createPanel(15, 12, "Level:", NULL, 0, PANEL_COLOR_YELLOW,
                                0, -4, _drawPanel),
      .speed_panel = createPanel(20, 12, "Speed:", NULL, 0, PANEL_COLOR_GREEN,
                                 0, -3, _drawPanel),
      .game_field = createGameField(tetris, FIELD_WIDTH + 2, FIELD_HEIGHT + 2,
                                    _drawField, _drawTetramino),
      .draw = _drawWindow,
  };
}
