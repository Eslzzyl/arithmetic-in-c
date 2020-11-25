/**
 * 本文件实现项目中的各种函数。
 */

#ifndef ARITHMETIC_IMPLEMENTATION_H
#define ARITHMETIC_IMPLEMENTATION_H

#define STRING_LENGTH 100

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum datatype DataType;
typedef struct token Token;

enum datatype{
    ADD, MINUS, MULTIPLY, DIVIDE, LEFT_PARENTHESES, RIGHT_PARENTHESES
};
enum readmode{
    READ, CLOSE,
};

struct token
{
    DataType mode;
    double data;
    _Bool isvalid;
};

/**
 * 堆栈的节点
 */
struct Node
{
    char Element;
    PtrToNode Next;
};

double Calculate(char *);               //实现见calculate.h
char *DeleteSpace_Tab(char *);
char *ReadFile(char *, enum readmode);
Token Tokenize(const char *);
void FatalError(const char *);


/**
 * 报错函数。将传入的错误信息打印至屏幕，然后终止程序。
 * @param str
 */
void FatalError(const char *str)
{
    puts(str);
    exit(1);
}


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

    S = malloc(sizeof(struct Node));
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

    TmpCell = malloc(sizeof(struct Node));
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

/**
 * 删除字符串中的所有空格和Tab
 * @param const char *str
 * @return char *str
 */
char *DeleteSpace_Tab(char *str)
{
    char *p = str, *q = str;

    while (*p != '\0')                  //删除字符串中的所有空格和Tab
    {
        if (*p != ' ' && *p != 9)       //9: Tab键的ASCII码值
        {
            *q = *p;
            q++;
        }
        p++;
    }
    *q = '\0';

    return str;
}

/**
 * 从文件中读取算式
 * @param FILE *fp
 * @return char *formula
 */
char *ReadFile(char *filesource, enum readmode mode)
{
    static FILE *fp = NULL;
    static char string[STRING_LENGTH];

    if (filesource == NULL)
    {
        printf("Input the formula you want to calculate, input \"exit\" to exit the program.\n");
        gets(string);
        if (strcmp(string, "exit") == 0)
            exit(0);
    }
    else if (mode == READ)
    {
        if (fp == NULL)
        {
            fp = fopen(filesource, "r");
            if (fp == NULL)
                FatalError("Couldn't find file!\n");
        }
        char *isendoffile = fgets(string, STRING_LENGTH, fp);
        if (isendoffile == NULL)
            return NULL;
    }
    else if (mode == CLOSE)
        fclose(fp);


    return string;
}

#endif //ARITHMETIC_IMPLEMENTATION_H
