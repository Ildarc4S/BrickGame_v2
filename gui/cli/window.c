#include "./include/window.h"

void drawPanelHead(Panel_t *self) {
  attron(COLOR_PAIR(self->color));
  mvprintw(self->y - 1, (self->x) * 2, "%s", self->head_text);
  attroff(COLOR_PAIR(self->color));
}

void drawFigure(Panel_t *self, GameInfo_t game_info) {
  if (!game_info.next) return;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvprintw(self->y + i + 1, (self->x + j + 1) * 2, "  ");
      if (game_info.next[i][j]) {
        attron(COLOR_PAIR(game_info.next[i][j]));
        mvprintw(self->y + i + 1, (self->x + j + 1) * 2, "[]");
        attroff(COLOR_PAIR(game_info.next[i][j]));
      }
    }
  }
}

void drawText(Panel_t *self) {
  GameInfo_t game_info = updateCurrentState();
  
  int start = 0;
  int count = 5;
  
  if (game_info.next == NULL) {
    start = 5;
    count = 5;
  }

  for (int i = 0; i < count && (start + i) < self->size; i++) {
    mvprintw(self->y + i, self->x * 2, "%s", self->text[start + i]);
  }
}

void _drawPanel(Panel_t *self) {
  GameInfo_t game_info = updateCurrentState();
  if (!(self->mode == PANEL_MODE_NEXT_FIGURE && !game_info.next)) {
    drawPanelHead(self);
  }

  mvprintw(self->y, (self->x) * 2, "       ");  // Clean Field
  if (self->mode == PANEL_MODE_TEXT) {
    drawText(self);   
  } else if (self->mode == PANEL_MODE_HIGH_SCORE) {
    mvprintw(self->y, self->x * 2, "%d", game_info.high_score);
  } else if (self->mode == PANEL_MODE_SPEED) {
    mvprintw(self->y, self->x * 2, "%d", game_info.speed);
  } else if (self->mode == PANEL_MODE_LEVEL) {
    mvprintw(self->y, self->x * 2, "%d", game_info.level);
  } else if (self->mode == PANEL_MODE_CUR_SCORE) {
    mvprintw(self->y, self->x * 2, "%d", game_info.score);
  } else if (self->mode == PANEL_MODE_NEXT_FIGURE){
    drawFigure(self, game_info);
  }
}

void _drawWindow(Window_t *self) {
  self->game_field.drawField(&self->game_field);

  self->help_panel.draw(&self->help_panel);
  self->score_panel.draw(&self->score_panel);
  self->high_score_panel.draw(&self->high_score_panel);
  self->level_panel.draw(&self->level_panel);
  self->next_figure_panel.draw(&self->next_figure_panel);
  self->speed_panel.draw(&self->speed_panel);
}

void drawCleanField(GameField_t *self) {
  for (int i = 0; i < self->height; i++) {
    for (int j = 0; j < self->width; j++) {
      if (i == self->height - 1 || j == self->width - 1 || i == 0 || j == 0) {
        mvprintw(self->y + i, (self->x + j) * 2, "[]");
      } else {
        mvprintw(self->y + i, (self->x + j) * 2, "  ");
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


void _drawField(GameField_t *self) {
  GameInfo_t game = updateCurrentState();

  for (int i = 0; i < self->height; i++) {
    for (int j = 0; j < self->width; j++) {
      mvprintw(self->y + i, (self->x + j) * 2, "  ");
    }
  }

  if (game.pause == PAUSE_MODE_GAME_CONTINUE) {
    for (int i = 0; i < self->height; i++) {
      for (int j = 0; j < self->width; j++) {
        
        if (game.field[i][j] == OBJECT_CODE_WALL) {
          mvprintw(self->y + i, (self->x + j) * 2, "[]");
        } else if (isTetraminoCode(game.field[i][j]) || game.field[i][j] == OBJECT_CODE_SNAKE) {
          attron(COLOR_PAIR(game.field[i][j]));
          mvprintw(self->y + i, (self->x + j) * 2, "[]");
          attroff(COLOR_PAIR(game.field[i][j]));
        } else if (game.field[i][j] == OBJECT_CODE_AIR) {
          mvprintw(self->y + i, (self->x + j) * 2, "  ");
        } else if (game.field[i][j] == OBJECT_CODE_APPLE) {
          mvprintw(self->y + i, (self->x + j) * 2, "()");
        }
      }
    }
  } else if (game.pause == PAUSE_MODE_START) {
    drawCleanField(self);
    mvprintw(self->height / 2, ((self->width - 1) / 2) * 2, "START");
  } else if (game.pause == PAUSE_MODE_PAUSE) {
    drawCleanField(self);
    mvprintw(self->height / 2, ((self->width - 1) / 2) * 2, "PAUSE");
  } else if (game.pause == PAUSE_MODE_GAME_OVER) {
    drawCleanField(self);
    mvprintw(self->height / 2, ((self->width - 1) / 2) * 2, "GAME_OVER");
  }
}


Panel_t createPanel(int x, int y, 
                   const char *title, 
                   const char **text, 
                   int size, 
                   PanelColor_t color, 
                   PanelMode_t mode,
                   void (*drawFunc)(Panel_t*)) {
  Panel_t panel = {
      .x = x,
      .y = y,
      .size = size,
      .mode = mode,
      .color = color,
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
