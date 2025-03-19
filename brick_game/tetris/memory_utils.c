#include "./include/memory_utils.h"

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
