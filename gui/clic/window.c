#include "./include/window.h"

/**
 * @brief Draws the header of a panel.
 *
 * This function draws the header of a panel at the specified coordinates. The
 * header text is displayed using the color specified for the panel.
 *
 * @param this A pointer to the panel to draw.
 */
void _drawPanelHead(Panel_t *this) {
  attron(COLOR_PAIR(this->color));
  mvprintw(this->y - 1, (this->x) * 2, "%s", this->head_text);
  attroff(COLOR_PAIR(this->color));
}

/**
 * @brief Draws the figure on the next figure panel.
 *
 * This function draws the next tetromino figure on the next figure panel if
 * there is a figure to display. It iterates over the cells of a 4x4 grid and
 * prints the blocks of the tetromino in the next figure position.
 *
 * @param this A pointer to the panel to draw on.
 * @param game_info A structure containing the current game state, including the
 * next tetromino.
 */
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

/**
 * @brief Draws the entire panel.
 *
 * This function draws the entire panel, including the header and content based
 * on the mode and value. It checks for the panel's mode and adjusts the drawing
 * accordingly (e.g., drawing score, high score, etc.).
 * - **`mode == -2`**: Displays the **high score**. The highest score achieved
 * in the game.
 * - **`mode == -3`**: Displays the **game speed**. The current speed of the
 * game, which increases with levels.
 * - **`mode == -4`**: Displays the **current level**. The level that the player
 * is currently on.
 * - **`mode == -5`**: Displays the **current score**. The player's current
 * score in the ongoing game.
 *
 * @param this A pointer to the panel to draw.
 */
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

/**
 * @brief Draws the entire window.
 *
 * This function draws all the panels and the game field by calling the drawing
 * functions for each of the panels and the game field. It ensures the whole
 * game state is displayed correctly.
 *
 * @param this A pointer to the window to draw.
 */
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

/**
 * @brief Draws a clean field (bordered empty field).
 *
 * This function draws a clean game field with borders around it. The empty
 * spaces inside the borders are represented by spaces, and the borders are
 * represented by the "[]" block symbol.
 *
 * @param this A pointer to the game field to draw.
 */
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

void _drawField(GameField_t *this) {
  GameInfo_t game = updateCurrentState();
  if (game.pause == 0) {
    for (int i = 0; i < this->height; i++) {
      for (int j = 0; j < this->width; j++) {
        if (game.field[i][j]) {
          mvprintw(this->y + i, (this->x + j) * 2, "[]");
        } else {
          mvprintw(this->y + i, (this->x + j) * 2, "  ");
        }
      }
    }
  } else if (game.pause == 2) {
    drawCleanField(this);
    mvprintw(this->height / 2, ((this->width - 1) / 2) * 2, "START");
  } else if (game.pause == 1) {
    drawCleanField(this);
    mvprintw(this->height / 2, ((this->width - 1) / 2) * 2, "PAUSE");
  } else if (game.pause == -1) {
    drawCleanField(this);
    mvprintw(this->height / 2, ((this->width - 1) / 2) * 2, "GAME_OVER");
  }
}


void _drawTetramino(GameField_t *this) {
  Tetramino_t *tetramino = this->tetris->info.curr_tetramino;
  if (!tetramino) return;
  if (this->tetris->info.game_info.pause != 0) return;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetramino->brick[i][j]) {
        attron(COLOR_PAIR(tetramino->color));
        mvprintw(tetramino->y + i, (tetramino->x + j) * 2, "[]");
        attroff(COLOR_PAIR(tetramino->color));
      }
    }
  }
}

/**
 * @brief Creates a new panel.
 *
 * This function initializes a panel with the specified properties such as
 * position, header text, content text, size, color, and draw function.
 *
 * @param x The x-coordinate of the panel.
 * @param y The y-coordinate of the panel.
 * @param head_text The header text of the panel.
 * @param text The content text of the panel.
 * @param size The size (number of lines) of the content text.
 * @param color The color of the panel.
 * @param value The initial value to be displayed in the panel.
 * @param mode The mode used to determine what content to display in the panel.
 * @param drawFunc The function used to draw the panel.
 * @return The initialized panel.
 */
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

/**
 * @brief Creates a new game field.
 *
 * This function initializes a game field with the specified width, height, and
 * drawing functions.
 *
 * @param tetris A pointer to the tetris structure.
 * @param width The width of the game field.
 * @param height The height of the game field.
 * @param drawFieldFunc The function used to draw the game field.
 * @param drawTetraminoFunc The function used to draw the current tetramino.
 * @return The initialized game field.
 */
GameField_t createGameField(Tetris_t *tetris, int width, int height,
                            void (*drawFieldFunc)(GameField_t *),
                            void (*drawTetraminoFunc)(GameField_t *)) {
  GameField_t field = {
      .x = 0,
      .y = 0,
      .width = width,
      .height = height,
      .tetris = tetris,
      .drawField = drawFieldFunc,
      .drawTetramino = drawTetraminoFunc,
  };
  return field;
}

/**
 * @brief Constructs a new window with panels and game field.
 *
 * This function creates a new window that includes various panels (score, help,
 * next figure, etc.) and the game field. Each panel is drawn using its
 * corresponding drawing function.
 *
 * @param tetris A pointer to the tetris structure.
 * @return The constructed window.
 */
Window_t _constructorWindow(Tetris_t *tetris) {
  return (Window_t){
      .helpPanel =
          createPanel(15, 16, "Help:",
                      (const char *[]){"Press q to quit", "Press p to pause",
                                       "Press left/right to move figure",
                                       "Press double down to move figure down",
                                       "Press s to start"},
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
