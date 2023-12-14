//
// Created by Timur Akhmetzianov on 28.11.2023.
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
                              minus_(other.minus_) {}
  Number(const std::string& num, int base);

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

  void setMinus(bool minus) {
    minus_ = minus;
  }

  const std::vector<unsigned char> &getPeriod() const {
    return period_;
  }
  void setPeriod(const std::vector<unsigned char> &period) {
    period_ = period;
  }

  friend Number operator+(Number num1, Number num2);
  friend Number operator-(Number num1, Number num2);
  friend Number operator*(Number num1, Number num2);
  friend Number operator*(const Number &num1, int num2);
  friend Number operator/(Number num1, Number divider);
  friend int operator%(Number num1, uint64_t divider);
  friend Number operator%(const Number& num, const Number& divider);

  friend Number operator+(const Number& num1, int num2);

  Number& operator+=(const Number& other);
  Number& operator*=(const Number& other);
  Number& operator-=(const Number& other);
  Number& operator/=(const Number& other);

  friend bool operator==(const Number& num1, const Number& num2);
  friend bool operator!=(const Number& num1, const Number& num2);

  friend Number operator--(Number num, int x);
  friend Number operator++(Number& num);
  friend Number operator--(Number& num);

  friend bool operator<(const Number& num1, const Number& num2);
  friend bool operator<=(const Number& num1, const Number& num2);
  friend bool operator>(const Number& num1, const Number& num2);

  static unsigned char integerDivision(const Number& num, const Number& divider);

  std::string toString();

  friend std::ostream& operator<<(std::ostream& out, Number num) {
    out << num.toString();
    return out;
  }

  static int toNum(const std::string& str);
  static int toNum(char c);

  static std::string toLet(unsigned char c);

  static Number binaryPow(const Number& num, int pow);

  uint64_t toInt64() const;

  static void normalizePeriods(Number& num, int pre_period_size);

  void reversePeriod();

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
