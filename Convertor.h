//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#pragma once
#include "Number.h"


class Convertor {
 public:
  static std::string convert(const std::string& num, int base, int target);

 private:
  static bool isGood(const std::string& number, int base);

  static Number convertNumToDecSys(const Number& num);

  static Number convertNumFromDecSystem(const Number& num, int target);
};
