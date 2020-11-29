/**
 * 声明文件。
 */

#ifndef ARITHMETIC_DECLARATION_H
#define ARITHMETIC_DECLARATION_H

struct stack_node;                        //栈的节点
struct stack_double_node;
struct queue_node;
struct queue_double_node;
struct token;                       //字段，用于Tokenize()
enum datatype;                      //字段类型
enum read_mode;                      //读取模式，用于GetFormula()

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
void FatalError(const char *);
char *DeleteSpace_Tab(char *);
char *GetFormula(char *, int, enum read_mode);
Token Tokenize(const char *);
_Bool InfixToPostfix(Queue, Doublequeue, const char *);
double Calculate(char *);

//枚举堆栈ADT
Stack CreateStack(void);            //创建栈
void MakeStackEmpty(Stack);
void Push(DataType, Stack);             //将数据压入栈中
DataType Top(Stack);                    //返回栈顶元素
void Pop(Stack);                    //弹出栈顶元素
_Bool IsStackEmpty(Stack);            //检查栈是否为空

//double堆栈ADT
DoubleStack CreateDoubleStack(void);
void MakeDoubleStackEmpty(DoubleStack);
void PushDoubleStack(double, DoubleStack);
double PopDoubleStack(DoubleStack);
_Bool IsDoubleStackEmpty(DoubleStack);

//枚举队列ADT
Queue CreateQueue(void);            //创建队列
void MakeQueueEmpty(Queue);
void Enqueue(DataType, Queue);        //入队
DataType Dequeue(Queue);              //出队
_Bool IsQueueEmpty(Queue);            //检查队列是否为空
DataType TailOfQueue(Queue);

//double队列ADT
Doublequeue CreateDoubleQueue(void);            //创建队列
void MakeDoubleQueueEmpty(Doublequeue);
void EnDoublequeue(double, Doublequeue);        //入队
double DeDoublequeue(Doublequeue);              //出队
_Bool IsDoubleQueueEmpty(Doublequeue);            //检查队列是否为空
double TailOfDoubleQueue(Doublequeue);

#endif //ARITHMETIC_DECLARATION_H