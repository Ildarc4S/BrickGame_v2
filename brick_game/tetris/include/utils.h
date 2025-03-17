/**
 * @file utils.h
 * @brief Header file for utility functions used in the Tetris game.
 *
 * This file contains utility functions for creating, cleaning, and freeing
 * the game field, as well as other helper functions related to managing memory.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

/**
 * @brief Creates a new 2D array representing the game field.
 *
 * This function dynamically allocates memory for a 2D array (game field)
 * with the specified width and height. The array is initialized with zeros.
 *
 * @param width The width of the game field (number of columns).
 * @param height The height of the game field (number of rows).
 * @return A pointer to the newly created 2D array (game field).
 */
int **newField(int width, int height);

/**
 * @brief Frees the memory allocated for the game field.
 *
 * This function deallocates the memory used by the 2D array representing the
 * game field. The field should be freed row by row before freeing the array
 * itself.
 *
 * @param field A pointer to the 2D array (game field) to be freed.
 * @param height The height of the game field (number of rows).
 */
void freeField(int **field, int height);

/**
 * @brief Cleans (resets) the game field by setting all elements to zero.
 *
 * This function iterates through the entire game field and sets each element to
 * zero. This is typically used to reset the field to an empty state.
 *
 * @param field A pointer to the 2D array (game field) to be cleaned.
 */
void cleanField(int **field);

#endif /* UTILS_H */
