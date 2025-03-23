#ifndef MEMORY_UTILS
#define MEMORY_UTILS

namespace s21 {

class MemoryUtility {
 public:
  static int** createField(int width, int height);
  static void removeField(int** ptr, int height);
};

}  // namespace s21

#endif  // MEMORY_UTILS

