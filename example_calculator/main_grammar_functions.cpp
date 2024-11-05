#include "main_grammar_functions.h"

#include <cmath>

#include "Token.h"
#include "calculator_globals.h"
#include "const_kinds.h"
#include "std_lib_facilities.h"

double assign_var(string name) {
  Token rec_t_2 = ts.get();  // вспомогательный токен для получения значения
                             // после левой части
  if (rec_t_2.kind == '=') {
    double var_value = expression();
    return nm.set_value(name, var_value);
  }

  ts.unget(rec_t_2);  // возвращаем вспомогательный токен в поток
  return nm.get_value(name);
}

double eval_sqrt() {
  Token rec_t = ts.get();

  if (rec_t.kind != '(') {
    ts.unget(rec_t);
    error("'(' expected");
  }

  double arg = expression();
  rec_t = ts.get();
  if (rec_t.kind != ')') {
    ts.unget(rec_t);
    error("'(' expected");
  }

  if (arg < 0)  // проверка на то, что берем корень неотрицательного числа
    error("square root of a negative number");

  return sqrt(arg);
}

double eval_power() {
  Token rec_t = ts.get();
  if (rec_t.kind != '(') {
    ts.unget(rec_t);
    error("'(' expected");
  }

  double base_number = expression();
  rec_t = ts.get();
  if (rec_t.kind != comma) {  // за первым аргументом должна следовать запятая
    ts.unget(rec_t);
    error("',' expected");
  }

  double power_number =
      expression();  // "сужение" значения с потерей информации и
                     // генерацией исключения в противном случае
  rec_t = ts.get();
  if (rec_t.kind != ')') {
    ts.unget(rec_t);
    error("')' expected");
  }

  try {
    return pow(base_number, narrow_cast<int>(power_number));
  } catch (runtime_error&)  // expect from narrow casting
  {
    error("power must be an integer");
  }

  return 0;
}

char close_bracket(char open_bracket) {
  switch (open_bracket) {
    case '(':
      return ')';
    case '{':
      return '}';
  }
  error("Oops, unreachable code point");

  return 0;
}

double primary() {
  Token rec_t = ts.get();
  switch (rec_t.kind) {
    case '(':
    case '{': {
      char b = close_bracket(rec_t.kind);
      double rec_expr = expression();
      rec_t = ts.get();
      if (rec_t.kind != b) {
        ts.unget(rec_t);
        error(to_string(b) + " expected");
      }
      return rec_expr;
    }
    // предусмотренный случай для отрицательного первичного выражения
    case '-':
      return -primary();
    // предусмотренный случай, если пользователь решит начать первич. выраж. с
    // плюса
    case '+':
      return primary();
    case number:
      return rec_t.value;
    case name:
      return assign_var(rec_t.name);
    case square_root:
      return eval_sqrt();
    case power:
      return eval_power();
    // не получили, чего хотели
    default: {
      ts.unget(rec_t);
      error("primary expected");
    }
  }

  return 0;
}

double term() {
  double left_part = primary();
  for (;;) {
    Token rec_t = ts.get();
    switch (rec_t.kind) {
      case '*': {
        left_part *= primary();
        break;
      }
      case '/': {
        double right_part = primary();
        if (right_part == 0) {
          ts.unget(rec_t);
          error("/: divide by zero");
        }
        left_part /= right_part;
        break;
      }
      case '%': {
        double right_part = primary();
        if (right_part == 0) {
          ts.unget(rec_t);
          error("%: divided by zero");
        }
        left_part =
            fmod(left_part, right_part);  // функция из cmath, вычисляющая
                                          // остаток с плавающей запятой
        break;
      }
      default: {
        ts.unget(rec_t);
        return left_part;
      }
    }
  }
}

double expression() {
  double left_part = term();

  for (;;) {
    Token rec_t = ts.get();
    switch (rec_t.kind) {
      case '+':
        left_part += term();
        break;
      case '-':
        left_part -= term();
        break;
      // выражение закончилось
      default:
        ts.unget(rec_t);  // возвращаем токен в поток
        return left_part;
    }
  }
}

double declaration(bool is_const) {
  Token rec_t = ts.get();
  if (rec_t.kind != name) {  // полученное при вводе не соотв. заданным правилам
                             // для имени переменной
    ts.unget(rec_t);
    error("name expected in declaration");
  }
  string var_name = rec_t.name;
  Token rec_t_2 = ts.get();  // используем второй токен, чтобы проверить
                             // присваивание значения для переменной
  if (rec_t_2.kind != '=') {
    ts.unget(rec_t_2);
    error("=: missing in declaration of ", var_name);
  }
  double var_value = expression();  // получаем значение переменной - выражение
  nm.define_name(var_name, var_value, is_const);
  return var_value;
}

double statement() {
  Token rec_t = ts.get();
  switch (rec_t.kind) {
    case let:
      return declaration(false);
    case cnst:
      return declaration(true);
    default:
      ts.unget(rec_t);
      return expression();
  }
}
