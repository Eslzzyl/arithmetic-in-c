/**
 * 项目 arithmetic 入口
 * 执行标准 C99
 * 编译器 GCC 8.1.0 on CLion
 * 参考文献
 * Data Structures and Algorithm Analysis in C 2nd Edition by Mark Allen Weiss
 */

#include "implementation.h"
#include "calculate.h"

int main(int argc, char *argv[])
{
    char string[STRING_LENGTH] = {'\0'};
    char *p = string;
    char *filesource = NULL;
    double result;

    if (argc == 2)
        filesource = argv[1];
    else if (argc > 2)
        FatalError("Invalid arguments!\n");
    while ((p = ReadFile(filesource, READ)) != NULL)
    {
        result = Calculate(p);
        printf("%lf\n\n", result);
    }
    ReadFile(string, CLOSE);

    return 0;
}
