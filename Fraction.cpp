//
// Created by Тимур Ахметзянов on 07.12.2023.
//

#include "Fraction.h"

bool operator==(const Fraction &fract_first, const Fraction &fract_second) {
  return fract_first.num_ == fract_second.num_ && fract_first.den_ == fract_second.den_;
}

bool operator!=(const Fraction &fract_first, const Fraction &fract_second) {
  return !(fract_first == fract_second);
}

Fraction operator*(Fraction fract, const Number& num) {
  fract.num_ *= num;
  return fract;
}
