#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "./window.h"

namespace s21 {


MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);

  QWidget *status_container = new QWidget(this);
  QVBoxLayout *status_layout = new QVBoxLayout(status_container);

  status_label_ = new QLabel(this);
  status_label_->setAlignment(Qt::AlignCenter);
  status_label_->setStyleSheet("QLabel {"
                               "   color: #FFFFFF;"
                               "   font: bold 32px;"
                               "   margin-bottom: 30px;"
                               "}");
  status_layout->addWidget(status_label_);

  layout->addWidget(status_container);

  start_continue_btn_ = new QPushButton("Start", this);
  exit_btn_ = new QPushButton("Exit", this);

  layout->addStretch();
  layout->addWidget(start_continue_btn_);
  layout->addWidget(exit_btn_);
  layout->addStretch();
  layout->addSpacing(20);

  connect(start_continue_btn_, &QPushButton::clicked, this,
          &MenuWidget::pauseClicked);
  connect(exit_btn_, &QPushButton::clicked, this, &MenuWidget::exitClicked);
}

void MenuWidget::updateButtons(int pause_mode) {
  PauseMode named_pause_mode = static_cast<PauseMode>(pause_mode);

  if (named_pause_mode == PauseMode::kPause) {
    start_continue_btn_->setText("Continue");
  } else if (named_pause_mode == PauseMode::kStart ||
             named_pause_mode == PauseMode::kWin) {
    start_continue_btn_->setText("Start");
    exit_btn_->setVisible(true);
  } else if (named_pause_mode == PauseMode::kGameOver) {
    start_continue_btn_->setText("Restart");
  }

  if (named_pause_mode == PauseMode::kPause) {
    status_label_->setText("Pause");
  } else if (named_pause_mode == PauseMode::kStart) {
    status_label_->setText("Start");
  } else if (named_pause_mode == PauseMode::kGameOver) {
    status_label_->setText("Game Over");
  } else if (named_pause_mode == PauseMode::kWin) {
    status_label_->setText("You win!");
  } else {
    status_label_->clear();
  }
}

}  // namespace s21
