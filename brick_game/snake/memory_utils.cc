/**
 * @file memory_utils.cc
 * @brief Реализация методов работы с динамической памятью
 */

#include "./include/memory_utils.h"

namespace s21 {

/**
 * @brief Создает двумерный массив целых чисел
 * @return Указатель на созданный двумерный массив
 *
 * Выделяет память под двумерный массив размером height x width.
 * В случае ошибки выделения памяти может сгенерировать исключение
 * std::bad_alloc.
 */
int** MemoryUtility::createField(int width, int height) {
  int** ptr = new int*[height];
  for (int i = 0; i < height; i++) {
    ptr[i] = new int[width];
  }
  return ptr;
}

/**
 * @brief Освобождает память, занятую двумерным массивом
 *
 * Безопасно удаляет двумерный массив, проверяя указатель на nullptr.
 * Последовательно удаляет все строки массива, затем массив указателей.
 */
void MemoryUtility::removeField(int** ptr, int height) {
  if (ptr == nullptr) return;

  for (int i = 0; i < height; i++) {
    delete[] ptr[i];
    ptr[i] = nullptr;
  }
  delete[] ptr;
  ptr = nullptr;
}

}  // namespace s21
