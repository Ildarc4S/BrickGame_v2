#include "./include/memory_utils.h"

int **newField(int width, int height) {
  int error_code = MEMORY_UTIL_OK;
  int **field = (int **)calloc(height, sizeof(int *));
  if (field == NULL) {
    error_code = MEMORY_UTIL_ERROR;
  }

  for (int i = 0; i < height && error_code != MEMORY_UTIL_ERROR; i++) {
    field[i] = (int *)calloc(width, sizeof(int));
    if (field[i] == NULL) {
      error_code = MEMORY_UTIL_ERROR;
    }
  }

  if (error_code) {
    freeField(&field, height);
    field = NULL;
  }

  return field;
}

void freeField(int ***field, int height) {
  if (!*field || !field) {
    return;
  }

  for (int i = 0; i < height; i++) {
    free((*field)[i]);
    (*field)[i] = NULL;
  }

  free(*field);
  *field = NULL;
}
