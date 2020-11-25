
#ifndef ARITHMETIC_CALCULATE_H
#define ARITHMETIC_CALCULATE_H

#include "implementation_stack.h"
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

    token = Tokenize(str);
    while (1)
    {
        if (token.isvalid == 0){
            result = 0.0;
            break;
        }

        token = Tokenize(NULL);
    }
    return result;
}
#endif //ARITHMETIC_CALCULATE_H
