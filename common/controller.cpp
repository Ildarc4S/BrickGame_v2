#include "./controller.h"
#include <QDebug>
#include <QTimer>
#include <QApplication>

namespace s21 {

Controller::Controller(Window* view, QObject* parent)
  : QObject(parent),
    view_(view) {
      connect(view_, &Window::keyPressed, this, &Controller::processUserInput);
      QTimer *timer = new QTimer(this);
      connect(timer, &QTimer::timeout, this, &Controller::update_game);
      timer->start(10);
}

UserAction_t Controller::convertKeyToAction(int key) {
  UserAction_t action = UserAction_t::Action;
  switch (key) {
    case Qt::Key_Left:
      action = UserAction_t::Left;
      break;
    case Qt::Key_Right:
      action = UserAction_t::Right;
      break;
      case Qt::Key_Up:
      action = UserAction_t::Up;
      break;
      case Qt::Key_Down:
      action = UserAction_t::Down;
      break;
     case Qt::Key_Space:
      action = UserAction_t::Action;
      break;
     case Qt::Key_P:
      action = UserAction_t::Pause;
      break;
     case Qt::Key_S:
      action = UserAction_t::Start;
      break;
     case Qt::Key_Q:
      action = UserAction_t::Terminate;
      break;
  }

  return action;
}

void Controller::processUserInput(int key, bool hold) {
  UserAction_t action = convertKeyToAction(key);
  userInput(action, hold);
}

void Controller::update_game() {
  GameInfo_t game_info = updateCurrentState();

  if (game_info.pause == 5) {
    QApplication::quit();
  } else {
    view_->setGameInfo(game_info);
    view_->update();
  }
}

}  // namespace s21
