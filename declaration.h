/**
 * 声明文件。
 */

#ifndef ARITHMETIC_DECLARATION_H
#define ARITHMETIC_DECLARATION_H

struct stack_node;                        //栈的节点
struct queue_node;
struct stack_double_node;
struct token;                       //字段，用于Tokenize()
enum datatype;                      //字段类型
enum read_mode;                      //读取模式，用于GetFormula()

typedef struct stack_node *PtrToStackNode;
typedef struct stack_double_node *PtrToStackDoubleNode;
typedef PtrToStackDoubleNode DoubleStack;
typedef struct queue_node *PtrToQueueNode;
typedef PtrToStackNode Stack;
typedef PtrToQueueNode Queue;

typedef enum datatype DataType;
typedef struct token Token;

//功能性函数声明
void FatalError(const char *);
char *DeleteSpace_Tab(char *);
char *GetFormula(char *, enum read_mode);
Token Tokenize(const char *);
_Bool InfixToPostfix(Stack, Queue, const char *);
double Calculate(char *);

//枚举堆栈ADT
Stack CreateStack(void);            //创建栈
void MakeStackEmpty(Stack);
void Push(DataType, Stack);             //将数据压入栈中
DataType Top(Stack);                    //返回栈顶元素
void Pop(Stack);                    //弹出栈顶元素
_Bool IsStackEmpty(Stack);            //检查栈是否为空

DoubleStack CreateDoubleStack(void);
void MakeDoubleStackEmpty(DoubleStack);
void PushDoubleStack(double, DoubleStack);
double PopDoubleStack(DoubleStack);
_Bool IsDoubleStackEmpty(DoubleStack);

//队列ADT
Queue CreateQueue(void);            //创建队列
void MakeQueueEmpty(Queue);
void Enqueue(double, Queue);        //入队
double Dequeue(Queue);              //出队
_Bool IsQueueEmpty(Queue);            //检查队列是否为空

#endif //ARITHMETIC_DECLARATION_H