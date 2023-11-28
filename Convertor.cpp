//
// Created by Тимур Ахметзянов on 28.11.2023.
//

#include "Convertor.h"

bool Convertor::isGood(const std::string &str, int base) {
  std::string let;
  bool bracket = false;
  for (char c : str) {
    if (c == '[') {
      bracket = true;
      continue;
    }
    if (c == ']') {
      bracket = false;
      int num = toNum(let);
      let.clear();
      if (num >= base) {
        return false;
      }
      continue;
    }

    if (bracket) {
      let.push_back(c);
    } else if (toNum(c) >= base) {
      return false;
    }
  }

  return true;
}

int Convertor::toNum(const std::string& str) {
  int n = 0;
  for (char c : str) {
    n = n * 10 + c - '0';
  }
  return n;
}

int Convertor::toNum(char c) {
  if (c <= '9') {
    return c - '0';
  }

  return c - 'A' + 10;
}
