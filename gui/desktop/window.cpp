#include "./window.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <array>
#include <utility>

namespace s21 {

GameArea::GameArea(QWidget *parent) : QWidget(parent), game_info_(nullptr) {}

void GameArea::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  if (!game_info_ || !game_info_->field) {
    return;
  }

  QPainter painter(this);
  drawField(painter);
}

QColor GameArea::convertObjectCodeToColor(ObjectCode code) {
  QColor color = Qt::white;
  switch (code) {
  case ObjectCode::kAir:
    color = QColor(80, 80, 80);  // gray
    break;
  case ObjectCode::kWall:
    color = Qt::black;
    break;
  case ObjectCode::kSnake:
    color = Qt::green;
    break;
  case ObjectCode::kApple:
    color = Qt::red;
    break;
  default:
    break;
  }
  return color;
}

void GameArea::drawField(QPainter &painter) {
  if (!game_info_ || !game_info_->field) {
    return;
  }

  int field_rows = FIELD_HEIGHT + 2;
  int field_cols = FIELD_WIDTH + 2;

  int cell_size =
      qMin(width() / (FIELD_WIDTH + 2), height() / (FIELD_HEIGHT + 2));

  QColor wallColor = Qt::white;

  for (int i = 0; i < field_rows; i++) {
    for (int j = 0; j < field_cols; j++) {
      ObjectCode code = static_cast<ObjectCode>(game_info_->field[i][j]);
      QColor cellColor = convertObjectCodeToColor(code);

      painter.setPen(wallColor);
      painter.drawRect(j * cell_size, i * cell_size, cell_size, cell_size);

      if (code != ObjectCode::kWall) {
        painter.fillRect(j * cell_size, i * cell_size, cell_size, cell_size,
                         cellColor);
      }
    }
  }
}

void GameArea::setGameInfo(const GameInfo_t *game_info) {
  game_info_ = game_info;
}

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

Window::Window(QWidget *parent) : QWidget(parent) {
  setStyleSheet("QWidget {"
                "    background-color: #2E2E2E;" // Темный фон для всего окна
                "    color: white;"              // Белый текст
                "}"
                "QPushButton {"
                "    background-color: #444444;" // Темный фон для кнопок
                "    border: 1px solid #666666;" // Светлая граница
                "    color: white;"              // Белый текст на кнопках
                "    padding: 15px;"             // Увеличиваем высоту кнопок
                "    border-radius: 5px;"        // Округленные углы
                "    font-size: 18px;"           // Увеличиваем размер шрифта
                "}"
                "QPushButton:hover {"
                "    background-color: #555555;" // Фон кнопки при наведении
                "}"
                "QPushButton:pressed {"
                "    background-color: #333333;" // Фон кнопки при нажатии
                "}"
                "QLabel {"
                "    color: white;" // Белый текст для меток
                "}");

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);

  left_stack_ = new QStackedWidget;
  game_area_ = new GameArea;
  menu_ = new MenuWidget;
  left_stack_->addWidget(game_area_);
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
  frame->setStyleSheet("QFrame {"
                       "   background: #252525;"
                       "   border-radius: 12px;"
                       "   padding: 1px;"
                       "}");

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
  frame->setStyleSheet("QFrame {"
                       "   background: #252525;"
                       "   border-radius: 12px;"
                       "   padding: 2px;"
                       "}");

  QLabel *help_label = nullptr;

  if (game_info_.next == nullptr) {
    help_label = new QLabel("CONTROLS:\n"
                            "← → - Move left/right\n"
                            "↑ ↓ - Move up/down\n"
                            "S - Start/Continue\n"
                            "P - Pause\n"
                            "Q - Quit");
  } else {
    help_label = new QLabel("CONTROLS:\n"
                            "← → - Move left/right\n"
                            "↓ - Move down\n"
                            "Double ↓ - Move fast down\n"
                            "S - Start/Continue\n"
                            "P - Pause\n"
                            "Q - Quit");
  }

  help_label->setObjectName("helpFrame");
  help_label->setStyleSheet("color: #CCCCCC; font: 16px; line-height: 1.5;");
  QVBoxLayout *layout = new QVBoxLayout(frame);
  layout->addWidget(help_label);

  return frame;
}

QFrame *Window::createNextFigureBlock() {
  QFrame *frame = new QFrame;
  frame->setStyleSheet("QFrame {"
                       "   background: #252525;"
                       "   border-radius: 12px;"
                       "   padding: 5px;"
                       "}");

  QLabel *title_label = new QLabel("Next Figure", frame);
  title_label->setStyleSheet("color: #888888; font: bold 16px;");

  next_figure_widget_ = new NextFigureWidget(frame);
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
  game_area_->setGameInfo(&game_info_);
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
      next_figure_widget_ = findChild<NextFigureWidget *>("nextFigureWidget");
      if (!next_figure_widget_) {
        QFrame *next_figure_block = createNextFigureBlock();
        next_figure_widget_ = next_figure_block->findChild<NextFigureWidget *>(
            "nextFigureWidget");
        if (next_figure_widget_) {
          right_layout->addWidget(next_figure_block);
        }
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

} // namespace s21
