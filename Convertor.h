//
// Created by Timur Akhmetzianov on 28.11.2023.
//

#pragma once
#include "Fraction.h"


class Convertor {
 public:
  static std::string convert(const std::string& num, int base, int target);

 private:
  static bool isGood(const std::string& number, int base);

  static Number convertNumToDecSys(const Number& num);
  static Number convertPeriodToDecSys(const Number& period_num,
                                      const Number& period_den1,
                                      const Number& period_den2);

  static Number convertNumFromDecSystem(const Number& num, int target);
  static Number convertPeriodFromDecSys(const Number& period_num,
                                        int pre_period_size,
                                        int target);
};
