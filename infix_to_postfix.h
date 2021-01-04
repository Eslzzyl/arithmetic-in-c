
#ifndef ARITHMETIC_INFIX_TO_POSTFIX_H
#define ARITHMETIC_INFIX_TO_POSTFIX_H

#include "implementation_adt.h"
#include "implementation.h"
#include "tokenize.h"

_Bool InfixToPostfix(Queue postfix_queue, Doublequeue double_queue, const char *string)
{
    Token token;
    Stack s2 = CreateStack();                   //实现中缀式到后缀式变换的栈
    Queue q2 = CreateQueue();                   //实现中缀式到后缀式变换的队列
    DataType operator;                          //token类型

    unsigned int position = 0;                  //标记Tokenize()的执行位置

    if (BalanceParenthesis(string) == 0) {      //如果括号不平衡，报错返回
        Error("Invalid formula: Parenthesis is unbalanced.\n");
        return 0;
    }
    while (1) {                                 //第一轮循环，将字符串转换成中缀式
        Tokenize(string, &token, &position);    //取token
        if (token.isvalid == 0) {
            return 0;
        } else if (token.mode == END) {
            position = 0;
            if (HeadOfQueue(q2) != DOUBLE && HeadOfQueue(q2) != CLOSING_PARENTHESES) {     //若字符串并非以数字或右括号开头，则报错
                return 0;
            }
            break;
        }
        Enqueue(token.mode, q2);
        if (token.mode == DOUBLE) {             //如果token是double类型，还要额外在dq中插入double数据
            EnDoublequeue(token.data, double_queue);
        }
    }

    while (1) {                                 //第二轮循环，将中缀式转换成后缀式
        if (IsQueueEmpty(q2))
            break;
        operator = TailOfQueue(q2);             //取token
        Dequeue(q2);
        if (operator == DOUBLE)                 //如果是DOUBLE数据，直接入队
            Enqueue(DOUBLE, postfix_queue);
        else if (operator == ADD) {             //加
            if (IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES) {
                Push(ADD, s2);
            } else {
                while (!(IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES) && Top(s2) != ADD) {
                    Enqueue(Top(s2), postfix_queue);
                    Pop(s2);
                }
                Push(ADD, s2);
            }
        } else if (operator == MINUS) {         //减
            if (IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES) {
                Push(MINUS, s2);
            } else {
                while (!(IsStackEmpty(s2) || Top(s2) == LEFT_PARENTHESES) && Top(s2) != ADD) {
                    Enqueue(Top(s2), postfix_queue);
                    Pop(s2);
                }
                Push(MINUS, s2);
            }
        } else if (operator == LEFT_PARENTHESES)    //左括号
            Push(LEFT_PARENTHESES, s2);
        else if (operator == MULTIPLY) {        //乘
            if (IsStackEmpty(s2) || Top(s2) == ADD || Top(s2) == MINUS || Top(s2) == LEFT_PARENTHESES)
                Push(MULTIPLY, s2);
            else {
                while (!IsStackEmpty(s2) && (Top(s2) != ADD && Top(s2) != MINUS && Top(s2) != LEFT_PARENTHESES)) {
                    Enqueue(Top(s2), postfix_queue);
                    Pop(s2);
                }
                Push(MULTIPLY, s2);
            }
        } else if (operator == DIVIDE) {        //除
            if (IsStackEmpty(s2) || Top(s2) == ADD || Top(s2) == MINUS || Top(s2) == LEFT_PARENTHESES)
                Push(DIVIDE, s2);
            else {
                while (!IsStackEmpty(s2) && (Top(s2) != ADD && Top(s2) != MINUS && Top(s2) != LEFT_PARENTHESES)) {
                    Enqueue(Top(s2), postfix_queue);
                    Pop(s2);
                }
                Push(DIVIDE, s2);
            }
        } else if (operator == CLOSING_PARENTHESES) {   //右括号
            while (Top(s2) != LEFT_PARENTHESES) {
                Enqueue(Top(s2), postfix_queue);
                Pop(s2);
            }
            Pop(s2);                //弹出左小括号
        }
    }
    while (!IsStackEmpty(s2)) {     //将s2的内容全部转入postfix_queue
        Enqueue(Top(s2), postfix_queue);
        Pop(s2);
    }
    free(s2);
    free(q2);

    return 1;
}

#endif //ARITHMETIC_INFIX_TO_POSTFIX_H
