/**
 * 本文件实现Calculate()函数。
 */

#ifndef ARITHMETIC_CALCULATE_H
#define ARITHMETIC_CALCULATE_H

#include "infix_to_postfix.h"
#include <math.h>

/**
 * 执行计算过程的核心函数
 * @param const char *str
 * @return double result
 */
_Bool Calculate(char *str, double *result)          //返回值标记计算是否成功，0为成功，1为失败
{
    double a, b;
    str = DeleteSpace_Tab(str);

    DoubleStack s = CreateDoubleStack();
    Queue q = CreateQueue();                         //队列q，用于存储后缀形式的枚举队列
    Doublequeue dq = CreateDoubleQueue();
    if (InfixToPostfix(q, dq, str) == 0)         //isValid为false，返回0.0
        return 1;

    while (!IsQueueEmpty(q))
    {
        if (TailOfQueue(q) == DOUBLE)
            PushDoubleStack(DeDoublequeue(dq), s);
        else if (TailOfQueue(q) == ADD){
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            PushDoubleStack(a + b, s);
        }
        else if (TailOfQueue(q) == MINUS){
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            PushDoubleStack(b - a, s);
        }
        else if (TailOfQueue(q) == MULTIPLY){
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            PushDoubleStack(a * b, s);
        }
        else if (TailOfQueue(q) == DIVIDE){
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            if (fabs(a - 0) < 1e-10){
                printf("Error: %lf was divided by zero!\n", b);
                return 1;
            }
            PushDoubleStack(b / a, s);
        }
        Dequeue(q);
    }
    *result = PopDoubleStack(s);
    return 0;
}
#endif //ARITHMETIC_CALCULATE_H
