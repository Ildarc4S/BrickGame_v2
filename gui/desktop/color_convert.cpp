#include "./color_convert.h"
#include <QDebug>

namespace s21 {

QColor ColorConverter::convertObjectToColor(ObjectCode code) {
  QColor color = Qt::white;
  switch (code) {
  case ObjectCode::kAir:
    color = QColor(80, 80, 80);  // gray
    break;
  case ObjectCode::kWall:
    color = Qt::black;
    break;
  case ObjectCode::kTetraminoI:
    color = Qt::red;
    break;
  case ObjectCode::kTetraminoO:
    color = Qt::magenta;
    break;
  case ObjectCode::kTetraminoT:
    color = Qt::blue;
    break;
  case ObjectCode::kTetraminoS:
    color = Qt::green;
    break;
  case ObjectCode::kTetraminoZ:
    color = Qt::darkMagenta;
    break;
  case ObjectCode::kTetraminoJ:
    color = Qt::darkYellow;
    break;
  case ObjectCode::kTetraminoL:
    color = Qt::yellow;
    break;
  case ObjectCode::kSnake:
    color = Qt::green;
    break;
  case ObjectCode::kApple:
    color = Qt::red;
    break;
  default:
    break;
  }
  return color;
}

}   // namespace s21

