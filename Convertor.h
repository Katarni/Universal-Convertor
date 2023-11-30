//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#pragma once
#include "Number.h"


class Convertor {
 public:
  static std::string convert(const std::string& num, int base, int target);

  static Number convertNumToDecSys(const Number& num);
  static Number convertPeriodToDecSys(const Number& num, int pre_period_size);

 private:
  static bool isGood(const std::string& number, int base);
};
