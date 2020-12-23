/**
 * 本文件实现Tokenize()函数。
 * 本函数用来从字符串中分割出操作符和操作数。
 */

#ifndef ARITHMETIC_TOKENIZE_H
#define ARITHMETIC_TOKENIZE_H

#include "implementation.h"

void Tokenize(const char *str, Token *ptr_to_token, unsigned int *Position)
{
    ptr_to_token -> isvalid = 1;          //默认传入的token是合法的

    if (*(str + *Position) == '\0'){
        ptr_to_token -> mode = END;
        return;
    }
    else if (*(str + *Position) == '+'){                             //相加
        (*Position)++;
        ptr_to_token -> mode = ADD;
    }
    else if (*(str + *Position) == '-'){                        //相减
        (*Position)++;
        ptr_to_token -> mode = MINUS;
    }
    else if (*(str + *Position) == '*'){                        //相乘
        (*Position)++;
        ptr_to_token -> mode = MULTIPLY;
    }
    else if (*(str + *Position) == '/'){                        //相除
        (*Position)++;
        ptr_to_token -> mode = DIVIDE;
    }
    else if (*(str + *Position) == '('){                        //左括号
        (*Position)++;
        ptr_to_token -> mode = LEFT_PARENTHESES;
    }
    else if (*(str + *Position) == ')'){                        //右括号
        (*Position)++;
        ptr_to_token -> mode = RIGHT_PARENTHESES;
    }
    else if ((*(str + *Position) >= '0' && *(str + *Position) <= '9') || *(str + *Position) == '.'){  //数字的情况，兼容小数点
        char q[STRING_LENGTH];
        int i = 0;
        _Bool isPointOccured = 0;                   //标记小数点在这个token里是否已经出现
        while ((*(str + *Position) >= '0' && *(str + *Position) <= '9') || *(str + *Position) == '.'){
            if (*(str + *Position) == '.' && isPointOccured == 0)   //如果小数点未出现，改变标记
                isPointOccured = 1;
            else if (*(str + *Position) == '.' && isPointOccured == 1){                                   //如果小数点再次出现，报错
                printf("Error: invalid formula:\n");
                puts(str);
                ptr_to_token -> isvalid = 0;                  //token不合法
            }
            q[i] = *(str + *Position);                                //将str中的字段分离出来，放到q
            (*Position)++;;
            i++;
        }
        q[i] = '\0';                              //将q的下一个字符设为\0，标记q的结束
        ptr_to_token -> data = strtod((char *)q, NULL);               //使用库函数strtod()将字符串转换成double
        ptr_to_token -> mode = DOUBLE;
    }
    else if (*(str + *Position) == 's' && *(str + *Position + 1) == 'i'
            && *(str + *Position + 2) == 'n' && *(str + *Position + 3) == '('){
        char q[STRING_LENGTH];
        int i = 0, ParenthesesLevel = 0;
        ptr_to_token -> mode = DOUBLE;
        (*Position) += 4;
        while (1){
            if (*(str + *Position) == '\0'){
                printf("Error: invalid formula:\n");
                puts(str);
                ptr_to_token -> isvalid = 0;                          //token不合法
            }
            if (*(str + *Position) == '(') {
                ParenthesesLevel++;
            }
            else if (*(str + *Position) == ')') {
                ParenthesesLevel--;
                if (ParenthesesLevel == -1) {
                    (*Position)++;
                    break;
                }
            }
            q[i] = *(str + *Position);
            (*Position)++;
            i++;
        }
        q[i] = '\0';
        if (Calculate(q, &(ptr_to_token -> data)) == 1){
            printf("Error: invalid formula:\n");
            puts(str);
            ptr_to_token -> isvalid = 0;                          //token不合法
        }
        ptr_to_token -> data = sin(ptr_to_token -> data);
    }
    else if (*(str + *Position) == 'c' && *(str + *Position + 1) == 'o'
             && *(str + *Position + 2) == 's' && *(str + *Position + 3) == '('){
        char q[STRING_LENGTH];
        int i = 0, ParenthesesLevel = 0;
        ptr_to_token -> mode = DOUBLE;
        (*Position) += 4;
        while (1){
            if (*(str + *Position) == '\0'){
                printf("Error: invalid formula:\n");
                puts(str);
                ptr_to_token -> isvalid = 0;                          //token不合法
            }
            if (*(str + *Position) == '(') {
                ParenthesesLevel++;
            }
            else if (*(str + *Position) == ')') {
                ParenthesesLevel--;
                if (ParenthesesLevel == -1) {
                    (*Position)++;
                    break;
                }
            }
            q[i] = *(str + *Position);
            (*Position)++;
            i++;
        }
        q[i] = '\0';
        if (Calculate(q, &(ptr_to_token -> data)) == 1){
            printf("Error: invalid formula:\n");
            puts(str);
            ptr_to_token -> isvalid = 0;                          //token不合法
        }
        ptr_to_token -> data = cos(ptr_to_token -> data);
    }
    else if (*(str + *Position) == 's' && *(str + *Position + 1) == 'q'
             && *(str + *Position + 2) == 'r' && *(str + *Position + 3) == 't'
             && *(str + *Position + 4) == '('){
        char q[STRING_LENGTH];
        int i = 0, ParenthesesLevel = 0;
        ptr_to_token -> mode = DOUBLE;
        (*Position) += 5;
        while (1){
            if (*(str + *Position) == '\0'){
                printf("Error: invalid formula:\n");
                puts(str);
                ptr_to_token -> isvalid = 0;                          //token不合法
            }
            if (*(str + *Position) == '(') {
                ParenthesesLevel++;
            }
            else if (*(str + *Position) == ')') {
                ParenthesesLevel--;
                if (ParenthesesLevel == -1) {
                    (*Position)++;
                    break;
                }
            }
            q[i] = *(str + *Position);
            (*Position)++;
            i++;
        }
        q[i] = '\0';
        if (Calculate(q, &(ptr_to_token -> data)) == 1 || ptr_to_token -> data < 0){
            printf("Error: invalid formula:\n");
            puts(str);
            ptr_to_token -> isvalid = 0;                          //token不合法
        }
        ptr_to_token -> data = sqrt(ptr_to_token -> data);
    }
    else{                                           //若前面几种情况均未匹配到，视为未定义的表达式，报错
        printf("Error: invalid formula:\n");
        puts(str);
        ptr_to_token -> isvalid = 0;                          //token不合法
    }
}

#endif //ARITHMETIC_TOKENIZE_H