#include "./window.h"
#include "./color_convert.h"

#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>

namespace s21 {

GameArea::GameArea(QWidget *parent) : QWidget(parent), game_info_(nullptr) {}

void GameArea::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  if (!game_info_ || !game_info_->field) {
    return;
  }

  QPainter painter(this);
  drawField(painter);
}

void GameArea::drawField(QPainter &painter) {
  if (!game_info_ || !game_info_->field) {
    return;
  }

  int field_rows = FIELD_HEIGHT + 2;
  int field_cols = FIELD_WIDTH + 2;

  int cell_size = qMin(width() / (FIELD_WIDTH + 2), height() / (FIELD_HEIGHT + 2));

  QColor wallColor = Qt::white;

  for (int i = 0; i < field_rows; i++) {
    for (int j = 0; j < field_cols; j++) {
      ObjectCode code = static_cast<ObjectCode>(game_info_->field[i][j]);
      QColor cellColor = ColorConverter::convertObjectToColor(code);

      painter.setPen(wallColor);
      painter.drawRect(j * cell_size, i * cell_size, cell_size, cell_size);

      if (code != ObjectCode::kWall) {
        painter.fillRect(j * cell_size, i * cell_size, cell_size, cell_size,
                         cellColor);
      }
    }
  }
}

void GameArea::setGameInfo(const GameInfo_t *game_info) {
  game_info_ = game_info;
}

}  // namespace s21
