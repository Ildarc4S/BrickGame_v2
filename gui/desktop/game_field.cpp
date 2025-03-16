#include "./game_field.h"

namespace s21 {

NextFigureWidget::NextFigureWidget(QWidget *parent) : QWidget(parent) {}

void NextFigureWidget::setGameInfo(const GameInfo_t *game_info) {
  game_info_ = game_info;
  update();
}

void NextFigureWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  if (!game_info_ || !game_info_->next) {
    return;
  }

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  const int cell_size = qMin(width() / 4, height() / 4);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
        ObjectCode object_code = static_cast<ObjectCode>(game_info_->next[i][j]);
        painter.fillRect(
          j * cell_size,
          i * cell_size,
          cell_size, cell_size,
          ColorConverter::convertObjectToColor(object_code));

        painter.setPen(Qt::black);
        painter.drawRect(j * cell_size, i * cell_size, cell_size, cell_size);
    }
  }
}
}  // namespace s21
