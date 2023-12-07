//
// Created by Тимур Ахметзянов on 07.12.2023.
//

#pragma once
#include "Number.h"


class Fraction {
 public:
  Fraction() {
    num_ = Number("0", 10);
    den_ = Number("1", 10);
  };
  Fraction(const Number& num, const Number& den): num_(num), den_(den) {}

  Fraction(const Fraction &other) {
    num_ = other.num_;
    den_ = other.den_;
  }

  Number num() const { return num_; }
  Number den() const { return den_; }

  friend bool operator==(const Fraction &fract_first,
                         const Fraction &fract_second);
  friend bool operator!=(const Fraction &fract_first,
                         const Fraction &fract_second);

  friend Fraction operator*(Fraction fract, const Number& num);

 private:
  Number num_, den_;
};
