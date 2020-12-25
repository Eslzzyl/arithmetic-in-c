/**
 * 本文件实现Calculate()函数。
 */

#ifndef ARITHMETIC_CALCULATE_H
#define ARITHMETIC_CALCULATE_H

#include "infix_to_postfix.h"

/**
 * 执行计算过程的核心函数
 * @param char *str, double *result
 * @return _Bool isSuccessful
 */
_Bool Calculate(char *formula, double *result)                      //返回值标记计算是否成功，1为成功，0为失败
{
    double a, b;                                                    //计算时的两个操作数
    formula = DeleteSpace_Tab(formula);                             //去除空格、Tab、换行

    DoubleStack double_stack = CreateDoubleStack();                 //栈s，用于计算的暂存
    Queue postfix_queue = CreateQueue();                            //队列q，用于存储后缀形式的枚举队列
    Doublequeue double_Queue = CreateDoubleQueue();                 //队列dq，用于存储运算数据
    if (InfixToPostfix(postfix_queue, double_Queue, formula) == 0)  //isValid为false，返回0，表示运算不合法
        return 0;

    while (!IsQueueEmpty(postfix_queue))                            //只要q不为空，就持续循环
    {
        if (TailOfQueue(postfix_queue) == DOUBLE)
            PushDoubleStack(DeDoublequeue(double_Queue), double_stack);  //只要遇到DOUBLE就压入double_stack
        else {
            a = PopDoubleStack(double_stack);                       //依次弹出两个操作数
            b = PopDoubleStack(double_stack);
            if (TailOfQueue(postfix_queue) == ADD)                  //加
                PushDoubleStack(b + a, double_stack);
            else if (TailOfQueue(postfix_queue) == MINUS)           //减
                PushDoubleStack(b - a, double_stack);
            else if (TailOfQueue(postfix_queue) == MULTIPLY)        //乘
                PushDoubleStack(b * a, double_stack);
            else if (TailOfQueue(postfix_queue) == DIVIDE) {        //除
                if (fabs(a) < 1e-6) {
                    Error("Divide by zero!");
                    return 0;
                }
                PushDoubleStack(b / a, double_stack);
            }
        }
        Dequeue(postfix_queue);
    }
    *result = PopDoubleStack(double_stack);         //写入结果
    free(double_stack);
    free(postfix_queue);
    return 1;
}

#endif //ARITHMETIC_CALCULATE_H
