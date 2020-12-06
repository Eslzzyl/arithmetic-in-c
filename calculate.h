/**
 * 本文件实现Calculate()函数。
 */

#ifndef ARITHMETIC_CALCULATE_H
#define ARITHMETIC_CALCULATE_H

#include "infix_to_postfix.h"
#include <math.h>

/**
 * 执行计算过程的核心函数
 * @param char *str, double *result
 * @return _Bool isSuccessful
 */
_Bool Calculate(char *str, double *result)          //返回值标记计算是否成功，0为成功，1为失败
{
    double a, b;                                    //计算时的两个操作数
    str = DeleteSpace_Tab(str);                     //去除空格、Tab、换行

    DoubleStack s = CreateDoubleStack();            //栈s，用于计算的暂存
    Queue q = CreateQueue();                        //队列q，用于存储后缀形式的枚举队列
    Doublequeue dq = CreateDoubleQueue();           //队列dq，用于存储运算数据
    if (InfixToPostfix(q, dq, str) == 0)            //isValid为false，返回1，表示运算不合法
        return 1;

    while (!IsQueueEmpty(q))                        //只要q不为空，就持续循环
    {
        if (TailOfQueue(q) == DOUBLE)
            PushDoubleStack(DeDoublequeue(dq), s);  //只要遇到DOUBLE就压入s
        else if (TailOfQueue(q) == ADD){            //加，弹出两个数，将二者相加后压入栈中
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            PushDoubleStack(a + b, s);
        }
        else if (TailOfQueue(q) == MINUS){          //减，弹出两个数，将二者相减后压入栈中
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            PushDoubleStack(b - a, s);
        }
        else if (TailOfQueue(q) == MULTIPLY){       //乘，弹出两个数，将二者相乘后压入栈中
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            PushDoubleStack(a * b, s);
        }
        else if (TailOfQueue(q) == DIVIDE){         //除，弹出两个数，将二者相除后压入栈中
            a = PopDoubleStack(s);
            b = PopDoubleStack(s);
            if (fabs(a - 0) < 1e-10){           //检测除数是否为0
                printf("Error: %lf was divided by zero!\n", b);
                return 1;
            }
            PushDoubleStack(b / a, s);
        }
        Dequeue(q);
    }
    *result = PopDoubleStack(s);    //写入结果
    free(s);                        //释放s的内存
    free(q);                        //释放q的内存
    return 0;
}

#endif //ARITHMETIC_CALCULATE_H
