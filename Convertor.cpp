//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#include "Convertor.h"

bool Convertor::isGood(const std::string& number, int base) {
  std::string let;
  bool bracket = false;
  for (char c : number) {
    if (c == '.' || c == '(' || c == ')') continue;

    if (c == '[') {
      bracket = true;
      continue;
    }
    if (c == ']') {
      bracket = false;
      int num = Number::toNum(let);
      let.clear();
      if (num >= base) {
        return false;
      }
      continue;
    }

    if (bracket) {
      let.push_back(c);
    } else if (Number::toNum(c) >= base) {
      return false;
    }
  }

  return true;
}

std::string Convertor::convert(const std::string& num, int base, int target) {
  if (!isGood(num, base)) {
    return "число не корректно";
  }

  std::vector<unsigned char> str;

  Number integer, pre_period, period;
  integer.setBase(base);
  pre_period.setBase(base);
  period.setBase(base);

  bool bracket = false, dot = false;
  std::string let;
  for (char c : num) {
    if (c == '.') {
      std::reverse(str.begin(), str.end());
      integer.setNum(str);
      str.clear();
      dot = true;
      continue;
    }

    if (c == '(') {
      std::reverse(str.begin(), str.end());
      pre_period.setNum(str);
      str.clear();
      continue;
    }

    if (c == ')') {
      std::reverse(str.begin(), str.end());
      period.setNum(str);
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
    integer.setNum(str);
  } else if (!str.empty() && dot) {
    pre_period.setNum(str);
  }

  if (target == 10) {
    Number converted_integer = convertIntToDecSys(integer);
//    Number converted_pre_period = convertPrePeriodToDecSys(pre_period);
//    Number converted_period = convertPeriodToDecSys(period, int(pre_period.getNum().size()));

    std::cout << converted_integer;
  } else if (base == 10) {

  } else {

  }

  return std::string();
}

Number Convertor::convertIntToDecSys(const Number &num) {
  Number converted(std::vector<unsigned char>(0), 10);
  Number power(1, 10);

  for (unsigned char c : num.getNum()) {
    converted += power * Number(c, 10);
    power *= Number(num.getBase(), 10);
  }

  return converted;
}

Number Convertor::convertPrePeriodToDecSys(const Number &num) {
  if (num.getNum().empty()) return Number(std::vector<unsigned char>(0), 10);
  return Number();
}

Number Convertor::convertPeriodToDecSys(const Number &num, int pre_period_size) {
  if (num.getNum().empty()) return Number(std::vector<unsigned char>(0), 10);
  return Number();
}
