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
  Number left("0", 10), right(fract.num_);
  while (left < right) {
    Number mid = (left + right) / 2;
    if (Number::ceil(fract.den_ * mid) > fract.num_) {
      mid.setFraction(std::vector<unsigned char>(0));
      right = mid--;
    } else if (Number::ceil(fract.den_ * mid) < fract.num_) {
      mid.setFraction(std::vector<unsigned char>(0));
      left = mid + 1;
    } else {
      mid.setFraction(std::vector<unsigned char>(0));
      left = mid;
      break;
    }
  }

  for (Number i("0", 10); i < fract.den_ * left; ++i) {
    --fract.num_;
  }

  return left;
}
