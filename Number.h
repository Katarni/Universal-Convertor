//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#pragma once
#include "header.h"


class Number {
 public:
  Number(): num_(std::vector<unsigned char>(0)), base_(10) {}
  Number(const std::vector<unsigned char>& num, int base): num_(num), base_(base) {}
  Number(const Number& other): num_(other.num_), base_(other.base_) {}
  Number(int num, int base) {
    while (num > 0) {
      num_.push_back(num % base);
      num /= base;
    }
    base_ = base;
  }
  Number(std::string num, int base) {
    for (int i = num.size() - 1; i >= 0; --i) {
      num_.push_back(toNum(num[i]));
    }
    base_ = base;
  }

  void setNum(const std::vector<unsigned char>& num) {
    num_ = num;
  }

  std::vector<unsigned char> getNum() const {
    return num_;
  }

  int getBase() const;

  void setBase(int base);

  friend Number operator+(const Number& num1, const Number& num2);
  friend Number operator*(const Number& num1, const Number& num2);

  Number operator+=(const Number& other);
  Number operator*=(const Number& other);

  friend std::ostream& operator<<(std::ostream& out, const Number& num) {
    for (int i = (int)num.num_.size() - 1; i >= 0; --i) {
      if (num.num_[i] < 10) {
        out << int(num.num_[i]);
      } else if (num.num_[i] < 36) {
        out << char(num.num_[i] - 10 + 'A');
      } else {
        out << '[' << num.num_[i] << ']';
      }
    }
    return out;
  }

  static int toNum(const std::string& str);
  static int toNum(char c);

  std::string toString();

 private:
  std::vector<unsigned char> num_;
  int base_;
};
