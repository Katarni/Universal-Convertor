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

  Number integer, period, period_den1, period_den2;
  integer.setBase(base);
  period.setBase(base);

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

    if (c == '(') {
      integer.setFraction(str);
      str.clear();
      continue;
    }

    if (c == ')') {
      std::reverse(str.begin(), str.end());
      period.setInteger(str);
      period_den1 = Number::binaryPow(Number(std::to_string(base), 10), (int)str.size())--;
      period_den2 = Number::binaryPow(Number(std::to_string(base), 10), (int)integer.getFraction().size());
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
    integer.setInteger(str);
  } else if (!str.empty() && dot) {
    integer.setFraction(str);
  }

  Number converted_integer, converted_period;

  if (target == 10) {
    converted_integer = convertNumToDecSys(integer);
  } else if (base == 10) {
    converted_integer = convertNumFromDecSystem(integer, target);
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

Number Convertor::convertNumFromDecSystem(const Number &num, int target) {
  std::vector<unsigned char> converted_int;
  Number integer(num.getInteger(), std::vector<unsigned char>(0), 10);

  while (integer != Number("0", 10)) {
    converted_int.push_back(integer % target);
    integer /= target;
    integer.setFraction(std::vector<unsigned char>(0));
  }

  if (converted_int.empty()) {
    converted_int.push_back(0);
  }

  Number converted(converted_int, std::vector<unsigned char>(0), 10);

  std::vector<unsigned char> converted_fract;
  Number fract(std::vector<unsigned char>(0), num.getFraction(), 10);
  std::set<std::pair<std::string, int>> fract_find_period;

  int i = 0, period_start = -1;
  while (fract != Number(std::vector<unsigned char>(0), std::vector<unsigned char>(0), 10)) {
    fract *= Number(std::to_string(target), 10);
    converted_fract.push_back(fract.getInteger()[0]);
    fract.setInteger(std::vector<unsigned char>(0));
    std::string str;
    for (unsigned char c : fract.getFraction()) {
      str += Number::toLet(c);
    }
    auto it = fract_find_period.lower_bound({str, 0});
    if (it != fract_find_period.end() && it->first == str) {
      period_start = it->second + 1;
      break;
    }
    fract_find_period.insert({str, i});
  }

  if (period_start != -1) {
    converted.setFraction(std::vector<unsigned char>(converted_fract.begin(),
                                                     converted_fract.begin() + period_start));
    converted.setPeriod(std::vector<unsigned char>(converted_fract.begin() + period_start,
                                                   converted_fract.end()));
  } else {
    converted.setFraction(converted_fract);
  }

  return converted;
}
