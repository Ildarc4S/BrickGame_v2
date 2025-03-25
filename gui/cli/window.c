#include "./include/window.h"

void drawPanelHead(Panel_t *self) {
  attron(COLOR_PAIR(self->color));
  mvprintw(self->y - 1, (self->x) * WINDOW_CELL_WIDTH, "%s", self->head_text);
  attroff(COLOR_PAIR(self->color));
}

void drawFigure(Panel_t *self, GameInfo_t game_info) {
  if (!game_info.next) return;

  for (int i = 0; i < TETRAMINO_HEIGHT; i++) {
    for (int j = 0; j < TETRAMINO_WIDTH; j++) {
      mvprintw(self->y + i + 1, (self->x + j + 1) * WINDOW_CELL_WIDTH, "  ");
      if (game_info.next[i][j]) {
        attron(COLOR_PAIR(game_info.next[i][j]));
        mvprintw(self->y + i + 1, (self->x + j + 1) * WINDOW_CELL_WIDTH, "[]");
        attroff(COLOR_PAIR(game_info.next[i][j]));
      }
    }
  }
}

void drawText(Panel_t *self) {
  GameInfo_t game_info = updateCurrentState();
  
  int start = WINDOW_TETRIS_HELP_TEXT_START;
  int count = WINDOW_TETRIS_HELP_TEXT_COUNT;
  
  if (game_info.next == NULL) {
    start = WINDOW_SNAKE_HELP_TEXT_START;
    count = WINDOW_SNAKE_HELP_TEXT_COUNT;
  }
  for (int i = 0; i < count && (start + i) < self->size; i++) {
    mvprintw(self->y + i, self->x * WINDOW_CELL_WIDTH, "%s", self->text[start + i]);
  }
}

void _drawPanel(Panel_t *self) {
  GameInfo_t game_info = updateCurrentState();
  if (!(self->mode == PANEL_MODE_NEXT_FIGURE && !game_info.next)) {
    drawPanelHead(self);
  }

  mvprintw(self->y, (self->x) * WINDOW_CELL_WIDTH, "       ");  // Clean Field
  if (self->mode == PANEL_MODE_TEXT) {
    drawText(self);   
  } else if (self->mode == PANEL_MODE_HIGH_SCORE) {
    mvprintw(self->y, self->x * WINDOW_CELL_WIDTH, "%d", game_info.high_score);
  } else if (self->mode == PANEL_MODE_SPEED) {
    mvprintw(self->y, self->x * WINDOW_CELL_WIDTH, "%d", game_info.speed);
  } else if (self->mode == PANEL_MODE_LEVEL) {
    mvprintw(self->y, self->x * WINDOW_CELL_WIDTH, "%d", game_info.level);
  } else if (self->mode == PANEL_MODE_CUR_SCORE) {
    mvprintw(self->y, self->x * WINDOW_CELL_WIDTH, "%d", game_info.score);
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
        mvprintw(self->y + i, (self->x + j) * WINDOW_CELL_WIDTH, "[]");
      } else {
        mvprintw(self->y + i, (self->x + j) * WINDOW_CELL_WIDTH, "  ");
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
      mvprintw(self->y + i, (self->x + j) * WINDOW_CELL_WIDTH, "  ");
    }
  }

  if (game.pause == PAUSE_MODE_GAME_CONTINUE) {
    for (int i = 0; i < self->height; i++) {
      for (int j = 0; j < self->width; j++) {
        if (game.field[i][j] == OBJECT_CODE_WALL) {
          mvprintw(self->y + i, (self->x + j) * WINDOW_CELL_WIDTH, "[]");
        } else if (isTetraminoCode(game.field[i][j]) || game.field[i][j] == OBJECT_CODE_SNAKE) {
          attron(COLOR_PAIR(game.field[i][j]));
          mvprintw(self->y + i, (self->x + j) * WINDOW_CELL_WIDTH, "[]");
          attroff(COLOR_PAIR(game.field[i][j]));
        } else if (game.field[i][j] == OBJECT_CODE_AIR) {
          mvprintw(self->y + i, (self->x + j) * WINDOW_CELL_WIDTH, "  ");
        } else if (game.field[i][j] == OBJECT_CODE_APPLE) {
          attron(COLOR_PAIR(game.field[i][j]));
          mvprintw(self->y + i, (self->x + j) * WINDOW_CELL_WIDTH, "()");
          attroff(COLOR_PAIR(game.field[i][j]));
        }
      }
    }
  } else if (game.pause == PAUSE_MODE_START) {
    drawCleanField(self);
    mvprintw(self->height / WINDOW_CENTER_DIVISOR, ((self->width - WINDOW_CENTER_OFFSET) / WINDOW_CENTER_DIVISOR) * WINDOW_CELL_WIDTH, "START");
  } else if (game.pause == PAUSE_MODE_PAUSE) {
    drawCleanField(self);
    mvprintw(self->height / WINDOW_CENTER_DIVISOR, ((self->width - WINDOW_CENTER_OFFSET) / WINDOW_CENTER_DIVISOR) * WINDOW_CELL_WIDTH, "PAUSE");
  } else if (game.pause == PAUSE_MODE_GAME_OVER) {
    drawCleanField(self);
    mvprintw(self->height / WINDOW_CENTER_DIVISOR, ((self->width - WINDOW_CENTER_OFFSET) / WINDOW_CENTER_DIVISOR) * WINDOW_CELL_WIDTH, "GAME_OVER");
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

  for (int i = 0; i < size && i < WINDOW_TEXT_SIZE; i++) {
    strncpy(panel.text[i], text[i], sizeof(panel.text[i]) - 1);
  }
  return panel;
}

