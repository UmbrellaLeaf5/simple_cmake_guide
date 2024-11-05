#include "Token.h"

#include "const_kinds.h"
#include "std_lib_facilities.h"

Token Token_stream::get() {
  // если в буфере есть токен, забираем его оттуда
  if (is_full) {
    is_full = false;
    return buffer;
  }

  char rec_ch = ' ';
  while (cin.get(rec_ch) &&
         isspace(rec_ch)) {  // пропускаем все пробельные символы
    if (rec_ch == line_break)  // конец строки - вывод на экран
      return Token{line_break};
  }
  if (!cin)  // поток, скорее всего, закрыл пользователь
    return Token{exiting};

  switch (rec_ch) {
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case ';':
    case '\n':
    case '=':
    case ',':
    case '#':
    case '$':
      return Token(rec_ch);
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      cin.unget();  // возвращаем предыдущий символ в стандартный поток ввода
      double rec_value;
      cin >> rec_value;
      return Token(number, rec_value);
    }
    // случай для переменных или служебных слов типа 'sqrt', 'exit', 'pow'
    default: {
      if (isalpha(rec_ch)) {
        string user_input;
        user_input += rec_ch;
        // читаем посимвольно слово (из букв и цифр)
        while (cin.get(rec_ch) && (isalpha(rec_ch) || isdigit(rec_ch)))
          user_input += rec_ch;
        cin.unget();
        // если получены служебные слова, организуем соотв. действия в токене
        if (user_input == "exit") return Token(exiting);
        if (user_input == "sqrt") return Token(square_root);
        if (user_input == "pow") return Token(power);
        if (user_input == "help") return Token(help);
        return Token(name,
                     user_input);  // если было получено не служебное слово,
        // то это была переменная
      }
      error("bad token");

      return Token(0);
    }
  }
}

void Token_stream::unget(Token rec_t) {
  buffer = rec_t;
  is_full = true;
}

void Token_stream::ignore(const string& ending_chars) {
  // если символ этот в буфере, то останавливаемся, очищая буфер
  if (is_full && ending_chars.find(buffer.kind) != string::npos) {
    is_full = false;
    return;
  }
  is_full = false;

  char rec_ch;
  while (cin.get(rec_ch)) {
    if (ending_chars.find(rec_ch) != string::npos) return;
  }
}
