#ifndef DESKTOP_COLOR_CONVERT_H
#define DESKTOP_COLOR_CONVERT_H

#include "./objects_code.h"
#include <QColor>

namespace s21 {

class ColorConverter {
 public:
  static QColor convertObjectToColor(ObjectCode code);
};

}   // namespace s21

#endif  // DESKTOP_COLOR_CONVERT_H

