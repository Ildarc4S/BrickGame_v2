#include "./include/window.h"

void drawPanelHead(Panel_t *this_) {
  attron(COLOR_PAIR(this_->color));
  mvprintw(this_->y - 1, (this_->x) * 2, "%s", this_->head_text);
  attroff(COLOR_PAIR(this_->color));
}

void drawFigure(Panel_t *this, GameInfo_t game_info) {
  if (!game_info.next) return;

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

void drawText(Panel_t *this) {
  for (int i = 0; i < this->size; i++) {
    mvprintw(this->y + i, this->x * 2, "%s", this->text[i]);
  }
}

void _drawPanel(Panel_t *this) {
  GameInfo_t game_info = updateCurrentState();
  if (!game_info.next) {
    drawPanelHead(this);
  }

  mvprintw(this->y, (this->x) * 2, "       ");  // Clean Field
  if (this->mode == PANEL_MODE_TEXT) {
    drawText(this);   
  } else if (this->mode == PANEL_MODE_HIGH_SCORE) {
    mvprintw(this->y, this->x * 2, "%d", game_info.high_score);
  } else if (this->mode == PANEL_MODE_SPEED) {
    mvprintw(this->y, this->x * 2, "%d", game_info.speed);
  } else if (this->mode == PANEL_MODE_LEVEL) {
    mvprintw(this->y, this->x * 2, "%d", game_info.level);
  } else if (this->mode == PANEL_MODE_CUR_SCORE) {
    mvprintw(this->y, this->x * 2, "%d", game_info.score);
  } else if (this->mode == PANEL_MODE_NEXT_FIGURE){
    drawFigure(this, game_info);
  }
}

void _drawWindow(Window_t *this) {
  this->game_field.drawField(&this->game_field);

  this->help_panel.draw(&this->help_panel);
  this->score_panel.draw(&this->score_panel);
  this->high_score_panel.draw(&this->high_score_panel);
  this->level_panel.draw(&this->level_panel);
  this->next_figure_panel.draw(&this->next_figure_panel);
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

bool _checkGameExit() {
  GameInfo_t game_info = updateCurrentState(); 
  return game_info.pause == PAUSE_MODE_EXIT;
}

void _drawField(GameField_t *this) {
  GameInfo_t game = updateCurrentState();
  if (game.pause == 0) {
    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        if (game.field[i][j] == OBJECT_CODE_WALL) {
          mvprintw(this->y + i, (this->x + j) * 2, "[]");
        } else if (isTetraminoCode(game.field[i][j])) {
          attron(COLOR_PAIR(game.field[i][j]));
          mvprintw(this->y + i, (this->x + j) * 2, "[]");
          attroff(COLOR_PAIR(game.field[i][j]));
        } else if (game.field[i][j] == OBJECT_CODE_AIR) {
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


Panel_t createPanel(int x, int y, 
                   const char *title, 
                   const char **text, 
                   int size, 
                   PanelColor_t color, 
                   PanelMode mode,
                   void (*drawFunc)(Panel_t*)) {
  Panel_t panel = {
      .x = x,
      .y = y,
      .head_text = "",
      .size = size,
      .color = color,
      .mode = mode,
      .draw = drawFunc,
  };
  strncpy(panel.head_text, title, sizeof(panel.head_text) - 1);

  for (int i = 0; i < size && i < 50; i++) {
    strncpy(panel.text[i], text[i], sizeof(panel.text[i]) - 1);
  }
  return panel;
}

GameField_t createGameField(int width, int height,
                            void (*drawFieldFunc)(GameField_t *)) {
  return (GameField_t){
      .x = 0,
      .y = 0,
      .width = width,
      .height = height,
      .drawField = drawFieldFunc,
  };
}

Window_t initWindow() {
  return (Window_t){
    .help_panel = createPanel(15, 16, "Help:",
                      (const char *[]){"Press q to quit", "Press p to pause",
                                       "Press left/right to move figure",
                                       "Press double down to move figure down",
                                       "Press s to start",
                                       "Press space to rotate figure"},
                      6,
                      PANEL_COLOR_GREEN, 
                      PANEL_MODE_TEXT,
                      _drawPanel),
      
      .next_figure_panel = createPanel(15, 1, "Next figure:", 
                                    NULL, 0,
                                    PANEL_COLOR_BLUE, 
                                    PANEL_MODE_NEXT_FIGURE,
                                    _drawPanel),
      
      .score_panel = createPanel(15, 8, "Score:", 
                               NULL, 0,
                               PANEL_COLOR_GREEN, 
                               PANEL_MODE_CUR_SCORE,
                               _drawPanel),
      
      .high_score_panel = createPanel(20, 8, "High value:", 
                                     NULL, 0,
                                     PANEL_COLOR_RED, 
                                     PANEL_MODE_HIGH_SCORE, // -4
                                     _drawPanel),
      
      .level_panel = createPanel(15, 12, "Level:", 
                               NULL, 0,
                               PANEL_COLOR_YELLOW, 
                               PANEL_MODE_LEVEL, // -6
                               _drawPanel),
      
      .speed_panel = createPanel(20, 12, "Speed:", 
                                NULL, 0,
                                PANEL_COLOR_GREEN, 
                                PANEL_MODE_SPEED, // -5
                                _drawPanel),
      
      .game_field = createGameField(FIELD_WIDTH + 2, FIELD_HEIGHT + 2,
                                   _drawField),
      .draw = _drawWindow,
      .checkGameExit = _checkGameExit
  };
}
