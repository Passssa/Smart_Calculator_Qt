/**
 * @file s21_smart_calc.с
 * @author carmanme
 * @brief
 * @version 0.1
 * @date 2023-01-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "s21_smart_calc.h"

/**
 * @brief   проверка символа на математические знаки
 *
 * @param a символ
 * @return  вернет 1, если char равен одному из математических знаков: *^+-/ или
 * m для mod
 */

int s21_math(char a) {
  int res = 0;
  char sign[7] = "*^+-/m";
  for (int i = 0; i != 7; i++) {
    if (sign[i] == a) {
      res = 1;
    }
  }
  return res;
}

/**
 * @brief   проверка символа на то, является ли он цифрой или точкой
 *
 * @param a символ
 * @return  вернет 1, если char - цифра, точка или запятая
 */

int s21_number(char a) {
  int res = 0;
  char number[15] = "0123456789.,";
  for (int i = 0; i != 11; i++) {
    if (number[i] == a) {
      res = 1;
    }
  }
  return res;
}

/**
 * @brief создание стэка
 *
 * @param st поступающий стэк
 */

void s21_create_stack(stack *st) {
  st->num[0] = '\0';
  st->num_count = 0;
  st->operators[0] = '\0';
  st->operator_count = 0;
}

/**
 * @brief достает число из стека
 *
 * @param st поступающий стэк
 * @return вернет символ из стека
 */

double s21_pop_number(stack *st) {
  double res = 0.00;
  if (st->num_count > 0) {
    res = st->num[st->num_count - 1];
    st->num[st->num_count - 1] = '\0';
    st->num_count--;
  }
  return res;
}

/**
 * @brief достает оператор из стека
 *
 * @param st поступающий стэк
 * @return вернет оператор из стека
 */

char s21_pop_operator(stack *st) {
  char res = '0';
  if (st->operator_count > 0) {
    res = st->operators[st->operator_count - 1];
    st->operators[st->operator_count - 1] = '\0';
    st->operator_count--;
  }
  return res;
}

/**
 * @brief кладет число в стек
 *
 * @param st поступающий стэк
 */

void s21_push_number(stack *st, double n) {
  st->num[st->num_count] = n;
  st->num_count++;
  st->num[st->num_count] = '\0';
}

/**
 * @brief кладет оператор в стек
 *
 * @param st поступающий стэк
 */

void s21_push_operator(stack *st, char c) {
  st->operators[st->operator_count] = c;
  st->operator_count++;
  st->operators[st->operator_count] = '\0';
}

/**
 * @brief записывает в стэк результат оператора над числом
 *
 * @param st поступающий стэк
 * @param operation поступающий оператор
 */

void s21_operations(stack *st, char operation) {
  double res = 0.00;
  double op1 = s21_pop_number(st);

  if (s21_is_trigonometry(operation)) {  // trigonometry
    switch (operation) {
      case 'a':
        res = cos(op1);
        break;
      case 'b':
        res = sin(op1);
        break;
      case 'c':
        res = tan(op1);
        break;
      case 'd':
        res = acos(op1);
        break;
      case 'e':
        res = asin(op1);
        break;
      case 'f':
        res = atan(op1);
        break;
      case 'g':
        res = sqrt(op1);
        break;
      case 'j':
        res = log(op1);
        break;
      case 'k':
        res = log10(op1);
        break;
    }
  } else if (s21_math(operation)) {  // simple operations
    double op2 = s21_pop_number(st);
    if (operation == '+') {
      res = op2 + op1;
    } else if (operation == '-') {
      res = op2 - op1;
    } else if (operation == '*') {
      res = op2 * op1;
    } else if (operation == '/') {
      res = op2 / op1;
    } else if (operation == 'm') {
      res = fmod(op2, op1);
    } else if (operation == '^') {
      res = pow(op2, op1);
    }
  }
  s21_push_number(st, res);
}

/**
 * @brief определяет приоритет операции: сначала +-, потом ;/mod, потом ^, потом
 * тригонометрия, потом скобки
 *
 * @param sign математический знак
 * @return вернет приоритет
 */

int s21_priority(char sign) {
  int priority = 0;
  if (sign == '+' || sign == '-') {
    priority = 1;
  } else if (sign == '*' || sign == '/' || sign == 'm') {
    priority = 2;
  } else if (sign == '^') {
    priority = 3;
  } else if (s21_is_trigonometry(sign)) {  // trigonometry func
    priority = 4;
  } else if (sign == '(') {
    priority = 7;
  }
  return priority;
}

