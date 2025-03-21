#include "./include/data_base.h"
#include <filesystem>
#include <string>
#include <QDebug>

namespace s21 {

DataBase::DataBase(const std::string& file_name) : file_name_(file_name) {
    std::filesystem::path full_path = std::filesystem::absolute(file_name);
    file_name_ = full_path.string();
}

int DataBase::read() {
  std::string line;
  if (!std::filesystem::exists(file_name_)) {
    qDebug() << "File does not exist: " << QString::fromStdString(file_name_);
} else {
    qDebug() << "File found: " << QString::fromStdString(file_name_);
}
  std::ifstream file(file_name_);
  int data = 0;
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
