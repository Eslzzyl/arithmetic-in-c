/**
 * 本文件实现Tokenize()函数。
 * 本函数用来从字符串中分割出操作符和操作数。
 */

#ifndef ARITHMETIC_TOKENIZE_H
#define ARITHMETIC_TOKENIZE_H

#include "implementation.h"

void Tokenize(const char *formula, Token *ptr_to_token, unsigned int *position)
{
    ptr_to_token->isvalid = 1;                                  //默认传入的token是合法的

    if (*(formula + *position) == '\0') {
        if (*position == 0) {                                   //如果formula第一个字符就是\0，即为空串
            Error("Empty formula.\n");
            ptr_to_token->isvalid = 0;
            return;
        }
        ptr_to_token->mode = END;
    } else if (*(formula + *position) == '+') {                 //相加
        (*position)++;
        ptr_to_token->mode = ADD;
    } else if (*(formula + *position) == '-') {                 //相减
        (*position)++;
        ptr_to_token->mode = MINUS;
    } else if (*(formula + *position) == '*') {                 //相乘
        (*position)++;
        ptr_to_token->mode = MULTIPLY;
    } else if (*(formula + *position) == '/') {                 //相除
        (*position)++;
        ptr_to_token->mode = DIVIDE;
    } else if (*(formula + *position) == '(') {                 //左括号
        if (*(formula + *position + 1) == '-') {                //如果左括号后紧跟一个负号，表示这是一个负数
            char q[STRING_LENGTH];
            int i = 0;
            _Bool isPointOccured = 0;                           //标记小数点在这个token里是否已经出现
            (*position)++;
            while (*(formula + *position) != ')') {
                if (*(formula + *position) == '.' && isPointOccured == 0)   //如果小数点未出现，改变标记
                    isPointOccured = 1;
                else if (*(formula + *position) == '.' &&
                         isPointOccured == 1) {                 //如果小数点再次出现，报错
                    Error("Invalid formula: repeated decimal point:\n");
                    ptr_to_token->isvalid = 0;                  //token不合法
                    return;
                }
                q[i] = *(formula + *position);                  //将str中的字段分离出来，放到q
                (*position)++;
                i++;
            }
            if (!(*(formula + *position - 1) >= '0' && *(formula + *position - 1) <= '9')) {
                Error("invalid formula: there are other characters in parentheses for negative numbers.\n");
                ptr_to_token->isvalid = 0;
                return;
            }
            (*position)++;
            q[i] = '\0';                                        //将q的下一个字符设为\0，标记q的结束
            ptr_to_token->data = strtod(q, NULL);               //使用库函数strtod()将字符串转换成double
            ptr_to_token->mode = DOUBLE;
        } else {                                                //如果左括号后面的不是负号，则按照正常的小括号处理
            (*position)++;
            ptr_to_token->mode = LEFT_PARENTHESES;
        }
    } else if (*(formula + *position) == ')') {                 //右括号
        (*position)++;
        ptr_to_token->mode = CLOSING_PARENTHESES;
    } else if ((*(formula + *position) >= '0' && *(formula + *position) <= '9')) {  //数字
        char q[STRING_LENGTH];
        int i = 0;
        _Bool isPointOccured = 0;                               //标记小数点在这个token里是否已经出现
        while ((*(formula + *position) >= '0' && *(formula + *position) <= '9') || *(formula + *position) == '.') {
            if (*(formula + *position) == '.' && isPointOccured == 0)   //如果小数点未出现，改变标记
                isPointOccured = 1;
            else if (*(formula + *position) == '.' &&
                     isPointOccured == 1) {                     //如果小数点再次出现，报错
                Error("Invalid formula: repeated decimal point in one token.\n");
                ptr_to_token->isvalid = 0;
                return;
            }
            q[i] = *(formula + *position);                      //将str中的字段分离出来，放到q
            (*position)++;
            i++;
        }
        q[i] = '\0';                                            //将q的下一个字符设为\0，标记q的结束
        ptr_to_token->data = strtod(q, NULL);                   //使用库函数strtod()将字符串转换成double
        ptr_to_token->mode = DOUBLE;
    } else if (*(formula + *position) == 's' && *(formula + *position + 1) == 'i'
               && *(formula + *position + 2) == 'n' && *(formula + *position + 3) == '(') { //sin
        char q[STRING_LENGTH];
        int i = 0, ParenthesesLevel = 0;
        ptr_to_token->mode = DOUBLE;
        (*position) += 4;
        while (1) {
            if (*(formula + *position) == '\0') {
                Error("Invalid formula: the expression does not end with a closing parenthesis.\n");
                ptr_to_token->isvalid = 0;
                return;
            }
            if (*(formula + *position) == '(') {
                ParenthesesLevel++;
            } else if (*(formula + *position) == ')') {
                ParenthesesLevel--;
                if (ParenthesesLevel == -1) {
                    if (*(formula + *position - 1) != ')' && *(formula + *position) < '0' && *(formula + *position) > '9') {
                        Error("Invalid formula: operand formula ends with an invalid token.\n");
                        ptr_to_token->isvalid = 0;
                        return;
                    }
                    (*position)++;
                    break;
                }
            }
            q[i] = *(formula + *position);
            (*position)++;
            i++;
        }
        q[i] = '\0';
        if (Calculate(q, &(ptr_to_token->data)) == 0) {
            ptr_to_token->isvalid = 0;
            return;
        }
        ptr_to_token->data = sin(ptr_to_token->data);
    } else if (*(formula + *position) == 'c' && *(formula + *position + 1) == 'o'
               && *(formula + *position + 2) == 's' && *(formula + *position + 3) == '(') { //cos
        char q[STRING_LENGTH];
        int i = 0, ParenthesesLevel = 0;
        ptr_to_token->mode = DOUBLE;
        (*position) += 4;
        while (1) {
            if (*(formula + *position) == '\0') {
                Error("Invalid formula: the expression does not end with a closing parenthesis.\n");
                ptr_to_token->isvalid = 0;
                return;
            }
            if (*(formula + *position) == '(') {
                ParenthesesLevel++;
            } else if (*(formula + *position) == ')') {
                ParenthesesLevel--;
                if (ParenthesesLevel == -1) {
                    if (*(formula + *position - 1) != ')' && *(formula + *position) < '0'
                        && *(formula + *position) > '9') {
                        Error("Invalid formula: operand formula ends with an invalid token.\n");
                        ptr_to_token->isvalid = 0;
                        return;
                    }
                    (*position)++;
                    break;
                }
            }
            q[i] = *(formula + *position);
            (*position)++;
            i++;
        }
        q[i] = '\0';
        if (Calculate(q, &(ptr_to_token->data)) == 0) {
            ptr_to_token->isvalid = 0;
            return;
        }
        ptr_to_token->data = cos(ptr_to_token->data);
    } else if (*(formula + *position) == 's' && *(formula + *position + 1) == 'q'
               && *(formula + *position + 2) == 'r' && *(formula + *position + 3) == 't'
               && *(formula + *position + 4) == '(') {          //sqrt
        char q[STRING_LENGTH];
        int i = 0, ParenthesesLevel = 0;
        ptr_to_token->mode = DOUBLE;
        (*position) += 5;
        while (1) {
            if (*(formula + *position) == '\0') {
                Error("Invalid formula: the expression does not end with a closing parenthesis.\n");
                ptr_to_token->isvalid = 0;
                return;
            }
            if (*(formula + *position) == '(') {
                ParenthesesLevel++;
            } else if (*(formula + *position) == ')') {
                ParenthesesLevel--;
                if (ParenthesesLevel == -1) {
                    if (*(formula + *position - 1) != ')' && *(formula + *position) < '0' && *(formula + *position) > '9') {
                        Error("Invalid formula: operand formula ends with an invalid token.\n");
                        ptr_to_token->isvalid = 0;
                        return;
                    }
                    (*position)++;
                    break;
                }
            }
            q[i] = *(formula + *position);
            (*position)++;
            i++;
        }
        q[i] = '\0';
        if (Calculate(q, &(ptr_to_token->data)) == 0 || ptr_to_token->data < 0) {   //递归计算
            if (ptr_to_token->data < 0)                         //操作数为负数，报错
                Error("Invalid formula: square root of a negative number.\n");
            ptr_to_token->isvalid = 0;
            return;
        }
        ptr_to_token->data = sqrt(ptr_to_token->data);          //调用库函数进行开平方运算
    } else {                                                    //若前面几种情况均未匹配到，视为未定义的表达式，报错
        Error("Invalid formula: undefined token.\n");
        ptr_to_token->isvalid = 0;
        return;
    }
}

#endif //ARITHMETIC_TOKENIZE_H