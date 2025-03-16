#include "./window.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>

namespace s21 {

GameArea::GameArea(QWidget* parent)
    : QWidget(parent),
      game_info_(nullptr) {}

void GameArea::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  if (!game_info_ || !game_info_->field) { 
    return;
  }

  QPainter painter(this);

  drawField(painter);
}

QColor GameArea::convertObbjectCodeToColor(ObjectCode code) {
  QColor color = Qt::white;
  switch (code) {
    case ObjectCode::OBJECT_CODE_AIR:
      color = Qt::white;
      break;
    case ObjectCode::OBJECT_CODE_WALL:
      color = Qt::black;
      break;
    case ObjectCode::OBJECT_CODE_SNAKE:
      color = Qt::green;
      break;
    case ObjectCode::OBJECT_CODE_APPLE:
      color = Qt::red;
      break;
    default:
      break;
  }
  return color;
}

void GameArea::drawField(QPainter& painter) {
  if (!game_info_ || !game_info_->field) {
  qDebug() << "game_info_ or field is null!";
  return;
}
  int field_rows = FIELD_HEIGHT + 2;
  int field_cols = FIELD_WIDTH + 2;

  int window_width = width() / 2;
  int window_height = height();

  int cell_size = qMin(width() / (FIELD_WIDTH + 2), 
                       height() / (FIELD_HEIGHT + 2));

  for (int i = 0; i < field_rows; i++) {
    for (int j = 0; j < field_cols; j++) {
      painter.fillRect(
          j * cell_size,
          i * cell_size,
          cell_size,
          cell_size,
          convertObbjectCodeToColor(static_cast<ObjectCode>(game_info_->field[i][j])));

      painter.setPen(Qt::black);
      painter.drawRect(
          j * cell_size,
          i * cell_size,
          cell_size,
          cell_size);
    }
  }
}

void GameArea::setGameInfo(const GameInfo_t* game_info) {
  game_info_ = game_info;
}

MenuWidget::MenuWidget(QWidget* parent)
  : QWidget(parent) {
  QVBoxLayout* layout = new QVBoxLayout(this);

  start_continue_btn_ = new QPushButton("Start", this);
  restart_btn_ = new QPushButton("Restart", this);
  exit_btn_ = new QPushButton("Exit", this);

  layout->addStretch();
  layout->addWidget(start_continue_btn_);
  layout->addWidget(restart_btn_);
  layout->addWidget(exit_btn_);
  layout->addStretch();
  layout->addSpacing(20);

  connect(start_continue_btn_, &QPushButton::clicked, this, &MenuWidget::pauseClicked);
  connect(restart_btn_, &QPushButton::clicked, this, &MenuWidget::restartClicked);
  connect(exit_btn_, &QPushButton::clicked, this, &MenuWidget::exitClicked);

  // В конструкторе MenuWidget
status_label_ = new QLabel(this);
status_label_->setAlignment(Qt::AlignCenter);
status_label_->setStyleSheet("font: bold 36px; color: blue;");
layout->addWidget(status_label_);

}

void MenuWidget::updateButtons(int pause_mode) {
  const bool show_restart = (pause_mode == 1 || pause_mode == 4);

  start_continue_btn_->setText((pause_mode == 4 || pause_mode == 8) ? "Start" : "Continue");
  start_continue_btn_->setVisible(true);
  restart_btn_->setVisible(show_restart);
  exit_btn_->setVisible(true);

  if (pause_mode == 1) {
    status_label_->setText("Pause");
  } else if (pause_mode == 3) {
    status_label_->setText("Start");
  } else if (pause_mode == 4) {
    status_label_->setText("Game Over");
  } else {
    status_label_->clear();
  }

  status_label_->setVisible(pause_mode == 1 || pause_mode == 3 || pause_mode == 4);
}

Window::Window(QWidget* parent) : QWidget(parent) {
  QHBoxLayout* main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);

  left_stack_ =  new QStackedWidget;
  game_area_ = new GameArea;
  menu_ = new MenuWidget;
  left_stack_->addWidget(game_area_);
  left_stack_->addWidget(menu_);

  QWidget* right_panel = new QWidget;
  QVBoxLayout* right_layout = new QVBoxLayout(right_panel);
  right_layout->setAlignment(Qt::AlignTop);

  score_label_ = new QLabel("Score: 0");
  level_label_ = new QLabel("Level: 1");
  speed_label_ = new QLabel("Speed: 10");

  QFont font("Arial", 18, QFont::Bold);
  for (auto label : {score_label_, level_label_, speed_label_}) {
    label->setFont(font);
    right_layout->addWidget(label);
  }

  right_layout->addStretch();

  main_layout->addWidget(left_stack_, 2);
  main_layout->addWidget(right_panel, 1);

  connect(menu_, &MenuWidget::pauseClicked, this, &Window::pauseClicked);
  connect(menu_, &MenuWidget::restartClicked, this, &Window::restartClicked);
  connect(menu_, &MenuWidget::exitClicked, this, &Window::exitClicked);
}

void Window::setGameInfo(const GameInfo_t& game_info) {
  game_info_ = game_info;
  game_area_->setGameInfo(&game_info_);
  left_stack_->setCurrentIndex((game_info.pause == 2) ? 0 : 1);

  menu_->updateButtons(game_info_.pause);

  updateInfoPanel();
  update();
}

void Window::updateInfoPanel() {
  score_label_->setText(QString("Score: %1").arg(game_info_.score));
  level_label_->setText(QString("Level: %1").arg(game_info_.level));
  speed_label_->setText(QString("Speed: %1").arg(game_info_.speed));
}

void Window::keyPressEvent(QKeyEvent* event) {
  emit keyPressed(event->key(), event->isAutoRepeat());
}

}  // namespace s21
