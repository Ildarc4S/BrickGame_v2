#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>

#include "./objects.h"
#include "./color.h"

#define TEXT_SIZE 50
#define TEXT_LINE_COUNT 10

typedef struct _panel {
  int x; /**< X coordinate of the panel */
  int y; /**< Y coordinate of the panel */

  char head_text[TEXT_SIZE]; /**< Header text for the panel */
  char text[TEXT_LINE_COUNT][TEXT_SIZE];  /**< Text content of the panel */
  int size;           /**< Size of the panel (number of rows) */
  int value; /**< Value associated with the panel (e.g., score, level) */
  int mode;  /**< Mode of the panel (e.g., display mode) */

  Color_t color; /**< Color associated with the panel */

  void (*draw)(struct _panel *_this);
} Panel_t;

typedef struct _game_field {
  int x; /**< X coordinate of the game field */
  int y; /**< Y coordinate of the game field */

  int width;  /**< Width of the game field */
  int height; /**< Height of the game field */

  void (*drawField)(struct _game_field *);
  void (*drawTetramino)(struct _game_field *);
  void (*updateTetramino)(struct _game_field *);
} GameField_t;

typedef struct _window {
  Panel_t nextFigurePanel;  /**< Panel displaying the next figure */
  Panel_t scorePanel;       /**< Panel displaying the current score */
  Panel_t high_score_panel; /**< Panel displaying the high score */
  Panel_t levelPanel;       /**< Panel displaying the current level */
  Panel_t helpPanel;        /**< Panel displaying game help information */
  Panel_t speed_panel;      /**< Panel displaying the speed level */
  GameField_t game_field;   /**< The main game field */

  void (*draw)(struct _window *); /**< Function to draw the entire window */
} Window_t;

#endif  // WINDOW_H
