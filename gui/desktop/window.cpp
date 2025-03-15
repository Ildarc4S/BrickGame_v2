#include "./window.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

namespace s21 {
Window::Window(QWidget* parent) : game_info_{0}{ 
}

void Window::setGameInfo(GameInfo_t& game_info) {
  game_info_ = game_info;
}

void Window::keyPressEvent(QKeyEvent* event) {
  emit keyPressed(event->key(), event->isAutoRepeat());
}

void Window::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);

  render(painter);
}

QColor Window::convertObbjectCodeToColor(ObjectCode code) {
  QColor color = Qt::blue;
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
      qDebug() << "Unknown ObjectCode:" << static_cast<int>(code);
      break;
  }
  return color;
}

void Window::renderField(QPainter& painter) {
  int field_rows = FIELD_HEIGHT + 2;
  int field_cols = FIELD_WIDTH + 2;

  int window_width = width() / 2;
  int window_height = height();

  int cell_size = qMin(window_width / field_cols, window_height / field_rows);

  for (int i = 0; i < field_rows; i++) {
    for (int j = 0; j < field_cols; j++) {
      painter.fillRect(
          j * cell_size,
          i * cell_size,
          cell_size,
          cell_size,
          convertObbjectCodeToColor(static_cast<ObjectCode>(game_info_.field[i][j])));

      painter.setPen(Qt::black);
      painter.drawRect(
          j * cell_size,
          i * cell_size,
          cell_size,
          cell_size);
    }
  }
}

void Window::render(QPainter& painter) {
    if (game_info_.field == nullptr)
        return;

    if (game_info_.pause == 2) {
      renderField(painter);
    }
  int window_width = width() / 2;
  int window_height = height();


    if (game_info_.pause == 1 || game_info_.pause == 4) {
        QFont font("Arial", 20, QFont::Bold);
        painter.setFont(font);

        int button_width = 200;
        int button_height = 50;
        int start_x = (window_width - button_width) / 2;
        int start_y = (window_height - 3 * button_height) / 2;

        if (game_info_.pause == 1) {
            painter.setBrush(Qt::lightGray);
            painter.drawRect(start_x, start_y, button_width, button_height);
            painter.setPen(Qt::black);
            painter.drawText(start_x, start_y, button_width, button_height, Qt::AlignCenter, "Continue");

            painter.setBrush(Qt::lightGray);
            painter.drawRect(start_x, start_y + button_height + 10, button_width, button_height);
            painter.setPen(Qt::black);
            painter.drawText(start_x, start_y + button_height + 10, button_width, button_height, Qt::AlignCenter, "Restart");

            painter.setBrush(Qt::lightGray);
            painter.drawRect(start_x, start_y + 2 * (button_height + 10), button_width, button_height);
            painter.setPen(Qt::black);
            painter.drawText(start_x, start_y + 2 * (button_height + 10), button_width, button_height, Qt::AlignCenter, "Exit");
        }

        if (game_info_.pause == 4) {
            painter.setPen(Qt::red);
            painter.drawText(start_x, start_y - 50, button_width, button_height, Qt::AlignCenter, "Game Over");

            painter.setBrush(Qt::lightGray);
            painter.drawRect(start_x, start_y, button_width, button_height);
            painter.setPen(Qt::black);
            painter.drawText(start_x, start_y, button_width, button_height, Qt::AlignCenter, "Restart");

            painter.setBrush(Qt::lightGray);
            painter.drawRect(start_x, start_y + button_height + 10, button_width, button_height);
            painter.setPen(Qt::black);
            painter.drawText(start_x, start_y + button_height + 10, button_width, button_height, Qt::AlignCenter, "Exit");
        }
    }
}
}  // namespace s21
