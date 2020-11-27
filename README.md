# Arithmetic in C

这是本人在合肥工业大学宣城校区 2020级计算机科学与技术专业的C语言课程设计中选定的题目。
原题如下：

>### 实现带有括号的四则运算
>输入是一个带有括号的四则运算表达式，输出是计算得出的正确计算结果。
>例如：输入：123+213-67\*34+345/23\*45\*(34+34-345+245+567)回车，
>然后程序计算得出结果为：359183

程序整体使用C99标准下的C语言

IDE使用CLion 2020.2 on Windows

编译器为GCC 8.1.0

后期可能会在Ubuntu上测试程序

~~GitHub识别有问题，会把所有的头文件识别成C++，其实都是C~~

## 实现思路

本项目首先将输入的中缀表达式(infix)转换成逆波兰(reverse Polish)
表示的后缀表达式(postfix)，之后对后缀表达式求值。
用到的核心数据结构为栈(Stack)和队列(Queue)。

剩余内容待补
