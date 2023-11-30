//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#pragma once
#include "header.h"


class Number {
 public:
  Number(): integer_(std::vector<unsigned char>(0)), base_(10), fraction_(std::vector<unsigned char>(0)) {}
  Number(const std::vector<unsigned char>& num,
         const std::vector<unsigned char>& fraction,
         int base): integer_(num), base_(base), fraction_(fraction) {}
  Number(const Number& other): integer_(other.integer_),
                              base_(other.base_),
                              fraction_(other.fraction_) {}
  Number(std::string num, int base) {
    std::vector<unsigned char> let;
    for (int i = (int)num.size() - 1; i >= 0; --i) {
      if (num[i] == '.') {
        std::reverse(let.begin(), let.end());
        fraction_ = let;
        let.clear();
        continue;
      }

      let.push_back(toNum(num[i]));
    }
    integer_ = let;
    base_ = base;
  }

  void setNum(const std::vector<unsigned char>& num) {
    integer_ = num;
  }

  std::vector<unsigned char> getNum() const {
    return integer_;
  }

  int getBase() const {
    return base_;
  }

  void setBase(int base) {
    base_ = base;
  }

  const std::vector<unsigned char>& getFraction() const {
    return fraction_;
  }

  void setFraction(const std::vector<unsigned char> &fraction) {
    fraction_ = fraction;
  }


  friend Number operator+(const Number& num1, const Number& num2);
  friend Number operator*(Number num1, Number num2);
  friend Number operator/(Number num1, int divider);

  Number operator+=(const Number& other);
  Number operator*=(const Number& other);

  friend std::ostream& operator<<(std::ostream& out, const Number& num) {
    for (int i = (int)num.integer_.size() - 1; i >= 0; --i) {
      if (num.integer_[i] < 10) {
        out << int(num.integer_[i]);
      } else if (num.integer_[i] < 36) {
        out << char(num.integer_[i] - 10 + 'A');
      } else {
        out << '[' << num.integer_[i] << ']';
      }
    }

    if (num.fraction_.size() != 0) {
      out << ".";
    }

    for (int i = 0; i < num.fraction_.size(); ++i) {
      if (num.fraction_[i] < 10) {
        out << int(num.fraction_[i]);
      } else if (num.fraction_[i] < 36) {
        out << char(num.fraction_[i] - 10 + 'A');
      } else {
        out << '[' << num.fraction_[i] << ']';
      }
    }

    return out;
  }

  static int toNum(const std::string& str);
  static int toNum(char c);

  std::string toString();

 private:
  std::vector<unsigned char> integer_, fraction_;
  int base_;
};
