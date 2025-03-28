/**
 * @file data_base.h
 * @brief Заголовочный файл класса для работы с базой данных рекордов
 */

#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <fstream>
#include <string>
#include <filesystem>

namespace s21 {

/**
 * @def Начальное значение рекорда по умолчанию
 */
#define INIT_SCORE 0

/**
 * @class DataBase
 * @brief Класс для чтения/записи рекордов в файл
 * 
 * Обеспечивает сохранение и загрузку лучшего счета игры.
 * Формат файла: "high_score:<число>"
 */
class DataBase {
 private:
  std::string file_name_; ///< Имя файла для хранения рекорда

 public:
  /**
   * @brief Конструктор с указанием имени файла
   * @param file_name Путь к файлу для хранения рекордов
   */
  explicit DataBase(const std::string& file_name);

  /**
   * @brief Чтение рекорда из файла
   * @return Текущий рекорд (0 если файл не существует)
   */
  int read();

  /**
   * @brief Запись нового рекорда в файл
   * @param data Значение рекорда для сохранения
   */
  void write(int data);
};

}  // namespace s21

#endif  // DATA_BASE_H
