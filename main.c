/**
 * 项目 arithmetic 入口
 * 执行标准 C99
 * 编译器 GCC 8.1.0
 * 参考文献
 * Data Structures and Algorithm Analysis in C 2nd Edition by Mark Allen Weiss
 */

#include "implementation.h"
#include "calculate.h"

int main(int argc, char *argv[])                    //接收命令行参数
{
    char *formula;                                  //char *formula:用于存放从GetFormula()读入的算式
    char *file_source = NULL;                       //用于存放命令行参数，设初值为NULL以防未指定参数的情况
    double result;                                  //存放计算结果

    if (argc == 2)                                  //argc == 2，表示运行时指定了一个命令行参数，则将其作为文件名赋给fileSource
        file_source = argv[1];
    else if (argc > 2)                              //若有不止一个参数，报错
        FatalError("Too many arguments!\n");
    while ((formula = GetFormula(file_source, argc, 1)) != NULL)  //只要GetFormula()返回的字符串不为NULL，就持续循环
    {
        if (Calculate(formula, &result) == 0)
            continue;
        else
            printf("The result is %lf\n\n", result);
    }
    GetFormula(formula, argc, 0);               //传入0，关闭GetFormula()中打开的文件

    return 0;
}