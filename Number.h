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

  void setInteger(const std::vector<unsigned char>& integer) {
    integer_ = integer;
  }

  std::vector<unsigned char> getInteger() const {
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

  bool isMinus() const {
    return minus_;
  }

  void setMinus(bool minus) {
    minus_ = minus;
  }


  friend Number operator+(const Number& num1, const Number& num2);
  friend Number operator*(Number num1, Number num2);
  friend Number operator/(Number num1, int divider);
  friend int operator%(Number num1, int divider);

  Number operator+=(const Number& other);
  Number operator*=(const Number& other);
  Number operator/=(int other);

  friend bool operator==(const Number& num1, const Number& num2);
  friend bool operator!=(const Number& num1, const Number& num2);

  std::string toString();

  friend std::ostream& operator<<(std::ostream& out, Number num) {
    out << num.toString();

    return out;
  }

  static int toNum(const std::string& str);
  static int toNum(char c);

 private:
  std::vector<unsigned char> integer_, fraction_;
  int base_;
  bool minus_;
};
