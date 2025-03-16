#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPainter>

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

enum class PauseMode_t {
  PAUSE_MODE_PAUSE = 1,
  PAUSE_MODE_GAME_CONTINUE = 2,
  PAUSE_MODE_START = 3,
  PAUSE_MODE_GAME_OVER = 4,
  PAUSE_MODE_EXIT = 5
};

class GameArea : public QWidget {
  Q_OBJECT

 public:
  explicit GameArea(QWidget* parent = nullptr);
  void setGameInfo(const GameInfo_t* game_info);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  QColor convertObjectCodeToColor(ObjectCode code);
  void drawField(QPainter& painter);

 private:
  const GameInfo_t* game_info_ = nullptr;
};

class MenuWidget: public QWidget {
  Q_OBJECT
 public:
  explicit MenuWidget(QWidget* parent = nullptr);
  void updateButtons(int pause_mode);

 signals:
  void restartClicked();
  void pauseClicked();
  void exitClicked();

 private:
  QPushButton* start_continue_btn_;
  QPushButton* exit_btn_;
  QLabel* status_label_;
};

class NextFigureWidget : public QWidget {
public:
    explicit NextFigureWidget(QWidget* parent = nullptr) : QWidget(parent) {}

    void setGameInfo(const GameInfo_t* game_info) {
        game_info_ = game_info;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        if (!game_info_ || !game_info_->next) return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        const int cell_size = qMin(width() / 4, height() / 4);
        const QColor blockColor = Qt::cyan;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (game_info_->next[i][j]) {
                    painter.fillRect(
                        j * cell_size, 
                        i * cell_size, 
                        cell_size, 
                        cell_size, 
                        blockColor
                    );
                    painter.setPen(Qt::black);
                    painter.drawRect(
                        j * cell_size, 
                        i * cell_size, 
                        cell_size, 
                        cell_size
                    );
                }
            }
        }
    }

private:
    const GameInfo_t* game_info_ = nullptr;
};


class Window : public QWidget {
  Q_OBJECT

 public:
  explicit Window(QWidget* parent = nullptr);
  void setGameInfo(const GameInfo_t& game_info);

 protected:
  void keyPressEvent(QKeyEvent* event) override;
  // void resizeEvent(QResizeEvent* event) override;

 signals:
  void keyPressed(int key, bool hoold);
  void pauseClicked();
  void restartClicked();
  void exitClicked();

 private:
  void updateInfoPanel();
  void updateLayout();
  void updateSingleInfoPanel(const QString& title, const QString& value);
  QFrame* createInfoBlock(const QString& title, const QString& value);
  QFrame* createHelpBlock();
  QFrame* createNextFigureBlock();
  void drawNextFigure(QPainter& painter);
  void paintNextFigureEvent(QPaintEvent* event);

 private:
    GameInfo_t game_info_;
    QStackedWidget* left_stack_;
    GameArea* game_area_;
    MenuWidget* menu_;
    QLabel* score_label_;
    QLabel* level_label_;
    QLabel* speed_label_;
    QVBoxLayout* right_layout;
    NextFigureWidget* next_figure_widget_;
};
}  // namespace s21

