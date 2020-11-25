/**
 * 堆栈ADT声明文件。
 */

//头文件防重入功能
#ifndef ARITHMETIC_STACK_H
#define ARITHMETIC_STACK_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

//堆栈ADT
int IsEmpty(Stack S);
Stack CreateStack(void);
void MakeEmpty(Stack S);
void Push(char X, Stack S);
char Top(Stack S);
void Pop(Stack S);

#endif //ARITHMETIC_STACK_H
