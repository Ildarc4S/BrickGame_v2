/**
 * @file memory_utils.h
 * @brief Заголовочный файл класса для работы с динамической памятью
 */

#ifndef SNAKE_MEMORY_UTILS
#define SNAKE_MEMORY_UTILS

namespace s21 {

/**
 * @class MemoryUtility
 * @brief Класс-утилита для работы с динамической памятью
 * 
 * Содержит статические методы для создания и освобождения двумерных массивов
 */
class MemoryUtility {
 public:
  /**
   * @brief Создает двумерный массив заданного размера
   * @param width Ширина массива (количество столбцов)
   * @param height Высота массива (количество строк)
   * @return Указатель на созданный двумерный массив
   */
  static int** createField(int width, int height);

  /**
   * @brief Освобождает память, занятую двумерным массивом
   * @param ptr Указатель на двумерный массив
   * @param height Высота массива (количество строк)
   */
  static void removeField(int** ptr, int height);
};

}  // namespace s21

#endif  // SNAKE_MEMORY_UTILS

