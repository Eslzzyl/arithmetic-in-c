/**
 * 本文件实现ADT中的各种操作函数。
 */

#ifndef ARITHMETIC_IMPLEMENTATION_ADT_H
#define ARITHMETIC_IMPLEMENTATION_ADT_H

#include "implementation.h"
#include "declaration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 堆栈的节点
 */
struct stack_node
{
    char Element;
    PtrToStackNode Next;
};
/**
 * 队列的节点
 */
struct queue_node
{
    double Element;
    PtrToQueueNode Next;
};

/**
 * 建立一个堆栈
 * @return Stack S
 */
Stack CreateStack(void)
{
    Stack S;

    S = malloc(sizeof(struct stack_node));
    if (S == NULL)
        FatalError("Out of Space!");
    S -> Next = NULL;
    MakeStackEmpty(S);
    return S;
}

/**
 * 将一个堆栈置空
 * @param Stack S
 */
void MakeStackEmpty(Stack S)
{
    if (S == NULL)
        FatalError("Must use CreateStack first");
    else
        while (!IsStackEmpty(S))
            Pop(S);
}

/**
 * 将一个值(X)压入栈中
 * @param char X
 * @param Stack S
 */
void Push(char X, Stack S)
{
    PtrToStackNode TmpCell;

    TmpCell = malloc(sizeof(struct stack_node));      //为新节点分配内存
    if (TmpCell == NULL)
        FatalError("Out of space!");
    else
    {
        TmpCell -> Element = X;
        TmpCell -> Next = S -> Next;            //在栈顶压入X，注意栈顶在栈的头部
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
    if (!IsStackEmpty(S))
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
    PtrToStackNode FirstCell;

    if (IsStackEmpty(S))
        FatalError("Empty Stack!");
    else
    {
        FirstCell = S -> Next;
        S -> Next = S -> Next -> Next;
        free(FirstCell);
    }
}

/**
 * 检查传入的堆栈是否为空
 * @param Stack S
 * @return 如果为空，返回1；如果不为空，返回0。
 */
int IsStackEmpty(Stack S)
{
    return S -> Next == NULL;
}


/**
 * 创建一个队列
 * @return Queue
 */
Queue CreateQueue(void)
{
    Queue Q;

    Q = malloc(sizeof(struct stack_node));
    if (Q == NULL)
        FatalError("Out of space!");
    Q -> Next = NULL;
    MakeQueueEmpty(Q);
    return Q;
}

/**
 * 将一个队列置空
 * @param Queue Q
 */
void MakeQueueEmpty(Queue Q)
{
    if (Q == NULL)
        FatalError("Must use CreateStack first");
    else
        while (!IsQueueEmpty(Q))
            Dequeue(Q);
}
/**
 * 将数据加入队列
 * @param double X
 * @param Queue Q
 */
void Enqueue(double X, Queue Q)
{
    PtrToQueueNode TmpCell;
    TmpCell = malloc(sizeof(struct stack_node));
    if (TmpCell == NULL)
        FatalError("Out of space!");
    else
    {
        TmpCell -> Element = X;
        TmpCell -> Next = Q -> Next;            //在栈顶压入X，注意栈顶在栈的头部
        Q -> Next = TmpCell;
    }
}

/**
 * 返回队列尾部元素
 * @param Queue Q
 * @return double Element
 */
double Dequeue(Queue Q)
{
    double Temp;
    while (Q -> Next != NULL)           //一直查找到队列尾部
        Q = Q -> Next;
    Temp = Q -> Element;
    free(Q);
    return Temp;
}

/**
 * 检查传入的队列是否为空
 * @param Queue S
 * @return 如果为空，返回1；如果不为空，返回0。
 */
int IsQueueEmpty(Queue Q)
{
    return Q -> Next == NULL;
}

#endif //ARITHMETIC_IMPLEMENTATION_ADT_H
