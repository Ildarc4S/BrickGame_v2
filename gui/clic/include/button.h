/**
 * @file button.h
 * @brief Header file for defining a Button structure and its attributes.
 *
 * This file contains the definition of the `Button_t` structure that represents
 * a button in the game, which is mapped to a specific key and its state
 * (whether the button is held or not).
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "./frontend.h"

/**
 * @struct _button
 * @brief Represents a button in the game associated with a specific key.
 *
 * This structure is used to represent a button that can be pressed or held
 * during gameplay. Each button corresponds to a specific key and its state
 * (whether it is currently being held or just pressed).
 */
typedef struct _button {
  /**
   * @brief The key associated with the button.
   *
   * This field stores the key code that is mapped to the button.
   */
  int key;

  /**
   * @brief The state of the button (whether it is held).
   *
   * This field indicates if the button is being held down (`true`) or not
   * (`false`).
   */
  bool hold;
} Button_t;

#endif  // BUTTON_H
