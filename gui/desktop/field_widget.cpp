#include "./include/field_widget.h"

namespace s21 {

FieldWidget::FieldWidget(FieldType type, QWidget *parent)
    : QWidget(parent), game_info_(nullptr), field_type_(type) {
  if (field_type_ == FieldType::MainField) {
    rows_ = FIELD_HEIGHT + FIELD_BORDER;
    cols_ = FIELD_WIDTH + FIELD_BORDER;
    border_color_ = Qt::white;
    use_antialiasing_ = false;
  } else {
    rows_ = TETRAMINO_HEIGHT;
    cols_ = TETRAMINO_WIDTH;
    border_color_ = Qt::black;
    use_antialiasing_ = true;
  }
}

void FieldWidget::setGameInfo(GameInfo_t *game_info) {
  game_info_ = game_info;
  update();
}

void FieldWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  if (!game_info_ || !getFieldData()) {
    return;
  }

  QPainter painter(this);
  if (use_antialiasing_) {
    painter.setRenderHint(QPainter::Antialiasing);
  }
  drawField(painter);
}

int **FieldWidget::getFieldData() {
  return (field_type_ == FieldType::MainField) ? game_info_->field : game_info_->next;
}

void FieldWidget::drawField(QPainter &painter) {
  int cell_size = qMin(width() / cols_, height() / rows_);
  int **field = getFieldData();

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      ObjectCode code = static_cast<ObjectCode>(field[i][j]);
      QColor cell_color = ColorConverter::convertObjectToColor(code);

      painter.fillRect(j * cell_size, i * cell_size, cell_size, cell_size, cell_color);
      painter.setPen(border_color_);
      painter.drawRect(j * cell_size, i * cell_size, cell_size, cell_size);
    }
  }
}

}  // namespace s21
