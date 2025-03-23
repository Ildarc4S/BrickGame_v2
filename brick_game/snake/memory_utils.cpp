#include "./include/memory_utils.h"

namespace s21 {

int** MemoryUtility::createField(int width, int height) {
  int** ptr = new int*[height];
  for (int i = 0; i < height; i++) {
    ptr[i] = new int[width];
  }
  return ptr;
}

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
