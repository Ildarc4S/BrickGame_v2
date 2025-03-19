#include "./data_base.h"

int _readToFile(DataBase_t *self) {
  int high_score = 0;
  FILE *file = fopen(self->file_name, "r");
  if (file) {
    fscanf(file, "high_score: %d", &high_score);
    fclose(file);
  }
  return high_score;
}

void _writeToFile(DataBase_t *self, int high_score) {
  FILE *file = fopen(self->file_name, "w");
  if (file) {
    fprintf(file, "high_score: %d", high_score);
    fclose(file);
  }
}

DataBase_t initDataBase(char *file_name) {
  DataBase_t db = {.read = _readToFile, .write = _writeToFile};
  sprintf(db.file_name, "%s", file_name);
  return db;
}
