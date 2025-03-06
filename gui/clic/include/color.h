#ifndef COLOR_H
#define COLOR_H

typedef enum {
  TETRAMINO_COLOR_RED = 2, /**< Red color for Tetramino */
  TETRAMINO_COLOR_YELLOW,  /**< Yellow color for Tetramino */
  TETRAMINO_COLOR_CYAN,    /**< Cyan color for Tetramino */
  TETRAMINO_COLOR_BLUE,    /**< Blue color for Tetramino */
  TETRAMINO_COLOR_GREEN,   /**< Green color for Tetramino */
  TETRAMINO_COLOR_MAGNETA, /**< Magenta color for Tetramino */

  PANEL_COLOR_GREEN = 7, /**< Green color for the panel */
  PANEL_COLOR_RED,       /**< Red color for the panel */
  PANEL_COLOR_YELLOW,    /**< Yellow color for the panel */
  PANEL_COLOR_BLUE,      /**< Blue color for the panel */
} Color_t;

#endif  // COLOR_H