/**
 * @brief определяет оператор/знак
 *
 * @param st поступающий стэк
 * @return последний оператор в стэке
 */
char s21_check_operator(stack *st) {
  char res;
  res = st->operators[st->operator_count - 1];
  return res;
}
/**
 * @brief определяет, тригонометрическая ли это функция
 *
 * @param c поступающий символ
 * @return вернет 1, если тригонометрия
 */
int s21_is_trigonometry(char c) {
  int res = 0;
  char signs[13] = "abcdefgjk";
  for (int i = 0; signs[i] != '\0'; i++) {
    if (c == signs[i]) {
      res = 1;
      signs[i + 1] = '\0';
    }
  }
  return res;
}

/**
 * @brief инициализирует тригонометрический опертор
 *
 * @param c поступающий символ
 * @return вернет 1, если тригонометрия
 */

int s21_is_trigonometry_init(char c) {
  int res = 0;
  char signs[7] = "cstal";
  for (int i = 0; signs[i] != '\0'; i++) {
    if (c == signs[i]) {
      res = 1;
      signs[i + 1] = '\0';
    }
  }
  return res;
}

/**
 * @brief Функция преобразования строки в односвязный список
 *
 * @param data поступающая строка для записи
 * @return 0 в случае успеха
 */

void s21_init_parser(char *data) {
  for (int i = 0; data[i] != '\0'; i++) {
    if (s21_is_trigonometry_init(data[i]) || data[i] == 'm') {
      int operator_size = 0;
      if (data[i] == 'a') {  // acos, asin, atan
        operator_size = 3;
        switch (data[i + 1]) {
          case 'c':
            data[i] = 'd';
            break;
          case 's':
            data[i] = 'e';
            break;
          case 't':
            data[i] = 'f';
            break;
        }
      } else if (data[i] == 's') {  // sin, sqrt
        switch (data[i + 1]) {
          case 'i':
            data[i] = 'b';
            operator_size = 2;
            break;
          case 'q':
            data[i] = 'g';
            operator_size = 3;
            break;
        }
      } else if (data[i] == 'l') {  // ln,log
        switch (data[i + 1]) {
          case 'n':
            data[i] = 'j';
            operator_size = 1;
            break;
          case 'o':
            data[i] = 'k';
            operator_size = 2;
            break;
        }
      } else if (data[i] == 'c') {  // cos
        operator_size = 2;
        data[i] = 'a';
      } else if (data[i] == 't') {  // tan
        operator_size = 2;
        data[i] = 'c';
      } else if (data[i] == 'm') {  // mod
        data[i] = 'm';
        operator_size = 2;
      }

      i++;
      for (; operator_size != 0; operator_size--) {
        s21_crop_str(data, i);
      }
      if (data[i] == '-') i++;       // minus
      while (s21_number(data[i])) {  // extra step for num, not a dig
        i++;
      }
    }
  }
}

/**
 * @brief сдвиг строки на определенное число символов (=index)
 *
 * @param str поступающая строка для записи
 * @param index
 */

void s21_crop_str(char *str, int index) {
  for (; str[index] != '\0'; index++) {
    str[index] = str[index + 1];
  }
}

/**
 * @brief определяет, содержится ли унарный минус
 *
 * @param now текущий символ
 * @param prev  предыдущий  символ
 * @param st поступающий текущий стэк
 * @return 1 если минус
 */

int s21_is_unary_minus(char now, char prev, stack *st) {
  int res = 0;
  if (s21_math(now) && s21_math(prev)) {
    res = 1;
  } else if (s21_math(now) && s21_is_trigonometry(prev)) {
    res = 1;
  } else if (s21_math(now) && st->num_count == 0) {
    res = 1;
  } else if (s21_math(now) && prev == '(') {
    res = 1;
  }
  return res;
}

/**
 * @brief определяет, плюс это, минус или другое
 *
 * @param sign поступающий символ
 * @return 1 если +-
 */

int s21_is_minus_or_plus(char sign) {
  int res = 0;
  if (sign == '+' || sign == '-') {
    res = 1;
  }
  return res;
}

/**
 * @brief определение кол-ва символов у операции
 *
 * @param str поступающая строка
 * @return возвращает кол-во символв
 */

int s21_how_many_steps(char *str) {
  int steps = 0;
  char first_letter = *str;
  str++;
  if (first_letter == 's') {
    if (*str == 'i') {
      steps = 3;
    } else if (*str == 'q') {
      steps = 4;
    }
  } else if (first_letter == 'a') {
    steps = 4;

  } else if (first_letter == 'l') {
    if (*str == 'o') {
      steps = 3;
    } else if (*str == 'n') {
      steps = 2;
    }
  } else if (first_letter == 't' || first_letter == 'c') {
    steps = 3;
  }
  return steps;
}

