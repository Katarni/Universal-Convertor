#include "App.h"

int main(int argc, char *argv[]) {
//  QApplication a(argc, argv);
//
//  App convertor(600, 500);
//  convertor.render();
//
//  return QApplication::exec();

  std::cout << Convertor::convert("4891.5(3)", 10, 8);
}
