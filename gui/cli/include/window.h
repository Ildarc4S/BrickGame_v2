#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>

#include "./objects.h"

#define TEXT_SIZE 50
#define TEXT_LINE_COUNT 10
#define CUR_TEXT_LINEC_COUNT 6

typedef struct _panel {
  int x;
  int y;

  char head_text[TEXT_SIZE];
  char text[TEXT_LINE_COUNT][TEXT_SIZE];
  int size;

  PanelMode mode;
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
