/************************************************************************
 * 数据结构代码总结：
 * 第二章>队列和栈>栈的操作汇总
 * 最后更改:
 *     2020/7/8
 * 说明：                                                               
 * 
========================================================================*/

/*栈的数据结构定义*/
/*顺序栈的数据结构定义：*/
typedef struct SqStack
{
    int top;
    Elemtype data[MaxSize];
}SqStack;

/*初始化一个空顺序栈*/
void InitSqStack(SqStack &L)
{
    L.top = -1;
}

/*判断栈空*/
int IsSqStackEmpty(SqStack L)
{
    if(L.top = -1)
        return 1;
    else
        return 0;
}
/*入栈操作*/
bool Push(SqStack &L, Elemtype e)
{
    if(L.top == MaxSize - 1)
        return false;
    ++(L.top);
    L.data[L.top] = e;
    return true;
}

/*出栈操作,并把数据返回到e*/
bool Pop(SqStack &L, Elemtype &e)
{
    if(L.top == -1)
        return false;
    e = L.data[L.top];
    --(L.top);
    return true;
}

/*中缀表达式转后缀表达式*/
void InfixToPostfix(char infix[], char s2[], int &top2)
{
    char s1[maxSize];
    int top1 = -1;
    int i = 0;

    while (infix[i] != '\0'){
        
        /*若是表达式则直接写*/
        if('0' <= infix[i] && infix <= '9'){
            s2[++top2] = infix[i];
            ++i;
        }

        /*若是括号则进入辅助栈s1*/
        else if (infix[i] == '('){
            s1[++top1] = '(';
            ++i;
        }

        /*若是运算符则判断：当辅助栈为空时直接入栈；
                           当辅助栈栈顶元素为（时直接入栈
                           当辅助栈栈顶符号的优先级小于该符号时，直接入栈
                           当该符号优先级小于等于辅助栈顶符号时，栈顶符号出栈，
                           该符号继续与辅助栈下一个元素比较*/
        else if (infix[i] == '+' || infix[i] == '-' || 
                infix[i] == '*' || infix[i] == '/'){
                 if(top1 = -1 || s1[top1] == '(' ||
                 getPriority(infix[i] > getPriority(s1[top1]) ){
                 s1[++top1] = infix[i];
                 ++i;
               }
            else 
                s2[++top2] = s1[top1--];
            }
        
        /*当遇到）时，辅助栈中一直出栈到下一个（*/
        else if (infix[i] == ')'){
            while (s1[top1 != '('){
                s2[++top2] = s1[top1--];
            }
            --top1;
            ++i;
        }
    }

    /*若辅助栈里还有剩余符号，依次写出*/
    while(top1 != -1){
        s2[++top2] = s1[top1--];
    }
}

/*再用结构体栈写一个中缀转前缀：*/
/*
****
*/

/*前转后*/
/*
****
*/

/*后转前*/
/*
****
*/



/*中缀表达式求值*/
int getPriority(char op)
{
    if ( op == '+' || op == '-')
        return 0;
    else
    {
        return 1;
    }
}

int calSub(float opand1, char op, float opand2, float &result)
{
    if (op == '+')
        result = opand1 + opand2;
    if (op == '-')
        result = opand1 - opand2;
    if (op == '*')
        result = opand1 * opand2;
    if (op == '/'){
        if (fabs(opand2 < MIN))
            return 0;
        else
        {
            result = opand1 / opand2;
        }  
    }
    return 1;    
}

float calInfix(char exp[])
{
    float s1[maxSize];
    int top1 = -1;
    char s2[maxSize];
    int top2 = -1;
    int i = 0;
    while ( exp[i] != '\0')
    {
        if (exp[i] >= '0' && exp[i] <= '9')
        {
             s1[++top1] = exp[i] - '0';
             ++i;
        }

        else if (exp[i] == '(')
        {
             s2[++top2] = '(';
             ++i;
        }
        else if (exp[i] == '+' || exp[i] == '-' ||
                 exp[i] == '*' || exp[i] == '/')
                 {
                    if (top2 == -1 || s2[top2] == "(" ||
                         getPriority(exp[i]) > getPriority(s2[top2]))
                         {
                             s2[++top2] == exp[i];
                             ++i;
                         }
                    
                    else
                    {
                        float opnd1, opnd2, result;
                        char op;
                        int flag;

                        opnd2 = s1[top1--];
                        opnd1 = s2[top2--];
                        op = s2[top2--];

                        flag = calSub(opnd1, op, opnd2, result);
                        if ( flag == 0){
                            cout<<"ERROR"<<endl;
                            break;
                        }
                        s1[++top1] = result;
                    }
                }
        else if (exp[i] == ')')
        {
            while (s2[top2] != '(')
            {
                float opnd1, opnd2, result;
                char op;
                int flag;
                opnd2 = s1[top1--];
                opnd1 = s1[top1--];
                op = s2[top2--];

                flag = calSub(opnd1, op, opnd2, result);
                if ( flag == 0){
                    cout<<"ERROR"<<endl;
                    break;
                }
                s1[++top1] = result;
            }
        --top2;
        ++i;
        }
    }
    while (top2 != -1)
    {
        float opnd1, opnd2, result;
                char op;
                int flag;
                opnd2 = s1[top1--];
                opnd1 = s1[top1--];
                op = s2[top2--];

                flag = calSub(opnd1, op, opnd2, result);
                if ( flag == 0){
                    cout<<"ERROR"<<endl;
                    break;
                }
                s1[++top1] = result;
    }
    return s1[top1];
}


//----------------------------------------------------------------------------
/*链式栈的数据结构定义及基本操作*/
typedef struct StackNode
{
    Elemtype data;
    struct StackNode *next;
}StackNode;

/*初始化一个空链栈*/
void InitLinkStack(StackNode *&S)
{
    S = (StackLNode*)malloc(sizeof(StackLNode));
    S->next = NULL;
}

/*判空*/
bool ISLinkStackEmpty(StackNode *S)
{
    if(S->next == NULL)
        return true;
    else 
        return false;
}

/*入栈*/
bool Push(StackNode *S, Elemtype e)
{
    
    StackNode *p;
    p = (StackNode*)malloc(sizeof(StackNode));
    p->data = e;
    p->next = S->next;
    S->next = p;
    return true;
}

/*出栈*/
bool Pop(StackNode *S, Elemtype &e)
{
    if (S->next == NULL)
         return false;
    StackNode *p;
    p = S->next;
    e = p->data;
    S->next = p->next;
    free(p);
    return true;
}

/*--------------------------用栈迭代计算--------------------------------*/
int calF(int m)
{
    int cum = 1;    /*用来暂存中间量*/
    int s[maxSize];
    int top = -1;   /*构造一个顺序栈, top为栈顶指针*/
    while (m != 0)
    {
        s[++top] = m;
        m /= 3;
        /*将每次的m入栈，直到m降为0为止*/
    }
    while (top != -1){
        /*将每一个m出栈相乘*/
        cum *= s[top--];
    }
    return cum;
}

/*----------------------------用堆栈的括号匹配--------------------------*/
/*判断左右括号匹配函数*/
bool isMatched(char left, chat right)
{
    if (left == '(' && right == ')')
        return true;
    else if (left == '[' && right == ']')
        return true;
    else if (left == '{' && right == '}')
        return true;
    else 
        return false;
}
/*判断括号串是否匹配函数*/
bool isBalanced(char exp[])
{
    char s[maxSize]; 
    int top = -1;   /*构造一个栈*/

    /*开始遍历整个括号串*/
    for (int i = 0; exp[i] != '\0'; ++i){
        
        /*遇到三种左括号，直接入栈*/
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
        {
            s[++top] = exp[i];
        }

        /*当遇到三种右括号时*/
        if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
        {   
            /*若栈为空，不匹配*/
            if (top == -1)
            {
                return false;
            }

            /*若栈不为空，弹出栈顶的括号，验证是否匹配*/
            char left = s[top--];
            if (isBalanced(left, exp[i]) == 0)
            {
                return true;
            }   
        } 
    }

    /*遍历完整个括号串，如果栈中还有未被中和的括号，不匹配*/
    if (top > -1)
        return false;
    
    /*匹配完成*/
    return true;
}

/*---------------------------------------------------------------------*/

/*队列及其相关操作*/
//1.顺序队列：-------------------------------------------------------------------
typedef struct SqQueue
{
    Elemtype data[MaxSize];
    int front, rear;
}SqQueue;

void InitQueue(SqQueue &Q)
{
    /*初始时，队头指针和队尾指针都指向0*/
    Q.rear = Q.front = 0;
}

bool IsQueueEmpty(SqQueue Q)
{
    /*当队头指针等于队尾指针时为空*/
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

bool IsQueueFull(SqQueue Q)
{
    /*当队尾指针下一个位置是队头时为满*/
    if ((Q.rear + 1) % MaxSize == Q.front)
        return true;
    else
        return false;
}

bool EnterQueue(SqQueue &Q, Elemtype x)
{
    /*入队前先判断队是否满*/
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    /*先赋值后移动尾指针*/
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

bool DeleteQueue(SqQueue &Q, Elemtype &x)
{
    /*出队前先判断队是否空*/
    if (Q.rear == Q.front)
        return false;
    /*先出值后移动头指针*/
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

//2.链式队列-----------------------------------------------------------------
typedef struct LQueueNode
{
    /*链式队列结点的数据结构(单链表结点)*/
    Elemtype data;
    struct LQueueNode *next;
}LQueueNode;
typedef struct LinkQueue
{
    /*链式队列的数据结构*/
    LQueuNode *front, *rear;
}LinkQueue;
LinkQueue Q;

void InitLinkQueue(LinkQueue &Q)
{
    /*链式队列的初始化即是让头尾结点都先指向新创建的头结点*/
    Q.front = Q.rear = (LQueueNode*)malloc(sizeof(LQueueNode));
    Q.front->next = NULL;
}

bool IsLQueueEmpty(LinkQueue Q)
{
    /*当头指针等于尾指针时链队为空*/
    if (Q.front == Q.rear)  return true;
    else  return false;
}

bool EnterLQueue(LinkQueue &Q, Elemtype x)
{
    /*
    1.先建立新结点
    2.尾插
    3.尾指针后移
    */
    LQueueNode *s = (LQueueNode*)malloc(sizeof(LQueueNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

bool DeleteLQueue(LinkQueue &Q, Elemtype &x)
{
    /*
    1.先判空
    2.头删
    3.若队列中只有一个结点，即出队后为空，需要特殊处理
    4.释放
    */
    if (Q.front == Q.rear)  return false;
    LQueueNode *p;  p = Q.front->next;
    x = p->data;
    Q.front->next == p->next;
    /*若只有一个结点，出队后尾指针要回到头结点*/
    if (Q.reat == p)
        Q.rear == Q.front;
    free(p);
    return true;
    
}

