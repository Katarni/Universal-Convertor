//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#include "Number.h"


Number operator+(const Number &num1, const Number &num2) {
  int carry = 0;
  std::vector<unsigned char> res_frac(std::max(num1.fraction_.size(), num2.fraction_.size()));
  for (int i = (int)res_frac.size(); i >= 0; --i) {
    if (i >= num1.fraction_.size()) {
      res_frac[i] = ((int)num2.fraction_[i] + carry) % num1.base_;
      carry = ((int)num2.fraction_[i] + carry) / num1.base_;
      continue;
    }

    if (i >= num2.fraction_.size()) {
      res_frac[i] = ((int)num1.fraction_[i] + carry) % num1.base_;
      carry = ((int)num1.fraction_[i] + carry) / num1.base_;
      continue;
    }

    res_frac[i] = ((int)num1.fraction_[i] + (int)num2.fraction_[i] + carry) % num1.base_;
    carry = ((int)num1.fraction_[i] + (int)num2.fraction_[i] + carry) / num1.base_;
  }

  std::vector<unsigned char> res_int(std::max(num1.integer_.size(), num2.integer_.size()));
  for (int i = 0; i < res_int.size(); ++i) {
    if (i >= num1.integer_.size()) {
      res_int[i] = ((int)num2.integer_[i] + carry) % num1.base_;
      carry = ((int)num2.integer_[i] + carry) / num1.base_;
      continue;
    }

    if (i >= num2.integer_.size()) {
      res_int[i] = ((int)num1.integer_[i] + carry) % num1.base_;
      carry = ((int)num1.integer_[i] + carry) / num1.base_;
      continue;
    }

    res_int[i] = ((int)num1.integer_[i] + (int)num2.integer_[i] + carry) % num1.base_;
    carry = ((int)num1.integer_[i] + (int)num2.integer_[i] + carry) / num1.base_;
  }

  while ((int)res_frac.size() > 0 && res_frac.back() == 0) {
    res_frac.pop_back();
  }

  if (carry) {
    res_int.push_back(carry);
  }

  return Number(res_int, res_frac, num1.base_);
}

Number operator*(Number num1, Number num2) {
  int dot = (int)num1.fraction_.size() + (int)num2.fraction_.size();
  int carry = 0;
  std::vector<unsigned char> res_int(num1.integer_.size() + num2.integer_.size() + num1.fraction_.size() + num2.fraction_.size());
  num1.integer_.insert(num1.integer_.begin(), num1.fraction_.begin(), num1.fraction_.end());
  num2.integer_.insert(num2.integer_.begin(), num2.fraction_.begin(), num2.fraction_.end());
  for (int i = 0; i < num1.integer_.size(); ++i) {
    for (int j = 0; j < num2.integer_.size() || carry; ++j) {
      int64_t cur = res_int[i + j] + num1.integer_[i] * 1ll * (j < num2.integer_.size() ? num2.integer_[j] : 0) + carry;
      res_int[i + j] = int (cur % num1.base_);
      carry = int (cur / num1.base_);
    }
  }

  while (res_int.size() > 1 && res_int.back() == 0) {
    res_int.pop_back();
  }

  std::vector<unsigned char> res_frac;
  while (dot > 0 && (int)res_int.size() > 0) {
    res_frac.insert(res_frac.begin(), res_int.front());
    res_int.erase(res_int.begin());
    --dot;
  }

  while (dot > 0) {
    res_frac.insert(res_frac.begin(), 0);
    --dot;
  }

  while ((int)res_frac.size() > 0 && res_frac.back() == 0) {
    res_frac.pop_back();
  }

  return Number(res_int, res_frac, num1.base_);
}

Number Number::operator+=(const Number &other) {
  *this = *this + other;
  return *this;
}

Number Number::operator*=(const Number &other) {
  *this = *this * other;
  return *this;
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

  return c - 'a' + 10;
}

std::string Number::toString() {
  std::string str;
  for (int i = (int)integer_.size() - 1; i >= 0; --i) {
    if (integer_[i] < 10) {
      str += char(integer_[i]);
    } else if (integer_[i] < 36) {
      str += char(integer_[i] - 10 + 'a');
    } else {
      str += "[" + std::to_string(integer_[i]) + "]";
    }
  }

  if ((int)fraction_.size() != 0) {
    str += ".";
  }

  for (unsigned char c : fraction_) {
    if (c < 10) {
      str += char(c);
    } else if (c < 36) {
      str += char(c - 10 + 'a');
    } else {
      str += "[" + std::to_string(c) + "]";
    }
  }
  return std::string();
}

Number operator/(Number num1, int divider) {
  int carry = 0;

  for (int i = (int)num1.integer_.size() - 1; i >= 0; --i) {
    int64_t cur = num1.integer_[i] + carry * 1ll * num1.base_;
    num1.integer_[i] = static_cast<unsigned char>(cur / divider);
    carry = int(cur % divider);
  }

  while (num1.integer_.size() > 1 && num1.integer_.back() == 0) {
    num1.integer_.pop_back();
  }

  return num1;
}