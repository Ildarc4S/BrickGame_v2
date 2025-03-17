/**
 * @file field_operations.c
 * @brief Functions for managing the game field in Tetris, including field
 * creation, cleanup, and resetting.
 *
 * This file contains the logic for managing the Tetris game field. It includes
 * functions for creating a new field, resetting the field, and freeing memory
 * when no longer needed.
 *
 * @author Major Sweet
 * @date 2025-02-12
 */

#include "./include/tetris.h"

/**
 * @brief Resets the game field to its initial state.
 *
 * This function clears the field, setting the outer boundary to 1 (representing
 * walls) and all other cells inside to 0 (empty space). It is called when
 * initializing or resetting the game field.
 *
 * @param field A pointer to the field (2D array) to be cleared.
 */
void cleanField(int **field) {
  for (int i = 0; i < FIELD_HEIGHT + 2; i++) {
    for (int j = 0; j < FIELD_WIDTH + 2; j++) {
      // Set the boundary (first and last row/column) to 1 (walls)
      if (i == 0 || j == 0 || i == FIELD_HEIGHT + 1 || j == FIELD_WIDTH + 1) {
        field[i][j] = 1;
      } else {
        // Set all other cells to 0 (empty space)
        field[i][j] = 0;
      }
    }
  }
}

/**
 * @brief Allocates memory for a new game field.
 *
 * This function creates a 2D array to represent the game field. It allocates
 * memory dynamically and adds an extra border around the field to represent the
 * walls. If memory allocation fails, it frees any previously allocated memory
 * and returns NULL.
 *
 * @param width The width of the field (excluding the borders).
 * @param height The height of the field (excluding the borders).
 * @return A pointer to the newly allocated field, or NULL if memory allocation
 * failed.
 */
int **newField(int width, int height) {
  int error_code = 0;
  // Allocate memory for the field, including extra space for the boundary
  // rows/columns.
  int **field = (int **)calloc(height, sizeof(int *));
  if (field == NULL) {
    error_code = 1;
  }

  // Allocate memory for each row in the field.
  for (int i = 0; i < height && error_code != 1; i++) {
    field[i] = (int *)calloc(width, sizeof(int));
    if (field[i] == NULL) {
      error_code = 1;
    }
  }

  // If memory allocation failed, free the previously allocated memory.
  if (error_code == 1) {
    freeField(field, height);
    field = NULL;
  }

  return field;
}

/**
 * @brief Frees the memory allocated for the game field.
 *
 * This function frees the dynamically allocated memory for the 2D field array.
 * It first frees each row and then frees the main array holding the rows.
 *
 * @param field A pointer to the field (2D array) to be freed.
 * @param height The height of the field (used to loop through rows).
 */
void freeField(int **field, int height) {
  if (field == NULL) {
    return;  // If the field is already NULL, do nothing.
  }

  // Free each row of the field.
  for (int i = 0; i < height; i++) {
    free(field[i]);
    field[i] = NULL;
  }

  // Finally, free the main array.
  free(field);
}
