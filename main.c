/**
 * 项目 arithmetic 入口
 * 执行标准 C99
 * 编译器 GCC 8.1.0 on CLion
 * 参考文献
 * Data Structures and Algorithm Analysis in C 2nd Edition by Mark Allen Weiss
 */

#include "implementation_stack.h"
#include "calculate.h"

int main(int argc, char *argv[])
{
    char string[STRING_LENGTH] = {'\0'};
    char *p = string;
    char *filesource = NULL;
    double result;

    if (argc == 2)                                  //argc == 2，表示运行时指定了一个参数，则将其作为文件名赋给filesource
        filesource = argv[1];
    else if (argc > 2)                              //若有不止一个参数，报错
        FatalError("Invalid arguments!\n");
    while ((p = GetFormula(filesource, READ)) != NULL)  //只要GetFormula()返回的字符串不为NULL，就持续循环
    {
        result = Calculate(p);
        printf("The result is %lf\n\n", result);
    }
    GetFormula(string, CLOSE);                      //传入CLOSE枚举参数，关闭GetFormula()中打开的文件

    return 0;
}
