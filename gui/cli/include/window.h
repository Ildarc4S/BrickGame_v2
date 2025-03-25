#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>

#include "./objects.h"

#define WINDOW_TEXT_SIZE 50
#define WINDOW_TEXT_LINE_COUNT 12
#define WINDOW_CUR_TEXT_LINEC_COUNT 12
#define WINDOW_TEXT_LINE_COUNT_ZERO 0

#define WINDOW_FIELD_BORDER 2
#define WINDOW_CELL_WIDTH 2

#define WINDOW_SNAKE_HELP_TEXT_START 6
#define WINDOW_SNAKE_HELP_TEXT_COUNT 6

#define WINDOW_TETRIS_HELP_TEXT_START 0
#define WINDOW_TETRIS_HELP_TEXT_COUNT 6

#define WINDOW_CENTER_OFFSET 1
#define WINDOW_CENTER_DIVISOR 2

#define WINDOW_GAME_FIELD_INIT_X 0
#define WINDOW_GAME_FIELD_INIT_Y 0

#define WINDOW_PANEL_COLUMN_ONE_X 15
#define WINDOW_PANEL_COLUMN_TWO_X 20
#define WINDOW_PANEL_ROW_ONE_Y 8
#define WINDOW_PANEL_ROW_TWO_Y 12
#define WINDOW_PANEL_HELP_Y 16
#define WINDOW_PANEL_NEXT_FIGURE_Y 1

typedef struct _panel {
  int x;
  int y;

  char head_text[WINDOW_TEXT_SIZE];
  char text[WINDOW_TEXT_LINE_COUNT][WINDOW_TEXT_SIZE];
  int size;

  PanelMode_t mode;
  PanelColor_t color;

  void (*draw)(struct _panel *);
} Panel_t;

typedef struct _game_field {
  int x;
  int y;

  int width;
  int height;

  void (*drawField)(struct _game_field *);
} GameField_t;

typedef struct _window {
  Panel_t next_figure_panel;
  Panel_t score_panel;
  Panel_t high_score_panel;
  Panel_t level_panel;
  Panel_t help_panel;
  Panel_t speed_panel;
  GameField_t game_field;

  void (*draw)(struct _window *);
  bool (*checkGameExit)(void);
} Window_t;

Window_t initWindow();

#endif  // WINDOW_H
