/**
 * 本文件实现Calculate()函数。
 */

#ifndef ARITHMETIC_CALCULATE_H
#define ARITHMETIC_CALCULATE_H

#include "implementation_adt.h"
#include "implementation.h"
#include "tokenize.h"

/**
 * 执行计算过程的核心函数
 * @param const char *str
 * @return double result
 */
double Calculate(char *str)
{
    double result;
    Token token;
    str = DeleteSpace_Tab(str);

    Stack stack1 = CreateStack();
    while (1)
    {
        token = Tokenize(str);
        if (token.isvalid == 0){
            result = 0.0;
            break;
        }

        Tokenize(NULL);
    }
    return result;
}
#endif //ARITHMETIC_CALCULATE_H
