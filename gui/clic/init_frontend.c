#include <ncurses.h>

#include "./include/color.h"

void initColorPairs() {
  init_pair(TETRAMINO_COLOR_RED, COLOR_RED,
            COLOR_BLACK); /**< Red Tetrimino */
  init_pair(TETRAMINO_COLOR_YELLOW, COLOR_YELLOW,
            COLOR_BLACK); /**< Yellow Tetrimino */
  init_pair(TETRAMINO_COLOR_CYAN, COLOR_CYAN,
            COLOR_BLACK); /**< Cyan Tetrimino */
  init_pair(TETRAMINO_COLOR_GREEN, COLOR_GREEN,
            COLOR_BLACK); /**< Green Tetrimino */
  init_pair(TETRAMINO_COLOR_MAGNETA, COLOR_MAGENTA,
            COLOR_BLACK); /**< Magenta Tetrimino */
  init_pair(TETRAMINO_COLOR_BLUE, COLOR_BLUE,
            COLOR_BLACK); /**< Blue Tetrimino */

  init_pair(PANEL_COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK); /**< Yellow Panel */
  init_pair(PANEL_COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);   /**< Green Panel */
  init_pair(PANEL_COLOR_RED, COLOR_RED, COLOR_BLACK);       /**< Red Panel */
  init_pair(PANEL_COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);     /**< Blue Panel */
}

void initNcurses() {
  initscr();             /**< Initialize ncurses */
  cbreak();              /**< Disable line buffering */
  noecho();              /**< Disable echoing of typed characters */
  keypad(stdscr, TRUE);  /**< Enable special key input (e.g., arrow keys) */
  curs_set(0);           /**< Hide the cursor */
  nodelay(stdscr, TRUE); /**< Enable non-blocking input */
  start_color();         /**< Initialize color functionality */
  initColorPairs();      /**< Initialize color pairs for game elements */
  timeout(300);          /**< Set input timeout (in milliseconds) */
}

