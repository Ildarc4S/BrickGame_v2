#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <stdio.h>

#define DB_FILE_NAME_SIZE 256
#define DB_MIN_HIGH_SCORE 0

typedef struct _data_base {
  char file_name[DB_FILE_NAME_SIZE];

  int (*read)(struct _data_base *db);
  void (*write)(struct _data_base *db, int data);
} DataBase_t;

DataBase_t initDataBase(char *file_name);

#endif  // DATA_BASE_H
