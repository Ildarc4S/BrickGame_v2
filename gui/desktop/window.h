#pragma once

#include <QMainWindow>
#include "./../../brick_game/spec/game_spec.h"

namespace s21 {

enum class ObjectCode {
  OBJECT_CODE_AIR = -2,
  OBJECT_CODE_WALL = -1,
  OBJECT_CODE_TETRAMINO_I = 1,
  OBJECT_CODE_TETRAMINO_O = 2,
  OBJECT_CODE_TETRAMINO_T = 3,
  OBJECT_CODE_TETRAMINO_S = 4,
  OBJECT_CODE_TETRAMINO_Z = 5,
  OBJECT_CODE_TETRAMINO_J = 6,
  OBJECT_CODE_TETRAMINO_L = 7,

  OBJECT_CODE_SNAKE = 10,
  OBJECT_CODE_APPLE = 11
};

class Window : public QMainWindow {
  Q_OBJECT
 public:
  explicit Window(QWidget* parent = nullptr);
  void setGameInfo(GameInfo_t& game_info);

 protected:
  void keyPressEvent(QKeyEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

 signals:
  void keyPressed(int key, bool hoold);

 private:
  void render(QPainter& painter);
  QColor convertObbjectCodeToColor(ObjectCode code);

 private:
  GameInfo_t game_info_;
};

}  // namespace s21

