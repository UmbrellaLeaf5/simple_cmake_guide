#pragma once

#include "std_lib_facilities.h"

// структура токена (у него есть тип, значение и (возможно) имя переменной)
struct Token {
  char kind;
  double value;
  string name;

  // использование конструкторов для разных вариантов использования токена
  // (числового значения, ключевого слова, имени переменной и т.п.)
  Token(char rec_ch) : kind(rec_ch), value(0) {}

  Token(char rec_ch, double val) : kind(rec_ch), value(val) {}

  Token(char rec_ch, string n) : kind(rec_ch), value(0), name(n) {}
};

// поток с буфером для чтения токенов
class Token_stream {
 private:
  bool is_full;  // переменная, отвечающая за переполнение потока токенов
  Token buffer;  // "буферный" считываемый токен

 public:
  Token_stream() : is_full(0), buffer(0) {}

  // функция, отвечающая за получение следующего токена из потока
  Token get();
  // функция, отвечающая за возврат токена в поток токенов
  void unget(Token rec_t);

  // функция, отвечающая за игнорирование ввода до появления символа
  // включительно
  void ignore(const string& ending_chars);
};
