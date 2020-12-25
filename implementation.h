/**
 * 本文件实现一些小型的工具函数。
 */

#ifndef ARITHMETIC_IMPLEMENTATION_H
#define ARITHMETIC_IMPLEMENTATION_H

#define STRING_LENGTH 200

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "declaration.h"

enum datatype
{                          //Tokenize()返回的结构体中包含的枚举，标记操作模式
    ADD, MINUS, MULTIPLY, DIVIDE, LEFT_PARENTHESES, CLOSING_PARENTHESES, DOUBLE, END,
};

struct token                            //Tokenize()返回的结构体
{
    DataType mode;
    double data;
    _Bool isvalid;
};

/**
 * 致命报错函数。将传入的错误信息打印至屏幕，然后终止程序。
 * @param error_info
 */
void FatalError(const char *error_info)
{
    char string[STRING_LENGTH] = "Fatal error: ";
    puts(strcat(string, error_info));
    exit(1);
}

/**
 * 报错函数。将传入的错误信息打印至屏幕，然后返回至调用处。
 * @param error_info
 */
void Error(const char *error_info)
{
    char string[STRING_LENGTH] = "Error: ";
    puts(strcat(string, error_info));
}

/**
 * 删除字符串中的所有空格和Tab
 * @param const char *str
 * @return char *str
 */
char *DeleteSpace_Tab(char *formula)
{
    char *p = formula, *q = formula;

    while (*p != '\0') {                                 //只要字符串不结束，就持续循环
        if (*p != ' ' && *p != 9 && *p != '\n') {        //注：9是Tab键的ASCII码值
            *q = *p;
            q++;
        }
        p++;
    }
    *q = '\0';

    return formula;
}

/**
 * 从文件中读取算式
 * @param FILE *fp
 * @return char *formula
 */
char *GetFormula(char *file_source, int argc, _Bool mode)
{
    static FILE *fp = NULL;                                     //两个变量定义成static，使其在多次调用中保持值。
    static char string[STRING_LENGTH];

    if (file_source == NULL)                                    //传入文件路径为NULL，则从命令行获取算式
    {
        printf("Input the formula you want to calculate, input \"exit\" to exit the program.\n");
        gets(string);
        if (string[0] == 'e' && strcmp(string, "exit") == 0)    //输入exit则直接退出，采用这样的写法是为了加快非exit情况下的检测速度
            exit(0);
    } else if (mode == 1) {
        if (fp == NULL) {                                        //如果之前没有打开过文件，则执行打开操作
            fp = fopen(file_source, "r");                //使用读模式打开文件
            if (fp == NULL)
                FatalError("Couldn't find file!\n");
        }
        while (1) {
            char *isEOF = fgets(string, STRING_LENGTH, fp);     //从文件读入算式。如果遇到文件尾，fgets返回NULL，用变量iseof接收。
            if (isEOF == NULL) {                                //如果遇到文件尾，直接退出
                if (argc == 2)
                    exit(0);
                return NULL;
            } else if (string[0] == '\n')                       //如果读入空行，则继续读取
                continue;
            else
                break;
        }
        printf("Read\n\t%s from file %s.\n", string, file_source);
    } else if (mode == 0)                                       //关闭文件
        fclose(fp);

    return string;                                              //返回读到的字符串
}

_Bool BalanceParenthesis(const char *formula)
{
    Stack s = CreateStack();
    int i;
    for (i = 0; formula[i] != '\0'; ++i) {
        if (formula[i] == '(')
            Push(LEFT_PARENTHESES, s);
        else if (formula[i] == ')')
            Pop(s);
    }
    if (IsStackEmpty(s))                                        //如果括号不平衡，返回0
        return 1;
    else
        return 0;
}

#endif //ARITHMETIC_IMPLEMENTATION_H
