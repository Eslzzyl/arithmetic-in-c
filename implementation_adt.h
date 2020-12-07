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
 * 枚举堆栈的节点
 */
struct stack_node
{
    DataType Element;
    PtrToStackNode Next;
};

/**
 * double堆栈的节点
 */
struct stack_double_node
{
    double Element;
    PtrToStackDoubleNode Next;
};

/**
 * 队列的节点
 */
struct queue_node
{
    DataType Element;
    PtrToQueueNode Next;
};

/**
 * double队列的节点
 */
struct queue_double_node
{
    double Element;
    PtrToQueueDoubleNode Next;
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
 * @param DataType X
 * @param Stack S
 */
void Push(DataType X, Stack S)
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
 * @return DataType top
 */
DataType Top(Stack S)
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
_Bool IsStackEmpty(Stack S)
{
    return S -> Next == NULL;
}

DoubleStack CreateDoubleStack(void)
{
    DoubleStack DS;

    DS = malloc(sizeof(struct stack_double_node));
    if (DS == NULL)
        FatalError("Out of space!");
    DS -> Next = NULL;
    MakeDoubleStackEmpty(DS);
    return DS;
}

void MakeDoubleStackEmpty(DoubleStack DS)
{
    if (DS == NULL)
        FatalError("Must use CreateDoubleStack() first!");
    else
        while (!IsDoubleStackEmpty(DS))
            PopDoubleStack(DS);
}

void PushDoubleStack(double X, DoubleStack DS)
{
    PtrToStackDoubleNode TmpCell;
    TmpCell = malloc(sizeof(struct stack_double_node));
    if (TmpCell == NULL)
        FatalError("Out of space!");
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = DS->Next;
        DS->Next = TmpCell;
    }
}

double PopDoubleStack(DoubleStack DS)
{
    PtrToStackDoubleNode FirstCell;
    double X;

    if (IsDoubleStackEmpty(DS))
        FatalError("Empty Stack!");
    else
    {
        X = DS -> Next -> Element;
        FirstCell = DS -> Next;
        DS -> Next = DS -> Next -> Next;
        free(FirstCell);
    }
    return X;
}

_Bool IsDoubleStackEmpty(DoubleStack DS)
{
    return DS -> Next == NULL;
}

/**
 * 创建一个队列
 * @return Queue
 */
Queue CreateQueue(void)
{
    Queue Q;

    Q = malloc(sizeof(struct queue_node));
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
        FatalError("Must use CreateQueue first");
    else
        while (!IsQueueEmpty(Q))
            Dequeue(Q);
}
/**
 * 将数据加入队列
 * @param Datatype X
 * @param Queue Q
 */
void Enqueue(DataType X, Queue Q)       //入队：从头部进入
{
    PtrToQueueNode TmpCell;
    TmpCell = malloc(sizeof(struct queue_node));
    if (TmpCell == NULL)
        FatalError("Out of space!");
    else
    {
        TmpCell -> Element = X;
        TmpCell -> Next = Q -> Next;
        Q -> Next = TmpCell;
    }
}

/**
 * 返回队列尾部元素
 * @param Queue Q
 * @return double Element
 */
DataType Dequeue(Queue Q)               //出队：从尾部离开
{
    PtrToQueueNode LastCell;
    DataType Temp;

    if (IsQueueEmpty(Q))
        FatalError("Empty Queue!");
    else
        while (Q -> Next -> Next != NULL)           //一直查找到队列尾部
            Q = Q -> Next;
    LastCell = Q -> Next;
    Temp = LastCell -> Element;
    free(LastCell);
    Q -> Next = NULL;
    return Temp;
}

/**
 * 检查传入的队列是否为空
 * @param Queue S
 * @return 如果为空，返回1；如果不为空，返回0。
 */
_Bool IsQueueEmpty(Queue Q)
{
    return Q -> Next == NULL;
}

DataType TailOfQueue(Queue Q)
{
    while (Q -> Next != NULL)           //一直查找到队列尾部
        Q = Q -> Next;
    return Q -> Element;
}

DataType HeadOfQueue(Queue Q)
{
    return Q -> Next -> Element;
}

/**
 * 创建一个队列
 * @return Queue
 */
Doublequeue CreateDoubleQueue(void)
{
    Doublequeue DQ;

    DQ = malloc(sizeof(struct queue_double_node));
    if (DQ == NULL)
        FatalError("Out of space!");
    DQ -> Next = NULL;
    MakeDoubleQueueEmpty(DQ);
    return DQ;
}

/**
 * 将一个队列置空
 * @param Queue Q
 */
void MakeDoubleQueueEmpty(Doublequeue DQ)
{
    if (DQ == NULL)
        FatalError("Must use CreateStack first");
    else
        while (!IsDoubleQueueEmpty(DQ))
            DeDoublequeue(DQ);
}
/**
 * 将数据加入队列
 * @param double X
 * @param Queue Q
 */
void EnDoublequeue(double X, Doublequeue DQ)
{
    PtrToQueueDoubleNode TmpCell;
    TmpCell = malloc(sizeof(struct queue_double_node));
    if (TmpCell == NULL)
        FatalError("Out of space!");
    else
    {
        TmpCell -> Element = X;
        TmpCell -> Next = DQ -> Next;
        DQ -> Next = TmpCell;
    }
}

/**
 * 返回队列尾部元素
 * @param Queue Q
 * @return double Element
 */
double DeDoublequeue(Doublequeue DQ)
{
    double Temp;
    PtrToQueueDoubleNode LastCell;

    if (IsDoubleQueueEmpty(DQ))
        FatalError("Empty Doublequeue!");
    else
        while (DQ -> Next -> Next != NULL)           //一直查找到队列尾部
            DQ = DQ -> Next;
    LastCell = DQ -> Next;
    Temp = LastCell -> Element;
    free(LastCell);
    DQ -> Next = NULL;
    return Temp;
}

/**
 * 检查传入的队列是否为空
 * @param Queue S
 * @return 如果为空，返回1；如果不为空，返回0。
 */
_Bool IsDoubleQueueEmpty(Doublequeue DQ)
{
    return DQ -> Next == NULL;
}

double TailOfDoubleQueue(Doublequeue DQ)
{
    while (DQ -> Next != NULL)           //一直查找到队列尾部
        DQ = DQ -> Next;
    return DQ -> Element;
}

#endif //ARITHMETIC_IMPLEMENTATION_ADT_H
