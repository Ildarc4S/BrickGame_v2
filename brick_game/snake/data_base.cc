 /**
 * @file data_base.cc
 * @brief Реализация работы с базой данных рекордов
 */

#include "./include/data_base.h"

namespace s21 {

/**
 * @brief Конструктор базы данных
 * 
 * Сохраняет путь к файлу, но не создает его до первой записи.
 */
DataBase::DataBase(const std::string& file_name) : file_name_(file_name) {}

/**
 * @brief Чтение рекорда из файла
 * @return Прочитанное значение или INIT_SCORE при ошибке
 * 
 * Алгоритм работы:
 * 1. Открывает файл для чтения
 * 2. Ищет строку с префиксом "high_score:"
 * 3. Извлекает числовое значение после двоеточия
 * 4. Возвращает 0 если файл не существует или имеет неверный формат
 */
int DataBase::read() {
  std::string line;
  std::ifstream file(file_name_);
  int data = INIT_SCORE;

  if (file.is_open()) {
    std::getline(file, line);
    if (line.find("high_score:") != std::string::npos) {
      data = std::stoi(line.substr(line.find(":") + 1));
    }
    file.close();
  }

  return data;
}

/**
 * @brief Запись рекорда в файл
 * 
 * Алгоритм работы:
 * 1. Открывает файл для записи (перезаписывает существующий)
 * 2. Сохраняет данные в формате "high_score:<число>"
 * 3. Закрывает файл
 * 
 * @warning Полностью перезаписывает содержимое файла!
 */
void DataBase::write(int data) {
  std::ofstream file(file_name_);  
  if (file.is_open()) {
    file << "high_score:" << data << std::endl; 
    file.close();
  }
}

}  // namespace s21