GameField_t createGameField(int width, int height,
                            void (*drawFieldFunc)(GameField_t *)) {
  return (GameField_t){
      .x = WINDOW_GAME_FIELD_INIT_X,
      .y = WINDOW_GAME_FIELD_INIT_Y,
      .width = width,
      .height = height,
      .drawField = drawFieldFunc,
  };
}

Window_t initWindow() {
  return (Window_t){
    .help_panel = createPanel(WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_HELP_Y, "Help:",
                      (const char *[]){"Press q to quit", 
                                       "Press p to pause",
                                       "Press s to start",
                                       "Press left/right to move figure",
                                       "Press down to move figure down",
                                       "Press space to rotate figure",
                                       "Press q to quit", 
                                       "Press p to pause",
                                       "Press s to start",
                                       "Press left/right to move snake horizontally",
                                       "Press up/down to move snake vertically",
                                       "Press space to boost snake"},
                      WINDOW_TEXT_LINE_COUNT,
                      PANEL_COLOR_GREEN, 
                      PANEL_MODE_TEXT,
                      _drawPanel),
      
      .next_figure_panel = createPanel(WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_NEXT_FIGURE_Y, "Next figure:", 
                                    NULL, WINDOW_TEXT_LINE_COUNT_ZERO,
                                    PANEL_COLOR_BLUE, 
                                    PANEL_MODE_NEXT_FIGURE,
                                    _drawPanel),
      
      .score_panel = createPanel(WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_ROW_ONE_Y, "Score:", 
                               NULL, WINDOW_TEXT_LINE_COUNT_ZERO,
                               PANEL_COLOR_GREEN, 
                               PANEL_MODE_CUR_SCORE,
                               _drawPanel),
      
      .high_score_panel = createPanel(WINDOW_PANEL_COLUMN_TWO_X, WINDOW_PANEL_ROW_ONE_Y, "High value:", 
                                     NULL, WINDOW_TEXT_LINE_COUNT_ZERO,
                                     PANEL_COLOR_RED, 
                                     PANEL_MODE_HIGH_SCORE,
                                     _drawPanel),
      
      .level_panel = createPanel(WINDOW_PANEL_COLUMN_ONE_X, WINDOW_PANEL_ROW_TWO_Y, "Level:", 
                               NULL, WINDOW_TEXT_LINE_COUNT_ZERO,
                               PANEL_COLOR_YELLOW, 
                               PANEL_MODE_LEVEL,
                               _drawPanel),
      
      .speed_panel = createPanel(WINDOW_PANEL_COLUMN_TWO_X, WINDOW_PANEL_ROW_TWO_Y, "Speed:", 
                                NULL, WINDOW_TEXT_LINE_COUNT_ZERO,
                                PANEL_COLOR_GREEN, 
                                PANEL_MODE_SPEED,
                                _drawPanel),
      
      .game_field = createGameField(FIELD_WIDTH + WINDOW_FIELD_BORDER, FIELD_HEIGHT + WINDOW_FIELD_BORDER,
                                   _drawField),
      .draw = _drawWindow,
      .checkGameExit = _checkGameExit
  };
}
