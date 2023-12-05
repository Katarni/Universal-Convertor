//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#pragma once
#include "header.h"


class Number {
 public:
  Number(): integer_(std::vector<unsigned char>(0)),
          base_(10),
          fraction_(std::vector<unsigned char>(0)),
          period_(std::vector<unsigned char>(0)),
          minus_(false) {}
  Number(const std::vector<unsigned char>& num,
         const std::vector<unsigned char>& fraction,
         int base): integer_(num),
                    base_(base), fraction_(fraction),
                    period_(std::vector<unsigned char>(0)),
                    minus_(false) {}
  Number(const Number& other): integer_(other.integer_),
                              base_(other.base_),
                              fraction_(other.fraction_),
                              period_(other.period_),
                              minus_(other.minus_){}
  Number(const std::string& num, int base) {
    bool bracket = false, dot = false;
    minus_ = false;
    std::string let;
    std::vector<unsigned char> str;
    for (char c : num) {
      if (c == '-') {
        minus_ = true;
        continue;
      }

      if (c == '.') {
        std::reverse(str.begin(), str.end());
        integer_ = str;
        str.clear();
        dot = true;
        continue;
      }

      if (c == '(') {
        fraction_ = str;
        str.clear();
        continue;
      }

      if (c == ')') {
        period_ = str;
        str.clear();
        continue;
      }

      if (c == '[') {
        bracket = true;
        continue;
      }

      if (c == ']') {
        bracket = false;
        str.push_back(Number::toNum(let));
        let.clear();
        continue;
      }

      if (bracket) {
        let.push_back(c);
      } else {
        str.push_back(Number::toNum(c));
      }
    }

    if (!str.empty() && !dot) {
      std::reverse(str.begin(), str.end());
      integer_ = str;
    } else if (!str.empty() && dot) {
      fraction_ = str;
    }

    base_ = base;
  }

  Number (const std::vector<unsigned char>& num,
          const std::vector<unsigned char>& fraction,
          const std::vector<unsigned char>& period,
          int base): integer_(num),
                    base_(base), fraction_(fraction),
                    period_(period),
                    minus_(false) {}

  Number& operator=(const Number& other) {
    integer_ = other.integer_;
    fraction_ = other.fraction_;
    minus_ = other.minus_;
    base_ = other.base_;
    period_ = other.period_;
    return *this;
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

  const std::vector<unsigned char> &getPeriod() const;

  void setPeriod(const std::vector<unsigned char> &period);

  friend Number operator+(Number num1, Number num2);
  friend Number operator*(Number num1, Number num2);
  friend Number operator/(Number num1, int divider);
  friend Number operator/(Number num1, int64_t divider);
  friend int operator%(Number num1, int divider);

  Number operator+=(const Number& other);
  Number operator*=(const Number& other);
  Number& operator/=(int divider);
  Number& operator/=(int64_t divider);

  friend bool operator==(const Number& num1, const Number& num2);
  friend bool operator!=(const Number& num1, const Number& num2);

  friend Number operator--(Number num, int x);

  std::string toString();

  friend std::ostream& operator<<(std::ostream& out, Number num) {
    out << num.toString();
    return out;
  }

  static int toNum(const std::string& str);
  static int toNum(char c);

  static std::string toLet(unsigned char c);

  static Number binaryPow(const Number& num, int pow);

  int64_t toInt64();
  int64_t toInt64() const;

 private:
  std::vector<unsigned char> integer_, fraction_, period_;
  int base_;
  bool minus_;

  static void normalizePeriods(Number& num1, Number& num2);

  static int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
  }

  static int lcm(int a, int b) {
    return a * b / gcd(a, b);
  }
};
