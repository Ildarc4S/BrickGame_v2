/**
 * @file init_frontend.h
 * @brief Header file for initializing ncurses and color pairs for the Tetris
 * game frontend.
 *
 * This file contains function prototypes for setting up the ncurses environment
 * and initializing color pairs that are used for rendering the Tetris game
 * interface. It provides the necessary functionality for displaying the game
 * interface, setting up colors for Tetriminos and panels, and handling terminal
 * settings for smooth user interaction.
 *
 * @author Major Sweet
 * @date 2024-05-12
 */

#ifndef INIT_FRONTEND_H
#define INIT_FRONTEND_H

#include <ncurses.h>

#include "../../../brick_game/tetris/include/tetris.h"
#include "./color.h"

/**
 * @brief Initializes the color pairs used in the game.
 *
 * This function initializes the color pairs used to represent different
 * Tetriminos and panels in the Tetris game. Each Tetrimino color is associated
 * with a specific color pair for rendering in the terminal interface. The color
 * pairs are defined using the `init_pair()` function of ncurses.
 */
void initColorPairs();

/**
 * @brief Initializes the ncurses library for the game interface.
 *
 * This function sets up the ncurses environment, including settings like
 * disabling echoing, enabling non-blocking input, configuring special keys
 * (like arrow keys), and preparing the terminal screen for rendering the game
 * interface. It provides a clean and interactive user experience in the
 * terminal.
 */
void initNcurses();

#endif  // INIT_FRONTEND_H
