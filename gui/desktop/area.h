#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "./../../brick_game/spec/game_spec.h"
#include "./color_convert.h"
#include "./field.h"

namespace s21 {

class GameArea : public QWidget {
  Q_OBJECT

 public:
  explicit GameArea(QWidget *parent = nullptr);
  void setGameInfo(const GameInfo_t *game_info);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  QColor convertObjectCodeToColor(ObjectCode code);
  void drawField(QPainter &painter);

 private:
  const GameInfo_t *game_info_ = nullptr;
};

} // namespace s21
