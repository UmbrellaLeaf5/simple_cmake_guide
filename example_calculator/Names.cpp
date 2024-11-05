#include "Names.h"

#include "Variable.h"
#include "std_lib_facilities.h"

double Names::get_value(const string& prob_name) const {
  for (size_t i = 0; i < names.size(); ++i) {
    if (names[i].name == prob_name) return names[i].value;
  }
  error("get_value: undefined name ",
        prob_name);  // переменной не оказалось в нашем списке
  return 0;
}

double Names::set_value(string rec_name, double rec_value) {
  for (auto& item : names) {
    if (item.name == rec_name) {
      if (!item.is_const) {
        item.value = rec_value;
        return item.value;
      }
      error("set: " + rec_name + " is const");
    }
  }
  error("set: undefined name ",
        rec_name);  // переменной не оказалось в нашем списке

  return 0;
}

bool Names::is_declared(const string& prob_name) const {
  for (size_t i = 0; i < names.size(); ++i) {
    if (names[i].name == prob_name) return true;
  }
  return false;
}

double Names::define_name(string var_name, double value, bool is_const) {
  if (is_declared(var_name))  // проверяем, не существует ли уже переменная с
                              // таким именем
    error(var_name, ": declared twice");
  names.push_back(
      Variable(var_name, value, is_const));  // иначе добавляем её в вектор
  return value;
}
