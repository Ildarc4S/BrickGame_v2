#include "./window.h"
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>

namespace s21 {

Window::Window(QWidget *parent) : QWidget(parent), game_info_{} {
  setFixedSize(600, 900);
  setStyleSheet("QWidget { background-color: #2E2E2E; color: white; }"
                "QPushButton { background-color: #444444; border: 1px solid #666666; color: white; padding: 15px; border-radius: 5px; font-size: 18px; }"
                "QPushButton:hover { background-color: #555555; }"
                "QPushButton:pressed { background-color: #333333; }"
                "QLabel { color: white; }");

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);

  left_stack_ = new QStackedWidget;
  main_field_ = new FieldWidget(FieldWidget::FieldType::MainField);
  menu_ = new MenuWidget;
  left_stack_->addWidget(main_field_);
  left_stack_->addWidget(menu_);

  QWidget *right_panel = new QWidget;
  right_layout = new QVBoxLayout(right_panel);
  right_layout->setAlignment(Qt::AlignTop);
  right_layout->setSpacing(25);
  right_layout->setContentsMargins(1, 10, 10, 1);

  std::array<std::pair<QString, QString>, 4> info_data = {
      std::make_pair("Score", QString::number(game_info_.score)),
      std::make_pair("High Score", QString::number(game_info_.score)),
      std::make_pair("Level", QString::number(game_info_.level)),
      std::make_pair("Speed", QString::number(game_info_.speed))};

  for (const auto &entry : info_data) {
    right_layout->addWidget(createInfoBlock(entry.first, entry.second));
  }

  next_figure_widget_ = nullptr;

  main_layout->addWidget(left_stack_, 2);
  main_layout->addWidget(right_panel, 1);

  connect(menu_, &MenuWidget::pauseClicked, this, &Window::pauseClicked);
  connect(menu_, &MenuWidget::restartClicked, this, &Window::restartClicked);
  connect(menu_, &MenuWidget::exitClicked, this, &Window::exitClicked);
}

QFrame *Window::createInfoBlock(const QString &title, const QString &value) {
  QFrame *frame = new QFrame;
  frame->setStyleSheet("QFrame { background: #252525; border-radius: 12px; padding: 1px; }");
  frame->setObjectName(title);

  QLabel *title_label = new QLabel(title, frame);
  title_label->setStyleSheet("color: #888888; font: bold 16px;");

  QLabel *value_label = new QLabel(value, frame);
  value_label->setStyleSheet("color: #FFFFFF; font: bold 28px;");
  value_label->setObjectName(title + "Value");

  QVBoxLayout *layout = new QVBoxLayout(frame);
  layout->addWidget(title_label);
  layout->addWidget(value_label);

  return frame;
}

QFrame *Window::createHelpBlock() {
  QFrame *frame = new QFrame;
  frame->setStyleSheet("QFrame { background: #252525; border-radius: 12px; padding: 2px; }");

  QLabel *help_label = nullptr;
  if (game_info_.next == nullptr) {
    help_label = new QLabel("CONTROLS:\n← → - Move left/right\n↑ ↓ - Move up/down\nS - Start/Continue\nP - Pause\nQ - Quit");
  } else {
    help_label = new QLabel("CONTROLS:\n← → - Move left/right\n↓ - Move down\nDouble ↓ - Move fast down\nS - Start/Continue\nP - Pause\nQ - Quit");
  }
  help_label->setObjectName("helpFrame");
  help_label->setStyleSheet("color: #CCCCCC; font: 16px; line-height: 1.5;");
  QVBoxLayout *layout = new QVBoxLayout(frame);
  layout->addWidget(help_label);

  return frame;
}

QFrame *Window::createNextFigureBlock() {
  QFrame *frame = new QFrame;
  frame->setStyleSheet("QFrame { background: #252525; border-radius: 12px; padding: 5px; }");

  QLabel *title_label = new QLabel("Next Figure", frame);
  title_label->setStyleSheet("color: #888888; font: bold 16px;");

  next_figure_widget_ = new FieldWidget(FieldWidget::FieldType::NextFigure, frame);
  next_figure_widget_->setStyleSheet("background: #222222;");
  next_figure_widget_->setFixedSize(120, 120);
  next_figure_widget_->setObjectName("nextFigureWidget");

  QVBoxLayout *layout = new QVBoxLayout(frame);
  layout->addWidget(title_label);
  layout->addWidget(next_figure_widget_);

  return frame;
}

void Window::setGameInfo(const GameInfo_t &game_info) {
  game_info_ = game_info;
  main_field_->setGameInfo(&game_info_);
  left_stack_->setCurrentIndex((game_info.pause == 2) ? 0 : 1);

  menu_->updateButtons(game_info_.pause);

  updateInfoPanel();
  QFrame *help_label = findChild<QFrame *>("helpFrame");
  if (!help_label) {
    help_label = createHelpBlock();
    right_layout->addWidget(help_label);
  }

  if (game_info_.next != nullptr) {
    if (!next_figure_widget_) {
      next_figure_widget_ = findChild<FieldWidget *>("nextFigureWidget");
      if (!next_figure_widget_) {
        QFrame *next_figure_block = createNextFigureBlock();
        next_figure_widget_ = next_figure_block->findChild<FieldWidget *>("nextFigureWidget");
        right_layout->addWidget(next_figure_block);
      }
    }
    if (next_figure_widget_) {
      next_figure_widget_->setGameInfo(&game_info_);
    }
  }

  update();
}

void Window::updateInfoPanel() {
  updateSingleInfoPanel("Score", QString::number(game_info_.score));
  updateSingleInfoPanel("High Score", QString::number(game_info_.high_score));
  updateSingleInfoPanel("Level", QString::number(game_info_.level));
  updateSingleInfoPanel("Speed", QString::number(game_info_.speed));
}

void Window::updateSingleInfoPanel(const QString &title, const QString &value) {
  QString labelName = title + "Value";
  QFrame *frame = findChild<QFrame *>(title);
  if (frame) {
    QLabel *label = frame->findChild<QLabel *>(labelName);
    if (label) {
      label->setText(value);
    }
  }
}

void Window::keyPressEvent(QKeyEvent *event) {
  emit keyPressed(event->key(), event->isAutoRepeat());
}

}  // namespace s21
