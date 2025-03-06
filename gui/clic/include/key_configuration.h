/**
 * @file key_config.h
 * @brief Header file for initializing and configuring keyboard listeners.
 *
 * This file defines a function prototype for initializing keyboard listeners
 * by configuring key event listeners for specific actions in the game.
 *
 * @author Major Sweet
 * @date 2024-05-12
 */

#ifndef KEY_CONFIG_H
#define KEY_CONFIG_H

#include "./key.h"

/**
 * @brief Initializes the keyboard configuration by setting up listeners for
 * specific keys.
 *
 * This function is responsible for adding key event listeners to the keyboard
 * structure. It associates specific key presses with their respective listener
 * functions that will be triggered when those keys are pressed during gameplay.
 */
void initKeyboardConfiguration();

#endif  // KEY_CONFIG_H
