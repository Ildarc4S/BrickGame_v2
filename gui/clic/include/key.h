/**
 * @file key.h
 * @brief Header file for handling keyboard input and event listening.
 *
 * This file defines structures and function prototypes related to keyboard
 * input handling. It includes functionality for listening to key presses and
 * invoking the associated listener functions for specific keys.
 *
 * @author Major Sweet
 * @date 2024-05-12
 */

#ifndef KEY_H
#define KEY_H

#include "./button.h"

/**
 * @struct KeyboardListener_t
 * @brief Structure representing a listener for a specific key press event.
 *
 * This structure holds information about a key press and the associated
 * listener function that should be called when that key is pressed.
 */
typedef struct _keyboard_listener {
  int key;                        /**< The key code to listen for */
  void (*listenerFunc)(Button_t); /**< Pointer to the function to be called when
                                     the key is pressed */
} KeyboardListener_t;

/**
 * @struct Keyboard_t
 * @brief Structure for managing keyboard input and listeners.
 *
 * This structure manages a list of keyboard listeners, each of which associates
 * a key press with a specific listener function. It provides functions for
 * adding listeners, listening for key events, and destroying the listeners when
 * no longer needed.
 */
typedef struct _keyboard {
  KeyboardListener_t *keyboard_listen_list; /**< List of keyboard listeners */
  int size; /**< Number of keyboard listeners in the list */

  /**
   * @brief Starts listening for key events.
   *
   * This function listens for key presses and triggers the appropriate
   * listener function for any key that has been registered in the listener
   * list.
   *
   * @param _this Pointer to the current keyboard structure.
   */
  void (*listen)(struct _keyboard *);

  /**
   * @brief Adds a new key listener.
   *
   * This function registers a listener for a specific key. When that key is
   * pressed, the associated listener function will be called.
   *
   * @param _this Pointer to the current keyboard structure.
   * @param key The key code to listen for.
   * @param listenerFunc Pointer to the function to call when the key is
   * pressed.
   */
  void (*addKeyboardListener)(struct _keyboard *, int,
                              void (*listenerFunc)(Button_t));

  /**
   * @brief Destroys the list of keyboard listeners.
   *
   * This function removes all keyboard listeners, freeing any allocated memory.
   *
   * @param _this Pointer to the current keyboard structure.
   */
  void (*destroyKeyboardListener)(struct _keyboard *);

  /**
   * @brief Destructor for the keyboard structure.
   *
   * This function cleans up the keyboard structure, freeing any memory
   * allocated during the creation of the structure.
   *
   * @param _this Pointer to the current keyboard structure.
   */
  void (*destructor)(struct _keyboard *);
} Keyboard_t;

/**
 * @brief Initializes a new keyboard structure.
 *
 * This function allocates memory for a new keyboard structure, initializes its
 * fields, and returns a pointer to the newly created structure.
 *
 * @return A pointer to the newly created and initialized keyboard structure.
 */
Keyboard_t *initKeyboard();

#endif  // KEY_H
