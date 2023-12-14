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

Number Fraction::normalizeFract(Fraction &fract) {
  Number ans("0", 10);
  while (fract.den_ * (ans + 1) <= fract.num_) {
    ++ans;
  }

  fract.num_ -= fract.den_ * ans;
  return ans;
}

Fraction operator*(const Fraction& fract, int num) {
  return fract * Number(std::to_string(num), 10);
}

Fraction Fraction::operator*=(int other) {
  *this = *this * other;
  return *this;
}

Fraction Fraction::operator*=(const Number &other) {
  *this = *this * other;
  return *this;
}

Fraction::Fraction(const Number &number) {
  Fraction pre_period_fract, period_fract;
  pre_period_fract.num_ = Number(number.getPeriod(), std::vector<unsigned char>(0), 10);
  pre_period_fract.den_ = Number::binaryPow(Number("10", 10), (int)number.getPeriod().size() + number.getFraction().size())--;
  pre_period_fract.den_ *= Number::binaryPow(Number("10", 10), number.getFraction().size());


}
