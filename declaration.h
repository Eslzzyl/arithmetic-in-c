/**
 * 声明文件。
 */

#ifndef ARITHMETIC_DECLARATION_H
#define ARITHMETIC_DECLARATION_H

struct node;
struct token;
enum datatype;
enum readmode;

typedef struct node *PtrToNode;
typedef PtrToNode Stack;

typedef enum datatype DataType;
typedef struct token Token;

//功能性函数声明
void FatalError(const char *);
char *DeleteSpace_Tab(char *);
char *GetFormula(char *, enum readmode);
Token Tokenize(const char *str);
double Calculate(char *str);

//堆栈ADT
int IsEmpty(Stack S);
Stack CreateStack(void);
void MakeEmpty(Stack S);
void Push(char X, Stack S);
char Top(Stack S);
void Pop(Stack S);

#endif //ARITHMETIC_DECLARATION_H
