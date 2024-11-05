#pragma once

#include "std_lib_facilities.h"

// структура, хранящая переменные в памяти (у них есть имя и значение)
struct Variable {
  string name;
  double value;
  bool is_const;

  Variable(string n, double val) : name(n), value(val), is_const(false) {}

  Variable(string n, double val, bool is_constanta)
      : name(n), value(val), is_const(is_constanta) {}
};
