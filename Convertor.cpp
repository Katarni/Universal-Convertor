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

  Number integer, period;
  integer.setBase(base);
//  period.setBase(base);

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

//    if (c == '(') {
//      integer.setFraction(str);
//      str.clear();
//      continue;
//    }
//
//    if (c == ')') {
//      std::reverse(str.begin(), str.end());
//      period.setNum(str);
//      str.clear();
//      continue;
//    }

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
    integer.setFraction(str);
  }

  if (target == 10) {
    Number converted_integer = convertNumToDecSys(integer);
//    Number converted_pre_period = convertPrePeriodToDecSys(pre_period);
//    Number converted_period = convertPeriodToDecSys(period, int(pre_period.getNum().size()));

    return converted_integer.toString();
  } else if (base == 10) {

  } else {

  }

  return std::string();
}

Number Convertor::convertNumToDecSys(const Number &num) {
  Number converted;
  Number power("1", 10);

  for (unsigned char c : num.getNum()) {
    converted += power * Number(std::to_string(c), 10);
    power *= Number(std::to_string(num.getBase()), 10);
  }

  return converted;
}

Number Convertor::convertPeriodToDecSys(const Number &num, int pre_period_size) {
  if (num.getNum().empty()) return Number();
  return Number();
}
