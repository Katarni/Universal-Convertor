//
// Created by Timur Akhmetzianov on 28.11.2023.
//

#include "Number.h"

Number::Number(const std::string &num, int base) {
  bool bracket = false, dot = false;
  minus_ = false;
  std::string let;
  std::vector<unsigned char> str;
  for (char c : num) {
    if (c == '-') {
      minus_ = true;
      continue;
    }

    if (c == '.' || c == ',') {
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

Number operator+(Number num1, Number num2) {
  int carry = 0;

  if (!num1.period_.empty() || !num2.period_.empty()) {
    Number::normalizePeriods(num1, num2);
  }
  std::vector<unsigned char> res_period(num1.period_.size());
  for (int i = (int)res_period.size() - 1; i >= 0; --i) {
    res_period[i] = ((int)num1.period_[i] + (int)num2.period_[i] + carry) % num1.base_;
    carry = ((int)num1.period_[i] + (int)num2.period_[i] + carry) / num1.base_;
  }

  int p_carry = carry;
  for (int i = (int)res_period.size() - 1; i >= 0 && p_carry > 0; --i) {
    res_period[i] = ((int)res_period[i] + p_carry) % num1.base_;
    p_carry = ((int)res_period[i] + p_carry) / num1.base_;
    if (!i && p_carry) {
      i = (int)res_period.size();
    }
  }

  std::vector<unsigned char> res_frac(std::max(num1.fraction_.size(), num2.fraction_.size()));
  for (int i = (int)res_frac.size() - 1; i >= 0; --i) {
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

  if (!res_period.empty() && res_frac.empty()) {
    res_frac.push_back(0);
  }

  if (carry) {
    res_int.push_back(carry);
  }

  return Number(res_int, res_frac, res_period, num1.base_);
}

Number operator*(Number num1, Number num2) {
  int dot = (int)num1.fraction_.size() + (int)num2.fraction_.size();
  int carry = 0;

  std::vector<unsigned char> res_int(num1.integer_.size() +
                                      num2.integer_.size() +
                                      num1.fraction_.size() +
                                      num2.fraction_.size());

  std::reverse(num1.fraction_.begin(), num1.fraction_.end());
  std::reverse(num2.fraction_.begin(), num2.fraction_.end());
  num1.integer_.insert(num1.integer_.begin(), num1.fraction_.begin(), num1.fraction_.end());
  num2.integer_.insert(num2.integer_.begin(), num2.fraction_.begin(), num2.fraction_.end());
  num2.fraction_.clear();
  num1.fraction_.clear();

  for (int i = 0; i < num1.integer_.size(); ++i) {
    for (int j = 0; j < num2.integer_.size() || carry; ++j) {
      uint64_t cur = res_int[i + j] + (uint64_t)num1.integer_[i] * (j < num2.integer_.size() ? num2.integer_[j] : 0) + carry;
      res_int[i + j] = int (cur % num1.base_);
      carry = int (cur / num1.base_);
    }
  }

  while (res_int.size() > 1 && res_int.back() == 0) {
    res_int.pop_back();
  }

  if (res_int.empty()) {
    res_int.push_back(0);
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

Number& Number::operator+=(const Number &other) {
  *this = *this + other;
  return *this;
}

Number& Number::operator*=(const Number &other) {
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

  if (minus_) {
    str += '-';
  }

  for (int i = (int)integer_.size() - 1; i >= 0; --i) {
    str += toLet(integer_[i]);
  }

  if (!fraction_.empty() || !period_.empty()) {
    str += ".";
  }

  for (unsigned char c : fraction_) {
    str += toLet(c);
  }

  if (period_.empty()) {
    return str;
  }

  str += "(";

  for (unsigned char c : period_) {
    str += toLet(c);
  }

  str += ")";

  return str;
}

Number operator/(Number num, int divider) {
  bool minus = divider < 0;
  num /= uint64_t(abs(divider));
  num.setMinus(minus ^ num.minus_);
  return num;
}

Number operator/(Number num, uint64_t divider) {
  if (divider == 1) {
    return num;
  }

  int dot = 0;
  if (!num.fraction_.empty()) {
    std::reverse(num.fraction_.begin(), num.fraction_.end());
    num.integer_.insert(num.integer_.begin(), num.fraction_.begin(), num.fraction_.end());
    dot += (int)num.fraction_.size();
    num.fraction_.clear();
  }

  if (num % divider != 0) {
    for (int i = 0; i < 10; ++i) {
      ++dot;
      num.integer_.insert(num.integer_.begin(), 0);
    }
  }

  std::set<std::pair<uint64_t, int>> find_period;

  int k = 0, period_start = -1, carry = 0;
  for (int i = (int)num.integer_.size() - 1; i >= 0; --i) {
    uint64_t cur = num.integer_[i] + (uint64_t)carry * num.base_;

    auto it = find_period.lower_bound({cur, 0});
    if (it != find_period.end() && it->first == cur) {
      period_start = it->second;
      break;
    }
    find_period.insert({cur, k});
    num.integer_[i] = static_cast<unsigned char>(cur / divider);
    carry = int(cur % divider);
    ++k;
  }

  while (num.integer_.size() > 1 && num.integer_.back() == 0) {
    num.integer_.pop_back();
  }

  bool plus = false;

  while (dot > 0 && (int)num.integer_.size() > 0) {
    num.fraction_.insert(num.fraction_.begin(), num.integer_.front());
    num.integer_.erase(num.integer_.begin());
    --dot;
    period_start = !plus ? period_start - 1 : period_start + 1;
    if (period_start <= 0) plus = true;
  }

  while (dot > 0) {
    num.fraction_.insert(num.fraction_.begin(), 0);
    --dot;
    period_start = !plus ? period_start - 1 : period_start + 1;
    if (period_start <= 0) plus = true;
  }

  while (!num.fraction_.empty() && num.fraction_.back() == 0) {
    num.fraction_.pop_back();
  }

  if (num.integer_.empty()) {
    num.integer_.push_back(0);
  }

  if (period_start > -1 && !num.fraction_.empty()) {
    num.period_ = std::vector<unsigned char>(num.fraction_.begin() + period_start, num.fraction_.end());
    num.fraction_.resize(period_start);
  }

  return num;
}

int operator%(Number num1, int divider) {
  int carry = 0;
  for (int i=(int)num1.integer_.size()-1; i>=0; --i) {
    long long cur = num1.integer_[i] + (uint64_t)carry * num1.base_;
    num1.integer_[i] = int (cur / divider);
    carry = int (cur % divider);
  }

  return carry;
}

bool operator==(const Number &num1, const Number &num2) {
  if (num1.base_ != num2.base_) return false;
  if (num1.integer_.size() != num2.integer_.size()) return false;
  if (num1.fraction_.size() != num2.fraction_.size()) return false;

  for (int i = 0; i < num1.integer_.size(); ++i) {
    if (num1.integer_[i] != num2.integer_[i]) return false;
  }

  for (int i = 0; i < num1.fraction_.size(); ++i) {
    if (num1.fraction_[i] != num2.fraction_[i]) return false;
  }

  return true;
}

bool operator!=(const Number &num1, const Number &num2) {
  return !(num1 == num2);
}

Number Number::binaryPow(const Number &num, int pow) {
  if (pow == 0) return Number("1", 10);
  if (pow % 2 == 0) return binaryPow(num * num, pow / 2);
  return num * binaryPow(num, pow - 1);
}

Number operator--(Number num, int x) {
  for (int i = 0; i < num.integer_.size(); ++i) {
    if (num.integer_[i] != 0) {
      num.integer_[i] -= 1;
      break;
    }
    if (i == num.integer_.size() - 1) {
      num.minus_ = true;
      break;
    }
    num.integer_[i] = num.base_ - 1;
  }

  while (!num.integer_.empty() && num.integer_.back() == 0) {
    num.integer_.pop_back();
  }

  if (num.integer_.empty()) {
    num.integer_.push_back(0);
  }

  return num;
}

Number& Number::operator/=(int divider) {
  *this = *this / divider;
  return *this;
}

Number& Number::operator/=(uint64_t divider) {
  *this = *this / divider;
  return *this;
}

std::string Number::toLet(unsigned char c) {
  std::string str;
  if (c < 10) {
    str += char(c + '0');
  } else if (c < 36) {
    str += char(c - 10 + 'A');
  } else {
    str += "[" + std::to_string(c) + "]";
  }
  return str;
}

uint64_t Number::toInt64() const {
  uint64_t sum = 0;
  for (int i = (int)integer_.size(); i >= 0; --i) {
    sum = sum * 10 + integer_[i];
  }
  return sum;
}

void Number::normalizePeriods(Number &num1, Number &num2) {
  if (num1.fraction_.size() > num2.fraction_.size()) {
    if (num2.period_.empty()) {
      num2.period_.resize(num1.period_.size());
      return;
    }

    while (num1.fraction_.size() != num2.fraction_.size()) {
      num2.fraction_.push_back(num2.period_.front());
      num2.period_.push_back(num2.period_.front());
      num2.period_.erase(num2.period_.begin());
    }
  } else if (num2.fraction_.size() > num1.fraction_.size()) {
    if (num1.period_.empty()) {
      num1.period_.resize(num2.period_.size());
      return;
    }

    while (num1.fraction_.size() != num2.fraction_.size()) {
      num1.fraction_.push_back(num1.period_.front());
      num1.period_.push_back(num1.period_.front());
      num1.period_.erase(num1.period_.begin());
    }
  }

  if (num1.period_.empty()) {
    num1.period_.resize(num2.period_.size());
    return;
  }
  if (num2.period_.empty()) {
    num2.period_.resize(num1.period_.size());
    return;
  }
  if (num1.period_.size() == num2.period_.size()) return;

  int size_lcm = lcm((int)num1.period_.size(), (int)num2.period_.size());
  int multiple_num1 = (size_lcm / (int)num1.period_.size()) - 1;
  std::vector<unsigned char> template_num1 = num1.period_;
  for (int i = 0; i < multiple_num1; ++i) {
    num1.period_.insert(num1.period_.end(), template_num1.begin(), template_num1.end());
  }

  int multiple_num2 = (size_lcm / (int)num2.period_.size()) - 1;
  std::vector<unsigned char> template_num2 = num2.period_;
  for (int i = 0; i < multiple_num2; ++i) {
    num2.period_.insert(num2.period_.end(), num2.period_.begin(), num2.period_.end());
  }
}

void Number::normalizePeriods(Number &num, int pre_period_size) {
  int period_size = num.integer_.size();

  for (int i = 0, j = 0; i < pre_period_size; ++i, j = j != period_size - 1 ? j + 1 : 0) {
    num.integer_.push_back(num.integer_[j]);
  }
}

Number operator++(Number &num) {
  num += Number("1", 10);
  return num;
}

bool operator<(const Number &num1, const Number &num2) {
  if (num1.integer_.size() < num2.integer_.size()) return true;
  if (num1.integer_.size() > num2.integer_.size()) return false;

  for (int i = (int)num1.integer_.size() - 1; i >= 0; --i) {
    if (num1.integer_[i] < num2.integer_[i]) return true;
    if (num1.integer_[i] > num2.integer_[i]) return false;
  }

  for (int i = 0; i < std::min(num1.fraction_.size(), num2.fraction_.size()); ++i) {
    if (num1.fraction_[i] < num2.fraction_[i]) return true;
    if (num1.fraction_[i] > num2.fraction_[i]) return false;
  }

  return num1.fraction_.size() < num2.fraction_.size();
}

bool operator>(const Number &num1, const Number &num2) {
  return !(num1 < num2) && num1 != num2;
}

Number operator+(const Number& num1, int num2) {
  return num1 + Number(std::to_string(num2), 10);
}

Number operator--(Number& num) {
  for (int i = 0; i < num.integer_.size(); ++i) {
    if (num.integer_[i] != 0) {
      num.integer_[i] -= 1;
      break;
    }
    if (i == num.integer_.size() - 1) {
      num.minus_ = true;
      break;
    }
    num.integer_[i] = num.base_ - 1;
  }

  while (!num.integer_.empty() && num.integer_.back() == 0) {
    num.integer_.pop_back();
  }

  if (num.integer_.empty()) {
    num.integer_.push_back(0);
  }

  return num;
}

bool operator<=(const Number &num1, const Number &num2) {
  return num1 < num2 || num1 == num2;
}

void Number::reversePeriod() {
  std::reverse(period_.begin(), period_.end());
}

Number operator-(Number num1, Number num2) {
  if (num2 > num1) {
    Number res = num2 - num1;
    res.minus_ = true;
    return res;
  }

  int carry = 0;
  for (int i = 0; i < num2.integer_.size() || carry; ++i) {
    int temp_carry = num1.integer_[i] < (carry + (i < num2.integer_.size() ? num2.integer_[i] : 0));
    num1.integer_[i] -= carry + (i < num2.integer_.size() ? num2.integer_[i] : 0);
    carry = temp_carry;
    if (carry)  num1.integer_[i] += num1.base_;
  }
  while (num1.integer_.size() > 1 && num1.integer_.back() == 0) {
    num1.integer_.pop_back();
  }
  return num1;
}

Number &Number::operator-=(const Number &other) {
  *this = *this - other;
  return *this;
}
