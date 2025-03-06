/**
 * @file window.h
 * @brief Header file for defining structures and functions related to the game
 * window, panels, and game field.
 *
 * This file contains definitions for the structures that represent different
 * panels, game field, and the window as a whole. It also includes the function
 * prototypes for initializing and drawing the window and its components.
 *
 * @author Major Sweet
 * @date 2024-05-12
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <string.h>

#include "./init_frontend.h"

/**
 * @struct Panel_t
 * @brief Structure representing a panel in the game window.
 *
 * This structure holds the properties of a panel, including its position,
 * text content, color, and size. It also contains a pointer to a function
 * that will be used to draw the panel.
 */
typedef struct _panel {
  int x; /**< X coordinate of the panel */
  int y; /**< Y coordinate of the panel */

  char head_text[50]; /**< Header text for the panel */
  char text[50][50];  /**< Text content of the panel */
  int size;           /**< Size of the panel (number of rows) */
  int value; /**< Value associated with the panel (e.g., score, level) */
  int mode;  /**< Mode of the panel (e.g., display mode) */

  Color_t color; /**< Color associated with the panel */

  void (*draw)(
      struct _panel *_this); /**< Pointer to function for drawing the panel */
} Panel_t;

/**
 * @struct GameField_t
 * @brief Structure representing the game field.
 *
 * This structure holds the properties of the game field, such as its position,
 * dimensions, and a reference to the Tetris game state. It also includes
 * function pointers for drawing and updating the field and the tetrominoes.
 */
typedef struct _game_field {
  int x; /**< X coordinate of the game field */
  int y; /**< Y coordinate of the game field */

  int width;  /**< Width of the game field */
  int height; /**< Height of the game field */

  Tetris_t *tetris; /**< Pointer to the Tetris game state */

  void (*drawField)(
      struct _game_field *); /**< Function to draw the game field */
  void (*drawTetramino)(
      struct _game_field *); /**< Function to draw the falling tetromino */
  void (*updateTetramino)(
      struct _game_field *,
      Tetris_t *); /**< Function to update the tetromino position */
} GameField_t;

/**
 * @struct Window_t
 * @brief Structure representing the main game window.
 *
 * This structure contains all the panels and the game field that are part
 * of the window. It also includes a function pointer for drawing the entire
 * window.
 */
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

/**
 * @brief Constructs and initializes a window structure.
 *
 * This function initializes the window with the necessary components, such
 * as panels for next figure, score, high score, level, help, speed, and the
 * game field.
 *
 * @param tetris Pointer to the Tetris game state.
 * @return Initialized window structure.
 */
Window_t _constructorWindow(Tetris_t *tetris);

#endif  // WINDOW_H
