/**
 * @file key_configuration.c
 * @brief Functions for configuring keyboard input and handling key press events
 * in the Tetris game.
 *
 * This file contains functions that configure the keyboard controls, bind key
 * press events, and handle user inputs during the game. It associates key
 * events with the appropriate game actions.
 *
 * @author Major Sweet
 * @date 2024-05-12
 */

#include "./include/key_configuration.h"

/**
 * @brief Handles the UP key press event.
 *
 * This function is called when the UP key is pressed. It calls the `userInput`
 * function to handle the corresponding action with the `Up` direction.
 *
 * @param btn The button structure containing the key press information.
 */
void upKeyPressed(Button_t btn) { userInput(Up, btn.hold); }

/**
 * @brief Handles the LEFT key press event.
 *
 * This function is called when the LEFT key is pressed. It calls the
 * `userInput` function to handle the corresponding action with the `Left`
 * direction.
 *
 * @param btn The button structure containing the key press information.
 */
void leftKeyPressed(Button_t btn) { userInput(Left, btn.hold); }

/**
 * @brief Handles the RIGHT key press event.
 *
 * This function is called when the RIGHT key is pressed. It calls the
 * `userInput` function to handle the corresponding action with the `Right`
 * direction.
 *
 * @param btn The button structure containing the key press information.
 */
void rightKeyPressed(Button_t btn) { userInput(Right, btn.hold); }

/**
 * @brief Handles the DOWN key press event.
 *
 * This function is called when the DOWN key is pressed. It calls the
 * `userInput` function to handle the corresponding action with the `Down`
 * direction.
 *
 * @param btn The button structure containing the key press information.
 */
void downKeyPressed(Button_t btn) { userInput(Down, btn.hold); }

/**
 * @brief Handles the SPACE key press event.
 *
 * This function is called when the SPACE key is pressed. It calls the
 * `userInput` function to perform the corresponding action, which may be
 * related to rotating or activating the Tetrimino.
 *
 * @param btn The button structure containing the key press information.
 */
void spaceKeyPressed(Button_t btn) { userInput(Action, btn.hold); }

/**
 * @brief Handles the S key press event to start a new game.
 *
 * This function is called when the 's' key is pressed. It calls the `userInput`
 * function to initiate the start of a new game.
 *
 * @param btn The button structure containing the key press information.
 */
void startKeyPressed(Button_t btn) { userInput(Start, btn.hold); }

/**
 * @brief Handles the P key press event to pause the game.
 *
 * This function is called when the 'p' key is pressed. It calls the `userInput`
 * function to pause the game.
 *
 * @param btn The button structure containing the key press information.
 */
void pauseKeyPressed(Button_t btn) { userInput(Pause, btn.hold); }

/**
 * @brief Handles the Q key press event to exit the game.
 *
 * This function is called when the 'q' key is pressed. It calls the `userInput`
 * function to terminate the game.
 *
 * @param btn The button structure containing the key press information.
 */
void exitKeyPressed(Button_t btn) { userInput(Terminate, btn.hold); }

/**
 * @brief Initializes the keyboard configuration for the game.
 *
 * This function sets up the keyboard listener for various key events and
 * associates each key with a corresponding function to handle specific game
 * actions. The keys are configured for movement, rotation, starting, pausing,
 * and exiting the game.
 *
 * - UP key: Moves the Tetrimino upwards.
 * - DOWN key: Moves the Tetrimino downwards.
 * - LEFT key: Moves the Tetrimino left.
 * - RIGHT key: Moves the Tetrimino right.
 * - SPACE key: Activates the action (e.g., rotate or drop).
 * - 's' key: Starts a new game.
 * - 'p' key: Pauses the game.
 * - 'q' key: Exits the game.
 *
 * This function also initializes the keyboard listener for the game and binds
 * the key press events to the appropriate handlers.
 */
void initKeyboardConfiguration() {
  Keyboard_t *keyboard = initKeyboard();

  // Add listeners for each key press event
  keyboard->addKeyboardListener(keyboard, KEY_UP, upKeyPressed);
  keyboard->addKeyboardListener(keyboard, KEY_DOWN, downKeyPressed);
  keyboard->addKeyboardListener(keyboard, KEY_LEFT, leftKeyPressed);
  keyboard->addKeyboardListener(keyboard, KEY_RIGHT, rightKeyPressed);
  keyboard->addKeyboardListener(keyboard, ' ', spaceKeyPressed);
  keyboard->addKeyboardListener(keyboard, 's', startKeyPressed);
  keyboard->addKeyboardListener(keyboard, 'p', pauseKeyPressed);
  keyboard->addKeyboardListener(keyboard, 'q', exitKeyPressed);
}
