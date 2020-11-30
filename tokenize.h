/**
 * 本文件实现Tokenize()函数。
 * 本函数用来从字符串中分割出操作符和操作数。
 */

#ifndef ARITHMETIC_TOKENIZE_H
#define ARITHMETIC_TOKENIZE_H

#include "implementation.h"

void Tokenize(const char *str, Token *ptr_to_token)
{
    ptr_to_token -> isvalid = 1;          //默认传入的token是合法的
    static char *p;

    if (str != NULL && p == NULL)            //如果传入的字符串不为NULL且p为NULL，表示这是一个新的字符串，将其赋给p
        p = (char *)str;
    else if (str == NULL && p != NULL){                    //如果传入NULL，表示分解完毕，将p设为NULL等待下一次分解
        p = NULL;
        return;
    }

    if (*p == '\0'){
        ptr_to_token -> mode = END;
        return;
    }
    else if (*p == '+'){                             //相加
        p++;
        ptr_to_token -> mode = ADD;
    }
    else if (*p == '-'){                        //相减
        p++;
        ptr_to_token -> mode = MINUS;
    }
    else if (*p == '*'){                        //相乘
        p++;
        ptr_to_token -> mode = MULTIPLY;
    }
    else if (*p == '/'){                        //相除
        p++;
        ptr_to_token -> mode = DIVIDE;
    }
    else if (*p == '('){                        //左括号
        p++;
        ptr_to_token -> mode = LEFT_PARENTHESES;
    }
    else if (*p == ')'){                        //右括号
        p++;
        ptr_to_token -> mode = RIGHT_PARENTHESES;
    }
    else if ((*p >= '0' && *p <= '9') || *p == '.'){  //数字的情况，兼容小数点
        char q[STRING_LENGTH], k[STRING_LENGTH];
        int i = 0;
        _Bool isPointOccured = 0;                   //标记小数点在这个token里是否已经出现
        while ((*p >= '0' && *p <= '9') || *p == '.'){
            if (*p == '.' && isPointOccured == 0)   //如果小数点未出现，改变标记
                isPointOccured = 1;
            else if (*p == '.' && isPointOccured == 1){                                   //如果小数点再次出现，报错
                printf("Error: invalid formula:\n");
                puts(str);
                ptr_to_token -> isvalid = 0;                  //token不合法
            }
            q[i] = *p;                                //将p中的字段分离出来，放到q
            p++;
            i++;
        }
        q[i] = '\0';                              //将q的下一个字符设为\0，标记q的结束
        ptr_to_token -> data = strtod((char *)q, NULL);               //使用库函数strtod()将字符串转换成double
        ptr_to_token -> mode = DOUBLE;
    }
    else{                                           //若前面几种情况均未匹配到，视为未定义的表达式，报错
        printf("Error: invalid formula:\n");
        puts(str);
        ptr_to_token -> isvalid = 0;                          //token不合法
    }
}

#endif //ARITHMETIC_TOKENIZE_H
