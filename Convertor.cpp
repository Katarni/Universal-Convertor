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
    if (c == '-') {
      integer.setMinus(true);
      continue;
    }

    if (c == '.') {
      std::reverse(str.begin(), str.end());
      integer.setInteger(str);
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
//      period.setInteger(str);
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
    std::reverse(str.begin(), str.end());
    integer.setInteger(str);
  } else if (!str.empty() && dot) {
    integer.setFraction(str);
  }

  Number converted_integer, converted_period;

  if (target == 10) {
    converted_integer = convertNumToDecSys(integer);
    converted_period = convertPeriodToDecSys(period, int(integer.getFraction().size()));

  } else if (base == 10) {
    converted_integer = convertNumFromDecSystem(integer);
  } else {

  }

  return converted_integer.toString() + converted_period.toString();
}

Number Convertor::convertNumToDecSys(const Number &num) {
  Number converted;
  Number power("1", 10);

  for (unsigned char c : num.getInteger()) {
    converted += power * Number(std::to_string(c), 10);
    power *= Number(std::to_string(num.getBase()), 10);
  }

  power = Number("1", 10) / num.getBase();

  for (unsigned char c : num.getFraction()) {
    converted += power * Number(std::to_string(c), 10);
    power /= num.getBase();
  }

  return converted;
}

Number Convertor::convertPeriodToDecSys(const Number &num, int pre_period_size) {
  if (num.getInteger().empty()) return Number();
  return Number();
}

Number Convertor::convertNumFromDecSystem(const Number &num) {
  return Number();
}
