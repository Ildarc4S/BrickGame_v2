#include "./include/window.h"

#include "./include/window_defines.h"

namespace s21 {

Window::Window(QWidget *parent) : QWidget(parent), game_info_{} {
  setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  applyStyleSheet();

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(LAYOUT_MARGIN, LAYOUT_MARGIN, LAYOUT_MARGIN,
                                  LAYOUT_MARGIN);

  left_stack_ = new QStackedWidget;
  main_field_ = new FieldWidget(FieldWidget::FieldType::MainField);
  menu_ = new MenuWidget;
  left_stack_->addWidget(main_field_);
  left_stack_->addWidget(menu_);

  QWidget *right_panel = new QWidget;
  right_layout = new QVBoxLayout(right_panel);
  right_layout->setAlignment(Qt::AlignTop);
  right_layout->setSpacing(RIGHT_PANEL_SPACING);
  right_layout->setContentsMargins(
      RIGHT_PANEL_LEFT_MARGIN, RIGHT_PANEL_TOP_MARGIN, RIGHT_PANEL_RIGHT_MARGIN,
      RIGHT_PANEL_BOTTOM_MARGIN);

  addInfoBlocks();

  next_figure_widget_ = nullptr;

  main_layout->addWidget(left_stack_, LEFT_STRETCH_FACTOR);
  main_layout->addWidget(right_panel, RIGHT_STRETCH_FACTOR);

  setupConnections();
}

void Window::applyStyleSheet() {
  setStyleSheet(QString("QWidget { background-color: %1; color: white; }"
                        "QPushButton { background-color: %2; border: %3px "
                        "solid %4; color: white; "
                        "padding: %5px; border-radius: %6px; font-size: %7px; }"
                        "QPushButton:hover { background-color: %8; }"
                        "QPushButton:pressed { background-color: %9; }"
                        "QLabel { color: white; }")
                    .arg(BACKGROUND_COLOR)
                    .arg(BUTTON_NORMAL_COLOR)
                    .arg(BORDER_WIDTH)
                    .arg(BORDER_COLOR)
                    .arg(BUTTON_PADDING)
                    .arg(BORDER_RADIUS)
                    .arg(BUTTON_FONT_SIZE)
                    .arg(BUTTON_HOVER_COLOR)
                    .arg(BUTTON_PRESSED_COLOR));
}
void Window::addInfoBlocks() {
  std::array<std::pair<QString, QString>, PANEL_COUNT> info_data = {
      std::make_pair("Score", QString::number(game_info_.score)),
      std::make_pair("High Score", QString::number(game_info_.score)),
      std::make_pair("Level", QString::number(game_info_.level)),
      std::make_pair("Speed", QString::number(game_info_.speed))};

  for (const auto &entry : info_data) {
    right_layout->addWidget(createInfoBlock(entry.first, entry.second));
  }
}

void Window::setupConnections() {
  connect(menu_, &MenuWidget::pauseClicked, this, &Window::pauseClicked);
  connect(menu_, &MenuWidget::restartClicked, this, &Window::restartClicked);
  connect(menu_, &MenuWidget::exitClicked, this, &Window::exitClicked);
}

QFrame *Window::createInfoBlock(const QString &title, const QString &value) {
  QFrame *frame = new QFrame;
  frame->setStyleSheet(
      QString("QFrame { background: %1; border-radius: %2px; padding: %3px; }")
          .arg(INFO_BLOCK_COLOR)
          .arg(BORDER_RADIUS)
          .arg(FRAME_PADDING));
  frame->setObjectName(title);

  QLabel *title_label = new QLabel(title, frame);
  title_label->setStyleSheet(QString("color: %1; font: bold %2px;")
                                 .arg(TITLE_COLOR)
                                 .arg(TITLE_FONT_SIZE));

  QLabel *value_label = new QLabel(value, frame);
  value_label->setStyleSheet(QString("color: %1; font: bold %2px;")
                                 .arg(VALUE_COLOR)
                                 .arg(VALUE_FONT_SIZE));
  value_label->setObjectName(title + "Value");

  QVBoxLayout *layout = new QVBoxLayout(frame);
  layout->addWidget(title_label);
  layout->addWidget(value_label);

  return frame;
}

QFrame *Window::createHelpBlock() {
  QFrame *frame = new QFrame;
  frame->setStyleSheet(
      QString("QFrame { background: %1; border-radius: %2px; padding: %3px; }")
          .arg(INFO_BLOCK_COLOR)
          .arg(BORDER_RADIUS)
          .arg(SMALL_PADDING));

  QLabel *help_label = nullptr;
  if (game_info_.next == nullptr) {
    help_label = new QLabel(
        "CONTROLS:\n"
        "← → - Move left/right\n"
        "↑ ↓ - Move up/down\n"
        "Space - boost snake\n"
        "S - Start/Continue/Restart\n"
        "P - Pause\n"
        "Q - Quit");
  } else {
    help_label = new QLabel(
        "CONTROLS:\n"
        "← → - Move left/right\n"
        "↓ - Move fast down\n"
        "Space - rotate figure\n"
        "S - Start/Continue/Restart\n"
        "P - Pause\n"
        "Q - Quit");
  }
  help_label->setObjectName("helpFrame");
  help_label->setStyleSheet(QString("color: %1; font: %2px; line-height: %3;")
                                .arg(HELP_TEXT_COLOR)
                                .arg(HELP_FONT_SIZE)
                                .arg(HELP_LINE_HEIGHT));
  QVBoxLayout *layout = new QVBoxLayout(frame);
  layout->addWidget(help_label);

  return frame;
}

QFrame *Window::createNextFigureBlock() {
  QFrame *frame = new QFrame;
  frame->setStyleSheet(
      QString("QFrame { background: %1; border-radius: %2px; padding: %3px; }")
          .arg(INFO_BLOCK_COLOR)
          .arg(BORDER_RADIUS)
          .arg(FRAME_PADDING));

  QLabel *title_label = new QLabel("Next Figure", frame);
  title_label->setStyleSheet(QString("color: %1; font: bold %2px;")
                                 .arg(TITLE_COLOR)
                                 .arg(TITLE_FONT_SIZE));

  next_figure_widget_ =
      new FieldWidget(FieldWidget::FieldType::NextFigure, frame);
  next_figure_widget_->setStyleSheet(
      QString("background: %1;").arg(NEXT_FIGURE_BG_COLOR));
  next_figure_widget_->setFixedSize(NEXT_FIGURE_SIZE, NEXT_FIGURE_SIZE);
  next_figure_widget_->setObjectName("nextFigureWidget");

  QVBoxLayout *layout = new QVBoxLayout(frame);
  layout->addWidget(title_label);
  layout->addWidget(next_figure_widget_);

  return frame;
}

void Window::setGameInfo(const GameInfo_t &game_info) {
  game_info_ = game_info;
  main_field_->setGameInfo(&game_info_);
  left_stack_->setCurrentIndex(
      (game_info.pause == static_cast<int>(PauseMode::kGameContinue))
          ? MAIN_FIELD_STACK_INDEX
          : MENU_STACK_INDEX);

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
        next_figure_widget_ =
            next_figure_block->findChild<FieldWidget *>("nextFigureWidget");
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
