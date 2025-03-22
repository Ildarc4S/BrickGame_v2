#include "./controller.h"
#include <QDebug>
#include <QTimer>
#include <QApplication>

namespace s21 {

Controller::Controller(Window* view, QObject* parent)
  : QObject(parent),
    view_(view) {
      connect(view_, &Window::keyPressed, this, &Controller::processUserInput);
      connect(view_, &Window::pauseClicked, this, &Controller::handleStartContinue);
      connect(view_, &Window::restartClicked, this, &Controller::handleRestart);
      connect(view_, &Window::exitClicked, this, &Controller::handleExit);

      timer_ = new QTimer(this);
      connect(timer_, &QTimer::timeout, this, &Controller::update_game);
      timer_->start(1);
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

void Controller::handleExit() {
  userInput(UserAction_t::Terminate, false);
  QApplication::quit();
  qDebug() << "Exit button clicked!";
}

void Controller::handleStartContinue() {
  userInput(UserAction_t::Start, false);
  qDebug() << "Start button clicked!";
}

void Controller::handleRestart() {
  qDebug() << "Restart button clicked!";
  userInput(UserAction_t::Start, false);
}

void Controller::processUserInput(int key, bool hold) {
  UserAction_t action = convertKeyToAction(key);
  userInput(action, hold);
  if (action == Terminate) {
    QApplication::quit();
  }
}

void Controller::update_game() {
  GameInfo_t game_info = updateCurrentState();

  view_->setGameInfo(game_info);
  view_->update();
}

}  // namespace s21
