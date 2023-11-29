//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#include "Number.h"


Number operator+(const Number &num1, const Number &num2) {
  std::vector<unsigned char> res(std::max(num1.num_.size(), num2.num_.size()));
  int carry = 0;
  for (int i = 0; i < res.size(); ++i) {
    if (i >= num1.num_.size()) {
      res[i] = ((int)num2.num_[i] + carry) % num1.base_;
      carry = ((int)num2.num_[i] + carry) / num1.base_;
      continue;
    }

    if (i >= num2.num_.size()) {
      res[i] = ((int)num1.num_[i] + carry) % num1.base_;
      carry = ((int)num1.num_[i] + carry) / num1.base_;
      continue;
    }

    res[i] = ((int)num1.num_[i] + (int)num2.num_[i] + carry) % num1.base_;
    carry = ((int)num1.num_[i] + (int)num2.num_[i] + carry) / num1.base_;
  }

  if (carry) {
    res.push_back(carry);
  }

  return Number(res, num1.base_);
}

Number operator*(const Number &a, const Number &b) {
  int carry = 0;
  std::vector<unsigned char> c(a.num_.size() + b.num_.size());
  for (int i = 0; i < a.num_.size(); ++i) {
    for (int j = 0; j < b.num_.size() || carry; ++j) {
      int64_t cur = c[i + j] + a.num_[i] * 1ll * (j < b.num_.size() ? b.num_[j] : 0) + carry;
      c[i+j] = int (cur % a.base_);
      carry = int (cur / a.base_);
    }
  }

  while (c.size() > 1 && c.back() == 0) {
    c.pop_back();
  }

  return Number(c, a.base_);
}

Number Number::operator+=(const Number &other) {
  *this = *this + other;
  return *this;
}

Number Number::operator*=(const Number &other) {
  *this = *this * other;
  return *this;
}

int Number::getBase() const {
  return base_;
}

void Number::setBase(int base) {
  base_ = base;
}

int Number::toNum(const std::string& str) {
  int n = 0;
  for (char c : str) {
    n = n * 10 + c - '0';
  }
  return n;
}

int Number::toNum(char c) {
  if (c <= '9') {
    return c - '0';
  }

  return c - 'A' + 10;
}

std::string Number::toString() {
  return std::string();
}
