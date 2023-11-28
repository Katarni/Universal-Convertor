//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#pragma once
#include "header.h"

class Convertor {
 public:
  Convertor() = default;

 private:
  static bool isGood(const std::string& str, int base);

  static int toNum(const std::string& str);
  static int toNum(char c);
};
