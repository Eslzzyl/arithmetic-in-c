/**
 * 本文件实现Tokenize()函数。
 * 本函数用来从字符串中分割出操作符和操作数。
 */

#ifndef ARITHMETIC_TOKENIZE_H
#define ARITHMETIC_TOKENIZE_H

#include "implementation.h"

Token Tokenize(const char *str)
{
    Token token;                //Token结构体，定义见implementation.h
    token.isvalid = 1;          //默认传入的token是合法的
    static char *p;

    if (str != NULL)            //如果传入的字符串不为NULL，则将其赋给p
        p = (char *)str;

    if (*p == '+'){                             //相加
        p++;
        token.mode = ADD;
    }
    else if (*p == '-'){                        //相减
        p++;
        token.mode = MINUS;
    }
    else if (*p == '*'){                        //相乘
        p++;
        token.mode = MULTIPLY;
    }
    else if (*p == '/'){                        //相除
        p++;
        token.mode = DIVIDE;
    }
    else if (*p == '('){                        //左括号
        p++;
        token.mode = LEFT_PARENTHESES;
    }
    else if (*p == ')'){                        //右括号
        p++;
        token.mode = RIGHT_PARENTHESES;
    }
    else if ((*p >= '0' && *p <= '9') || *p == '.'){  //数字的情况，兼容小数点
        char *q = p;
        _Bool ispointdefined = 0;                   //标记小数点在这个token里是否已经出现
        while ((*p >= '0' && *p <= '9') || *p == '.'){
            if (*p == '.' && ispointdefined == 0)   //如果小数点未出现，改变标记
                ispointdefined = 1;
            else{                                   //如果小数点再次出现，报错
                printf("Error: invalid formula:\n");
                puts(p);
                token.isvalid = 0;                  //token不合法
            }
            *q = *p;                                //将p中的字段分离出来，放到q
            p++;
            q++;
        }
        *(++q) = '\0';                              //将q的下一个字符设为\0，标记q的结束
        token.data = strtod(q, NULL);               //使用库函数strtod()将字符串转换成double
    }
    else{                                           //若前面几种情况均未匹配到，视为未定义的表达式，报错
        printf("Error: invalid formula:\n");
        puts(p);
        token.isvalid = 0;                          //token不合法
    }
    return token;
}

#endif //ARITHMETIC_TOKENIZE_H
