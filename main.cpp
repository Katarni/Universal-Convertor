#include "App.h"

int main(int argc, char *argv[]) {
//  QApplication a(argc, argv);
//
//  App convertor(600, 500);
//  convertor.render();
//
//  return QApplication::exec();

  Number num1("1.4(3)", 10), num2("1.5(23)", 10);
  std::cout << num1 + num2;
}