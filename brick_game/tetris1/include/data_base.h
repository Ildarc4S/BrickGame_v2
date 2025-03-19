#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <stdio.h>

#define FILE_NAME_SIZE 256

typedef struct _data_base {
  char file_name[FILE_NAME_SIZE];

  int (*read)(struct _data_base *db);
  void (*write)(struct _data_base *db, int data);
} DataBase_t;

DataBase_t initDatabase(char *file_name);

#endif  // DATA_BASE_H
