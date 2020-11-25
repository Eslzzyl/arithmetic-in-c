/**
 * 本文件实现Tokenize()函数。
 * 本函数用来从字符串中分割出操作符和操作数。
 */

#ifndef ARITHMETIC_TOKENIZE_H
#define ARITHMETIC_TOKENIZE_H

#include "implementation_stack.h"

Token Tokenize(const char *str)
{
    Token token;
    token.isvalid = 1;
    static char *p;

    if (str != NULL)
        p = (char *)str;

    while (*p != '\0')
    {
        if (*p == '+'){
            p++;
            token.mode = ADD;
        }
        else if (*p == '-'){
            p++;
            token.mode = MINUS;
        }
        else if (*p == '*'){
            p++;
            token.mode = MULTIPLY;
        }
        else if (*p == '/'){
            p++;
            token.mode = DIVIDE;
        }
        else if (*p == '('){
            p++;
            token.mode = LEFT_PARENTHESES;
        }
        else if (*p == ')'){
            p++;
            token.mode = RIGHT_PARENTHESES;
        }
        else if (*p >= '0' && *p <= '9' || *p == '.'){
            char *q = p;
            int ispointdefined = 0;
            while ((*p >= '0' && *p <= '9') || *p == '.'){
                if (*p == '.' && ispointdefined == 0)
                    ispointdefined = 1;
                else{
                    FatalError("Error: invalid formula:\n");
                    puts(p);
                    token.isvalid = 0;
                }
                *q = *p;
                p++;
                q++;
            }
            *(++q) = '\0';
            token.data = strtod(q, NULL);
        }
        else{
            printf("Error: invalid formula:\n");
            puts(p);
            token.isvalid = 0;
            break;
        }
    }

    return token;
}

#endif //ARITHMETIC_TOKENIZE_H
