#include "Token.h"
#include "calculator_globals.h"
#include "const_kinds.h"
#include "main_grammar_functions.h"
#include "std_lib_facilities.h"

// функция, выводящая инструкцию по работе с программой
void user_help() {
  cout << "Instructions for using the calculator:" << endl;
  cout << "With the enabled operations, this calculator"
          " can calculate lowercase mathematical expressions."
       << endl;
  cout << "Allowed operations in accordance with the axioms of mathematics:"
       << endl;
  cout << "! addition ('+'), subtraction ('-');" << endl;
  cout << "! multiplication ('*'), division ('/'), division remainder ('%');"
       << endl;
  cout << "! exponentiation ('pow(,)'), square root ('sqrt()');" << endl;
  cout << "! declaration of variables ('#'), declaration of constants ('$');"
       << endl;
  cout << "! evaluating the expression in brackets, assigning new values to "
          "variables ('=')."
       << endl;
  cout << "To get the result of a calculation, use the symbol ';' to separate "
          "expressions and "
          "line breaks, or just use line breaks."
       << endl;
  cout << "An example of a working program using all the commands:" << endl;
  cout << "> # s = 10; $ p = 5; 2 + s; s = 5 * p; pow(p, 4); sqrt(s); s % 10; "
          "s / 5;"
          " s / (5 % 10) + 6 - 7; s = 8"
       << endl;
}

// функция, очищающая потока ввода (игнорирование буфера до символа вывода
// результата включительно)
void clean_up_mess() { ts.ignore(";\n"); }

// функция, обрабатывающая вычисления: инструкция, вывод, выход, вычисление
void calculate() {
  cout << input_letter;
  for (;;) {
    try {
      Token rec_t = ts.get();
      while (rec_t.kind == prnt || rec_t.kind == line_break)
        if (rec_t.kind == prnt)
          rec_t = ts.get();
        else if (rec_t.kind == line_break) {
          cout << input_letter;
          rec_t = ts.get();
        }
      if (rec_t.kind == exiting) return;
      if (rec_t.kind == help)
        user_help();
      else {
        ts.unget(rec_t);
        // если нечего выводить на экран, но и не происходит выход из программы,
        // то возвращаем токен в поток ввода и обрабатываем инструкцию, выводя
        // результат
        double res = statement();
        cout << res_letter << res << endl;
      }
    } catch (runtime_error& exc)  // в случае ошибки выводим сообщение и очищаем
                                  // поток токенов, но
    {                             // не завершаем программу
      cerr << exc.what() << endl;
      clean_up_mess();
      cout << input_letter;
    }
  }
}

int main() {
  try {
    // объявляем известные мат. константы
    nm.define_name("pi", 3.1415926535, true);
    nm.define_name("e", 2.7182818284, true);

    calculate();  // вызываем весь основной алгоритм калькулятора
    return 0;
  }
  // все остальные ошибки, не обработанные в процессе выполнения других функций
  catch (exception& exc) {
    cerr << "exception: " << exc.what() << endl;
    return 1;
  } catch (...) {
    cerr << "exception" << endl;
    return 2;
  }
}
