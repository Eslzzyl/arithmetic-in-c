/**
 * 本文件实现一些小型的工具函数。
 */

#ifndef ARITHMETIC_IMPLEMENTATION_H
#define ARITHMETIC_IMPLEMENTATION_H

#define STRING_LENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum datatype DataType;
typedef struct token Token;

enum datatype{
    ADD, MINUS, MULTIPLY, DIVIDE, LEFT_PARENTHESES, RIGHT_PARENTHESES,
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

void FatalError(const char *);
char *DeleteSpace_Tab(char *);
char *GetFormula(char *, enum readmode);

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
char *GetFormula(char *filesource, enum readmode mode)
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
