
#ifndef ARITHMETIC_INFIX_TO_POSTFIX_H
#define ARITHMETIC_INFIX_TO_POSTFIX_H

#include "implementation_adt.h"
#include "implementation.h"
#include "tokenize.h"

_Bool InfixToPostfix(Stack s1, Queue q, const char *string)
{
    Token token;
    Stack s2 = CreateStack();
    Stack s3 = CreateStack();
    _Bool isValid = 1;
    DataType operator;

    for (;;)                            //第一轮循环，将字符串转换成中缀式
    {
        token = Tokenize(string);
        if (token.isvalid == 0){
            isValid = 0;
            return isValid;
        }
        else if (token.mode == END){
            if (Top(s2) != DOUBLE && Top(s2) != RIGHT_PARENTHESES){     //若字符串并非以数字或右括号结尾，则报错
                isValid = 0;
                return isValid;
            }
            break;
        }
        Push(token.mode, s2);
        if (token.mode == DOUBLE){
            Enqueue(token.data, q);
        }
    }
    Tokenize(NULL);

    for (;;)                              //将中缀式转换成后缀式
    {
        if (IsStackEmpty(s2))
            break;
        operator = Top(s2);
        Pop(s2);
        if (operator == DOUBLE)
            Push(DOUBLE, s1);
        else if (operator == ADD)
            Push(ADD, s3);
        else if (operator == MINUS)
            Push(MINUS, s3);
        else if (operator == LEFT_PARENTHESES)
            Push(LEFT_PARENTHESES, s3);
        else if (operator == MULTIPLY){
            while (Top(s3) != ADD && Top(s3) != MINUS){
                Push(Top(s3), s1);
                Pop(s3);
            }
            Push(MULTIPLY, s3);
        }
        else if (operator == DIVIDE){
            while (Top(s3) != ADD && Top(s3) != MINUS){
                Push(Top(s3), s1);
                Pop(s3);
            }
            Push(DIVIDE, s3);
        }
        else if (operator == RIGHT_PARENTHESES){
            while (Top(s3) != LEFT_PARENTHESES){
                Push(Top(s3), s1);
                Pop(s3);
            }
            Pop(s3);                //弹出左小括号
        }
    }
    MakeStackEmpty(s3);
    free(s3);

    return isValid;
}
#endif //ARITHMETIC_INFIX_TO_POSTFIX_H
