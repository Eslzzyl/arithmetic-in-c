/**
 * 声明文件。
 */

#ifndef ARITHMETIC_DECLARATION_H
#define ARITHMETIC_DECLARATION_H

struct stack_node;                          //枚举栈的节点
struct stack_double_node;                   //double栈的节点
struct queue_node;                          //枚举队列的节点
struct queue_double_node;                   //double队列的节点
struct token;                               //字段，用于Tokenize()
enum datatype;                              //字段类型

typedef struct stack_node *PtrToStackNode;
typedef PtrToStackNode Stack;
typedef struct stack_double_node *PtrToStackDoubleNode;
typedef PtrToStackDoubleNode DoubleStack;
typedef struct queue_node *PtrToQueueNode;
typedef PtrToQueueNode Queue;
typedef struct queue_double_node *PtrToQueueDoubleNode;
typedef PtrToQueueDoubleNode Doublequeue;

typedef enum datatype DataType;
typedef struct token Token;

//功能性函数声明
void FatalError(const char *);                          //致命报错函数，输出传入的字符串后终止进程
void Error(const char *);                               //一般性报错函数，用于算式错误的报错。输出后不终止进程。
char *DeleteSpace_Tab(char *);                          //删除算式中所有的空格和Tab
char *GetFormula(char *, int, _Bool);                   //从文件或命令行读取算式
void Tokenize(const char *, Token *, unsigned int *);   //从算式中分离出token
_Bool InfixToPostfix(Queue, Doublequeue, const char *); //将const char *形式的算式转换成枚举队列表示的后缀式
_Bool Calculate(char *, double *);                      //计算函数
_Bool BalanceParenthesis(const char *);                 //检查算式的括号是否匹配

//枚举堆栈ADT
Stack CreateStack(void);                //创建栈
void MakeStackEmpty(Stack);             //将栈置空
void Push(DataType, Stack);             //将数据压入栈中
DataType Top(Stack);                    //返回栈顶元素
void Pop(Stack);                        //弹出栈顶元素
_Bool IsStackEmpty(Stack);              //检查栈是否为空

//double堆栈ADT
DoubleStack CreateDoubleStack(void);
void MakeDoubleStackEmpty(DoubleStack);
void PushDoubleStack(double, DoubleStack);
double PopDoubleStack(DoubleStack);
_Bool IsDoubleStackEmpty(DoubleStack);

//枚举队列ADT
Queue CreateQueue(void);                //创建队列
void MakeQueueEmpty(Queue);             //将队列置空
void Enqueue(DataType, Queue);          //入队
DataType Dequeue(Queue);                //出队
_Bool IsQueueEmpty(Queue);              //检查队列是否为空
DataType TailOfQueue(Queue);            //返回队列尾部元素
DataType HeadOfQueue(Queue);            //返回队列头部元素

//double队列ADT
Doublequeue CreateDoubleQueue(void);
void MakeDoubleQueueEmpty(Doublequeue);
void EnDoublequeue(double, Doublequeue);
double DeDoublequeue(Doublequeue);
_Bool IsDoubleQueueEmpty(Doublequeue);

#endif //ARITHMETIC_DECLARATION_H