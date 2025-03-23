#include "./color_convert.h"

namespace s21 {

QColor ColorConverter::convertObjectToColor(ObjectCode code) {
  QColor color = Qt::white;
  switch (code) {
  case ObjectCode::kAir:
    color = QColor(80, 80, 80);    // Dark gray
    break;
  case ObjectCode::kWall:
    color = Qt::black;             // Black
    break;
  case ObjectCode::kTetraminoI:
    color = QColor(255, 0, 0);     // Red
    break;
  case ObjectCode::kTetraminoO:
    color = QColor(255, 0, 255);   // Magenta
    break;
  case ObjectCode::kTetraminoT:
    color = QColor(0, 0, 255);     // Blue
    break;
  case ObjectCode::kTetraminoS:
    color = QColor(0, 255, 0);     // Green
    break;
  case ObjectCode::kTetraminoZ:
    color = QColor(128, 0, 128);   // Purple
    break;
  case ObjectCode::kTetraminoJ:
    color = QColor(255, 165, 0);   // Orange
    break;
  case ObjectCode::kTetraminoL:
    color = QColor(255, 255, 0);   // Yellow
    break;
  case ObjectCode::kSnake:
    color = QColor(0, 255, 0);     // Green (same as TetraminoS)
    break;
  case ObjectCode::kApple:
    color = QColor(255, 0, 0);     // Red (same as TetraminoI)
    break;
  default:
    break;
  }
  return color;
}

}   // namespace s21

