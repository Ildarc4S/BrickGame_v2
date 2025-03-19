#include "./include/tetris.h"

void cleanField(int **field) {
  for (int i = 0; i < FIELD_HEIGHT + 2; i++) {
    for (int j = 0; j < FIELD_WIDTH + 2; j++) {
      // Set the boundary (first and last row/column) to 1 (walls)
      if (i == 0 || j == 0 || i == FIELD_HEIGHT + 1 || j == FIELD_WIDTH + 1) {
        field[i][j] = OBJECT_CODE_WALL;
      } else {
        field[i][j] = OBJECT_CODE_AIR;
      }
    }
  }
}

int **newField(int width, int height) {
  int error_code = 0;
  int **field = (int **)calloc(height, sizeof(int *));
  if (field == NULL) {
    error_code = 1;
  }

  for (int i = 0; i < height && error_code != 1; i++) {
    field[i] = (int *)calloc(width, sizeof(int));
    if (field[i] == NULL) {
      error_code = 1;
    }
  }

  if (error_code == 1) {
    freeField(field, height);
    field = NULL;
  }

  return field;
}

void freeField(int **field, int height) {
  if (field == NULL) {
    return;
  }

  for (int i = 0; i < height; i++) {
    free(field[i]);
    field[i] = NULL;
  }

  free(field);
}
