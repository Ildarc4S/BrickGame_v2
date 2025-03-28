#ifndef FIELD_WIDGET_H
#define FIELD_WIDGET_H

#include "./color_convert.h"
#include <QPainter>
#include <QWidget>
#include "./../../brick_game/spec/game_spec.h"

namespace s21 {

class FieldWidget : public QWidget {
  Q_OBJECT
 public:
  enum class FieldType { MainField, NextFigure };

  explicit FieldWidget(FieldType type, QWidget *parent = nullptr);
  void setGameInfo(GameInfo_t *game_info);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  GameInfo_t *game_info_;
  FieldType field_type_;
  int rows_;
  int cols_;
  QColor border_color_;
  bool use_antialiasing_;

  int **getFieldData();
  void drawField(QPainter &painter);
};

}  // namespace s21

#endif  // FIELD_WIDGET_H
