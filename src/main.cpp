#include "App.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  App convertor(600, 500);
  convertor.render();

  return QApplication::exec();
}
