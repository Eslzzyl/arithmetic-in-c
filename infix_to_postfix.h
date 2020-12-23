
#ifndef ARITHMETIC_INFIX_TO_POSTFIX_H
#define ARITHMETIC_INFIX_TO_POSTFIX_H

#include "implementation_adt.h"
#include "implementation.h"
#include "tokenize.h"

_Bool InfixToPostfix(Queue q1, Doublequeue dq, const char *string)
{
    Token token;
    Stack s2 = CreateStack();
    Queue q2 = CreateQueue();           //实现中缀式到后缀式变换的队列
    _Bool isValid = 1;
    DataType operator;

    unsigned int Position = 0;          //标记Tokenize()的执行位置

    for (;;)                            //第一轮循环，将字符串转换成中缀式
    {
        Tokenize(string, &token, &Position);
        if (token.isvalid == 0){
            isValid = 0;
            return isValid;
        }
        else if (token.mode == END){
            Position = 0;
            if (HeadOfQueue(q2) != DOUBLE && HeadOfQueue(q2) != RIGHT_PARENTHESES){     //若字符串并非以数字或右括号开头，则报错
                isValid = 0;
                return isValid;
            }
            break;
        }
        Enqueue(token.mode, q2);
        if (token.mode == DOUBLE){
            EnDoublequeue(token.data, dq);
        }
    }
    Position = 0;

    for (;;)                              //第二轮循环，将中缀式转换成后缀式
    {
        if (IsQueueEmpty(q2))
            break;
        operator = TailOfQueue(q2);
        Dequeue(q2);
        if (operator == DOUBLE)
            Enqueue(DOUBLE, q1);
        else if (operator == ADD){
            if (IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES){
                Push(ADD, s2);
            } else {
                while (!(IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES) && Top(s2) != ADD) {
                    Enqueue(Top(s2), q1);
                    Pop(s2);
                }
                Push(ADD, s2);
            }
        }
        else if (operator == MINUS){
            if (IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES){
                Push(MINUS, s2);
            } else {
                while (!(IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES) && Top(s2) != ADD) {
                    Enqueue(Top(s2), q1);
                    Pop(s2);
                }
                Push(MINUS, s2);
            }
        }
        else if (operator == LEFT_PARENTHESES)
            Push(LEFT_PARENTHESES, s2);
        else if (operator == MULTIPLY){
            if (IsStackEmpty(s2) || Top(s2) == ADD || Top(s2) == MINUS || Top(s2) == LEFT_PARENTHESES)
                Push(MULTIPLY, s2);
            else{
                while (!IsStackEmpty(s2) && (Top(s2) != ADD && Top(s2) != MINUS && Top(s2) != LEFT_PARENTHESES))
                {
                    Enqueue(Top(s2), q1);
                    Pop(s2);
                }
                Push(MULTIPLY, s2);
            }
        }
        else if (operator == DIVIDE){
            if (IsStackEmpty(s2) || Top(s2) == ADD || Top(s2) == MINUS || Top(s2) == LEFT_PARENTHESES)
                Push(DIVIDE, s2);
            else{
                while (!IsStackEmpty(s2) && (Top(s2) != ADD && Top(s2) != MINUS && Top(s2) != LEFT_PARENTHESES))
                {
                    Enqueue(Top(s2), q1);
                    Pop(s2);
                }
                Push(DIVIDE, s2);
            }
        }
        else if (operator == RIGHT_PARENTHESES){
            while (Top(s2) != LEFT_PARENTHESES){
                Enqueue(Top(s2), q1);
                Pop(s2);
            }
            Pop(s2);                //弹出左小括号
        }
    }
    while (!IsStackEmpty(s2)){
        Enqueue(Top(s2), q1);
        Pop(s2);
    }
    free(s2);

    return isValid;
}
#endif //ARITHMETIC_INFIX_TO_POSTFIX_H
