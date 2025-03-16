#ifndef COLOR_CONVERT_H
#define COLOR_CONVERT_H

#include "./objects_code.h"
#include <QColor>

namespace s21 {

class ColorConverter {
 public:
  static QColor convertObjectToColor(ObjectCode code);
};

}   // namespace s21

#endif  // COLOR_CONVERT_H

