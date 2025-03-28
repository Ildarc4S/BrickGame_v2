#pragma once

#include "./../desktop/include/window.h"
#include "./../../brick_game/spec/game_spec.h"

namespace s21 {

class Controller : public QObject {
  Q_OBJECT

 public:
  explicit Controller(Window* window, QObject* parrent = nullptr);
  ~Controller() = default;

  void update_game();

 private slots:
  void processUserInput(int key, bool hold);
  void handleRestart();
  void handleStartContinue();
  void handleExit();

 private:
  UserAction_t convertKeyToAction(int key);

 private:
  Window* view_;
  QTimer* timer_;
};

}  // namespace s21
