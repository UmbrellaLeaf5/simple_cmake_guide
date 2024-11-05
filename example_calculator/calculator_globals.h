#pragma once

#include "Names.h"
#include "Token.h"

// поток ввода токенов, используемый во всей программе
extern Token_stream ts;

// таблица символов, используемая во всей программе
extern Names nm;

const string input_letter = "> ";  // символ, предлагающий пользователю ввод
const string res_letter =
    "= ";  // символ, показывающий начало вывода результата
