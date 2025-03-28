#ifndef DESKTOP_WINDOW_H
#define DESKTOP_WINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "./field_widget.h"
#include "./menu.h"

namespace s21 {
class Window : public QWidget {
  Q_OBJECT

 public:
  explicit Window(QWidget *parent = nullptr);
  void setGameInfo(const GameInfo_t &game_info);

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 signals:
  void keyPressed(int key, bool hoold);
  void pauseClicked();
  void restartClicked();
  void exitClicked();

 private:
  void applyStyleSheet();
  void addInfoBlocks();
  void setupConnections();
  void updateInfoPanel();
  void updateLayout();
  void updateSingleInfoPanel(const QString &title, const QString &value);

  QFrame *createInfoBlock(const QString &title, const QString &value);
  QFrame *createHelpBlock();
  QFrame *createNextFigureBlock();

  void drawNextFigure(QPainter &painter);
  void paintNextFigureEvent(QPaintEvent *event);

 private:
  GameInfo_t game_info_;
  QStackedWidget *left_stack_;
  MenuWidget *menu_;
  QLabel *score_label_;
  QLabel *level_label_;
  QLabel *speed_label_;
  QVBoxLayout *right_layout;

  FieldWidget *main_field_;
  FieldWidget *next_figure_widget_;
};
}  // namespace s21

#endif  // DESKTOP_WINDOW_H