/**
 * @brief проверка на всё всё всё
 *
 * @param data поступающий массив символов
 * @return вернет статус ошибки
 */
int s21_validation(char *data) {
  int error = 0;
  int left_bracket_count = 0;
  int right_bracket_count = 0;
  if (s21_math(data[0]) && !s21_is_minus_or_plus(data[0])) {  // first sign
    error = 1;
  } else {
    int i = 0;
    for (; data[i] != '\0'; data++) {
      if (!s21_number(data[i])) {
        if (data[i] == '(') {
          left_bracket_count += 1;
          if (s21_number(data[i - 1])) {
            error = 1;
          } else if (data[i + 1] == ')') {
            error = 1;
          }
        } else if (data[i] == ')') {
          right_bracket_count += 1;
          if (s21_math(data[i - 1])) {
            error = 1;
          } else if (data[i + 1] != ')') {
            if (!s21_math(data[i + 1])) {
              error = 1;
            } else if (data[i + 1] == 'm') {
              error = 1;
            }
          }
        } else if (data[i] == ' ') {
          error = 1;
        } else if (s21_is_trigonometry_init(data[i])) {
          if (!s21_math(data[i - 1]) && data[i - 1] != '(') {
            error = 1;
          } else {
            int steps = s21_how_many_steps(data);
            while (steps != 0) {
              data++;
              steps--;
            }
            if (data[i] != '(') error = 1;
            data--;
          }
        }
      } else if (data[i] == '.') {
        if (s21_math(data[i + 1]) || data[i + 1] == '.') {
          error = 1;
        }
      }
    }
    if (error == 0) {
      if (left_bracket_count != right_bracket_count) {  // different brackets
        error = 1;
      } else if (s21_math(data[i - 1])) {  // last sign in str
        error = 1;
      }
    }
  }
  return error;
}

/**
 * @brief Основная логика калькулятора
 *
 * @param data поступающий массив символов
 * @return вернет указатель на крайнюю позицию в стэке чисел
 */
double s21_parser(char *data) {
  stack st;
  s21_create_stack(&st);
  stack *p_st = &st;
  s21_init_parser(data);
  int i = 0;
  int minus = 0;
  while (data[i] != '\0') {
    if (s21_number(data[i])) {
      double res = atof(data);
      if (minus == 1) {
        res *= -1;
        minus = 0;
      }
      s21_push_number(p_st, res);
    }
    while (s21_number(data[i])) {
      data++;
    }
    if (s21_is_unary_minus(data[i], data[i - 1], p_st)) {
      if (data[i] == '-') {
        if (s21_is_trigonometry(data[i + 1])) {
          minus = 2;
        } else {
          minus = 1;
        }
      }
      data[i] = 'z';
    }
    if (data[i] != '\0') {
      if (s21_math(data[i]) || s21_is_trigonometry(data[i])) {
        if (p_st->operator_count == 0) {
          s21_push_operator(p_st, data[i]);
        } else {
          int prior1 = s21_priority(data[i]);
          int prior2 = s21_priority(p_st->operators[p_st->operator_count - 1]);
          if (prior1 > prior2 || prior2 == 7) {
            s21_push_operator(p_st, data[i]);
          } else {
            s21_operations(p_st, s21_pop_operator(p_st));
            if (s21_priority(s21_check_operator(p_st)) >=
                s21_priority(data[i])) {
              s21_operations(p_st, s21_pop_operator(p_st));
            }
            if (minus == 2) {
              s21_push_number(p_st, s21_pop_number(p_st) * (-1));
              minus = 0;
            }
            s21_push_operator(p_st, data[i]);
          }
        }
      } else {
        if (data[i] == '(') {
          s21_push_operator(p_st, data[i]);
        } else if (data[i] == ')') {
          while (s21_check_operator(p_st) != '(') {
            s21_operations(p_st, s21_pop_operator(p_st));
          }
          s21_pop_operator(p_st);
        }
      }
    }

    data++;
  }
  while (p_st->operator_count != 0) {
    s21_operations(p_st, s21_pop_operator(p_st));
    if (minus == 2) {
      s21_push_number(p_st, s21_pop_number(p_st) * (-1));
      minus = 0;
    }
  }

  return p_st->num[0];
}
