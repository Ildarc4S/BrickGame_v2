#ifndef DESKTOP_MENU_H
#define DESKTOP_MENU_H

#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "./../../../brick_game/spec/game_spec.h"

namespace s21 {

#define BOTTOM_SPACING 20
#define STATUS_MARGIN_BOTTOM 30
#define STATUS_FONT_SIZE 32
#define STATUS_FONT_COLOR "#FFFFFF"

class MenuWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MenuWidget(QWidget *parent = nullptr);
  void updateButtons(int pause_mode);

 signals:
  void restartClicked();
  void pauseClicked();
  void exitClicked();

 private:
  QPushButton *start_continue_btn_;
  QPushButton *exit_btn_;
  QLabel *status_label_;
};
}  // namespace s21

#endif  // DESKTOP_MENU_H

