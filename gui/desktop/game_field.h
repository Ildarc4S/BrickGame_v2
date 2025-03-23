#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "./../../brick_game/spec/game_spec.h"
#include "./color_convert.h"

namespace s21 {

class NextFigureWidget : public QWidget {
Q_OBJECT
 public:
  explicit NextFigureWidget(QWidget *parent = nullptr);
  void setGameInfo(const GameInfo_t *game_info);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  const GameInfo_t *game_info_ = nullptr;
};

}  // namespace s21
