#include <QApplication>

#include "./include/window.h"
#include "./../common/controller.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::Window window;
  s21::Controller controller(&window);

  window.show();
  return app.exec();
}
