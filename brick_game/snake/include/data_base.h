#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <fstream>
#include <string>
#include <filesystem>

namespace s21 {

class DataBase {
 private:
  std::string file_name_;

 public:
  explicit DataBase(const std::string& file_name);

  int read();
  void write(int data);
};

}  // namespace s21

#endif  // DATA_BASE_H

