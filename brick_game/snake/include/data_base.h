#pragma once

#include <fstream>
#include <string>

namespace s21 {

class DataBase {
 private:
   std::string file_name_;
 public:
  DataBase(const std::string& file_name);
  
  int read();
  void write(int data);
};

}  // namespace s21
