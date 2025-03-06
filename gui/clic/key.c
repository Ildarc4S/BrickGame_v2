#include "./include/key.h"

void _addKeyboardListener(Keyboard_t *kb, int key,
                          void (*listenerFunc)(Button_t btn)) {
  kb->keyboard_listen_list = realloc(
      kb->keyboard_listen_list, sizeof(KeyboardListener_t) * (kb->size + 1));
  kb->size++;
  KeyboardListener_t new_keyboard_listener = {.key = key,
                                              .listenerFunc = listenerFunc};

  kb->keyboard_listen_list[kb->size - 1] = new_keyboard_listener;
}

/**
 * @brief Destroys all keyboard listeners and frees allocated memory.
 *
 * This function frees the memory allocated for the list of keyboard listeners
 * and resets the size of the listener list to 0. It is typically called when
 * the keyboard is no longer needed.
 *
 * @param kb A pointer to the keyboard structure.
 */
void _destroyKeyboardListener(Keyboard_t *kb) {
  if (!kb) return;

  if (kb->keyboard_listen_list) {
    free(kb->keyboard_listen_list);
    kb->keyboard_listen_list = NULL;
    kb->size = 0;
  }
}

/**
 * @brief Destroys the keyboard and all associated listeners.
 *
 * This function calls the destroy function for the keyboard listeners and then
 * frees the memory allocated for the keyboard structure.
 *
 * @param kb A pointer to the keyboard structure.
 */
void _destructorKeyboard(Keyboard_t *kb) {
  kb->destroyKeyboardListener(kb);
  free(kb);
}

/**
 * @brief Calculates the time difference in milliseconds between two time
 * points.
 *
 * This function calculates the time difference between two `struct timeval`
 * instances and returns the result in milliseconds.
 *
 * @param current_time The current time.
 * @param last_time The previous time.
 * @return The time difference in milliseconds.
 */
double calcDeltaTime(struct timeval current_time, struct timeval last_time) {
  return (current_time.tv_sec - last_time.tv_sec) * 1000.0 +
         (current_time.tv_usec - last_time.tv_usec) / 1000.0;
}

/**
 * @brief Checks if a key is being held down.
 *
 * This function checks if the specified key is being held down by comparing
 * the time difference between the last time the key was pressed and the
 * current time. If the key is held down longer than the specified timeout,
 * the function returns `true`.
 *
 * @param key The key to check.
 * @param hold_timeout The maximum time in milliseconds that the key can be
 * held.
 * @return `true` if the key is held, `false` otherwise.
 */
bool isHold(int key, double hold_timeout) {
  static struct timeval last_time = {0};
  struct timeval current_time = {0};
  gettimeofday(&current_time, NULL);

  bool is_hold = false;
  static int prev_key = ERR;

  if (prev_key != key) {
    prev_key = key;
  } else {
    is_hold = calcDeltaTime(current_time, last_time) <= hold_timeout;
  }

  last_time = current_time;
  return is_hold;
}

/**
 * @brief Listens for key press events and triggers the corresponding listener
 * functions.
 *
 * This function listens for key press events, and if a key is pressed, it
 * checks the list of listeners to see if there is a registered listener for
 * that key. If a listener is found, the associated listener function is called.
 *
 * @param this A pointer to the keyboard structure.
 */
void _listen(Keyboard_t *this) {
  int key = getch();

  Button_t button = {.key = key, .hold = isHold(key, 1000)};
  for (int i = 0; i < this->size; i++) {
    if (this->keyboard_listen_list[i].key == button.key) {
      this->keyboard_listen_list[i].listenerFunc(button);
    }
  }
}

/**
 * @brief Constructs a new keyboard structure with the necessary functions.
 *
 * This function creates and initializes a new keyboard structure. It assigns
 * the functions for managing listeners and handling input events to the
 * keyboard structure, and initializes the listener list and size.
 *
 * @return A pointer to the newly created keyboard structure.
 */
Keyboard_t *constructorKeyboard() {
  Keyboard_t *new_keyboard = malloc(sizeof(Keyboard_t));

  new_keyboard->destructor = _destructorKeyboard;
  new_keyboard->addKeyboardListener = _addKeyboardListener;
  new_keyboard->destroyKeyboardListener = _destroyKeyboardListener;
  new_keyboard->listen = _listen;

  new_keyboard->keyboard_listen_list = NULL;
  new_keyboard->size = 0;

  return new_keyboard;
}

/**
 * @brief Initializes the keyboard structure (singleton).
 *
 * This function checks if the keyboard structure has been initialized. If it
 * has not, the function creates and initializes a new keyboard structure. It
 * returns the existing keyboard structure if it has already been created.
 *
 * @return A pointer to the keyboard structure.
 */
Keyboard_t *initKeyboard() {
  static Keyboard_t *keyboard = NULL;
  if (!keyboard) {
    keyboard = constructorKeyboard();
  }
  return keyboard;
}
