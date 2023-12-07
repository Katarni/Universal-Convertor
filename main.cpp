#include "App.h"

int main(int argc, char *argv[]) {
//  QApplication a(argc, argv);
//
//  App convertor(600, 500);
//  convertor.render();
//
//  return QApplication::exec();

  Fraction fract(Fraction(Number("55", 10), Number("2", 10)));
  std::cout << Fraction::normalizeFract(fract) << '\n';
  std::cout << fract.num();
}
