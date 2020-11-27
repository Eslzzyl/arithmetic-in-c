/**
 * 本文件实现一些小型的工具函数。
 */

#ifndef ARITHMETIC_IMPLEMENTATION_H
#define ARITHMETIC_IMPLEMENTATION_H

#define STRING_LENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declaration.h"

enum datatype{                          //Tokenize()返回的结构体中包含的枚举，标记操作模式
    ADD, MINUS, MULTIPLY, DIVIDE, LEFT_PARENTHESES, RIGHT_PARENTHESES,
};
enum read_mode{                          //GetFormula()的操作模式，也许可以精简？
    READ, CLOSE,
};

struct token                            //Tokenize()返回的结构体
{
    DataType mode;
    double data;
    _Bool isvalid;
};

/**
 * 报错函数。将传入的错误信息打印至屏幕，然后终止程序。
 * @param str
 */
void FatalError(const char *str)
{
    puts(str);
    exit(1);                        //直接结束程序
}
/**
 * 删除字符串中的所有空格和Tab
 * @param const char *str
 * @return char *str
 */
char *DeleteSpace_Tab(char *str)
{
    char *p = str, *q = str;

    while (*p != '\0')                  //只要字符串不结束，就持续循环
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
char *GetFormula(char *fileSource, enum read_mode mode)
{
    static FILE *fp = NULL;                         //两个变量定义成static，使其在多次调用中保持值。
    static char string[STRING_LENGTH];

    if (fileSource == NULL)                         //传入文件路径为NULL，则从控制台获取算式
    {
        printf("Input the formula you want to calculate, input \"exit\" to exit the program.\n");
        gets(string);
        if (strcmp(string, "exit") == 0)            //输入exit则直接退出
            exit(0);
    }
    else if (mode == READ)
    {
        if (fp == NULL)                             //如果之前没有打开过文件，则执行打开操作
        {
            fp = fopen(fileSource, "r");     //使用读模式打开文件
            if (fp == NULL)
                FatalError("Couldn't find file!\n");
        }
        char *iseof = fgets(string, STRING_LENGTH, fp); //从文件读入算式。如果遇到文件尾，fgets()返回NULL，用变量iseof接收。
        if (iseof == NULL)
            return NULL;
    }
    else if (mode == CLOSE)                         //关闭文件
        fclose(fp);

    return string;                                  //返回读到的字符串
}

#endif //ARITHMETIC_IMPLEMENTATION_H
