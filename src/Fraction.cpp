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
  std::vector<unsigned char> period_fract_num = number.getPeriod();
  std::reverse(period_fract_num.begin(), period_fract_num.end());
  period_fract.num_ = Number(period_fract_num, std::vector<unsigned char>(0), 10);
  period_fract.den_ = Number::binaryPow(Number("10", 10), (int)number.getPeriod().size() + number.getFraction().size())--;
  period_fract.den_ *= Number::binaryPow(Number("10", 10), number.getFraction().size());

  std::vector<unsigned char> pre_period_num = number.getInteger();
  pre_period_num.insert(pre_period_num.end(), number.getFraction().begin(), number.getFraction().end());
  pre_period_fract.num_ = Number(pre_period_num, std::vector<unsigned char>(0), 10);
  pre_period_fract.den_ = Number::binaryPow(Number("10", 10), (int)number.getFraction().size());

  *this = pre_period_fract + period_fract;
  if (this->den_ == Number("0", 10) || this->den_.getInteger().empty()) {
    this->den_ = Number("1", 10);
  }
}

Fraction operator+(const Fraction& fract1, const Fraction& fract2) {
  Fraction res;
  Number dens_lcm = Number::lcm(fract1.den_, fract2.den_);
  res.num_ = fract1.num_ * Number::integerDivision(dens_lcm, fract1.den_) +
              fract2.num_ * Number::integerDivision(dens_lcm, fract2.den_);
  res.den_ = dens_lcm;
  return res;
}

Fraction Fraction::operator+=(const Fraction &other) {
  *this = *this + other;
  return *this;
}

Fraction operator/(const Fraction& fract, const Number& num) {
  return Fraction(fract.num_, fract.den_ * num);
}

Fraction Fraction::operator/=(const Number &other) {
  *this = *this / other;
  return *this;
}

Number Fraction::toNum() {
  return num_ / den_;
}
