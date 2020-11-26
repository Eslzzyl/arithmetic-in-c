/**
 * 本文件实现堆栈ADT中的各种操作函数。
 */

#ifndef ARITHMETIC_IMPLEMENTATION_STACK_H
#define ARITHMETIC_IMPLEMENTATION_STACK_H

#include "implementation.h"
#include "declaration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 堆栈的节点
 */
struct node
{
    char Element;
    PtrToNode Next;
};

/**
 * 检查传入的堆栈是否为空
 * @param Stack S
 * @return 如果为空，返回1；如果不为空，返回0。
 */
int IsEmpty(Stack S)
{
    return S -> Next == NULL;
}

/**
 * 建立一个堆栈
 * @return Stack S
 */
Stack CreateStack(void)
{
    Stack S;

    S = malloc(sizeof(struct node));
    if (S == NULL)
        FatalError("Out of Space!");
    S -> Next = NULL;
    MakeEmpty(S);
    return S;
}

/**
 * 将一个堆栈置空
 * @param Stack S
 */
void MakeEmpty(Stack S)
{
    if (S == NULL)
        FatalError("Must use CreateStack first");
    else
        while (!IsEmpty(S))
            Pop(S);
}
/**
 * 将一个值(X)压入栈中
 * @param char X
 * @param Stack S
 */
void Push(char X, Stack S)
{
    PtrToNode TmpCell;

    TmpCell = malloc(sizeof(struct node));
    if (TmpCell == NULL)
        FatalError("Out of space!!!");
    else
    {
        TmpCell -> Element = X;
        TmpCell -> Next = S -> Next;
        S -> Next = TmpCell;
    }
}

/**
 * 返回栈顶元素
 * @param Stack S
 * @return char top
 */
char Top(Stack S)
{
    if (!IsEmpty(S))
        return S -> Next -> Element;
    FatalError("Empty Stack!");
    return 0;       //此处的return用于规避编译警告
}

/**
 * 弹出栈顶元素
 * @param Stack S
 */
void Pop(Stack S)
{
    PtrToNode FirstCell;

    if (IsEmpty(S))
        FatalError("Empty Stack!");
    else
    {
        FirstCell = S -> Next;
        S -> Next = S -> Next -> Next;
        free(FirstCell);
    }
}

#endif //ARITHMETIC_IMPLEMENTATION_STACK_H
