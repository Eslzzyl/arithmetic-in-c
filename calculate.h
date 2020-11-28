/**
 * 本文件实现Calculate()函数。
 */

#ifndef ARITHMETIC_CALCULATE_H
#define ARITHMETIC_CALCULATE_H

#include "infix_to_postfix.h"

/**
 * 执行计算过程的核心函数
 * @param const char *str
 * @return double result
 */
double Calculate(char *str)
{
    double a, b;
    str = DeleteSpace_Tab(str);

    Stack s1 = CreateStack();
    DoubleStack s2 = CreateDoubleStack();
    Queue q = CreateQueue();
    if (InfixToPostfix(s1, q, str) == 0)         //isValid为false，返回0.0
        return 0.0;

    while (!IsStackEmpty(s1))
    {
        if (Top(s1) == DOUBLE)
            PushDoubleStack(Dequeue(q), s2);
        else if (Top(s1) == ADD){
            a = PopDoubleStack(s2);
            b = PopDoubleStack(s2);
            PushDoubleStack(a + b, s2);
        }
        else if (Top(s1) == MINUS){
            a = PopDoubleStack(s2);
            b = PopDoubleStack(s2);
            PushDoubleStack(a - b, s2);
        }
        else if (Top(s1) == MULTIPLY){
            a = PopDoubleStack(s2);
            b = PopDoubleStack(s2);
            PushDoubleStack(a * b, s2);
        }
        else if (Top(s1) == DIVIDE){
            a = PopDoubleStack(s2);
            b = PopDoubleStack(s2);
            PushDoubleStack(a / b, s2);
        }
        Pop(s1);
    }
    return PopDoubleStack(s2);
}
#endif //ARITHMETIC_CALCULATE_H
