#include "./include/data_base.h"

namespace s21 {

DataBase::DataBase(const std::string& file_name) : file_name_(file_name) {}
  
int DataBase::read() {
  std::string line;
  std::ifstream file(file_name_);
  int data = -1;
  if (file.is_open()) {
    std::getline(file, line);
    if (line.find("high_score:") != std::string::npos) {
      data = std::stoi(line.substr(line.find(":") + 1));
    }
    file.close();
  }
  
  return data;
}

void DataBase::write(int data) {
  std::ofstream file(file_name_);  
  if (file.is_open()) {
    file << "high_score:" << data << std::endl; 
    file.close();
  }
}

}  // namespace s21
