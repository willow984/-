/************************************************************************
 * 数据结构代码总结：
 * 第二章-线性表
 * 目录：
 *  1.顺序表
 *      ①顺序表的存储结构
 *      ②基本操作：初始化(静态+动态分配)/插入/删除/查找等
 *  2.链表
 *      ①单链表存储及基本操作(多带头，头尾插，头尾删是重点)
 *      ②双链表存
 *      ③循环链表
 *      ④静态链表
 * 最后更改:
 *     2020/8/6
 * 
 * 备注: 本章以上代码都是必须熟练的基本内容                                                           
 * 
========================================================================*/

/* 
** 先定义顺序表的数据结构Sqlist：
** MaxSize：指代当前数据结构所能容下的最大元素数量；
** ElemType：指当前数据结构存储的数据元素的类型（本部分用int）；
*/ 
#define MaxSize 65536
typedef int ElemType;
typedef struct Sqlist
{
    ElemType data[MaxSize];
    int length;
}Sqlist;

/*
** 1.初始化：void InitSqlist()
** 2.建表：CreatList()
** 3.插入：bool InsertElem()
** 4.删除：bool DeleteElem()
** 5.按值查找：int FindElem()
** 6.按序号查找：bool GetElem()
** 7.按顺序打印表中元素()
*/

/*------------------------------------------------------------------------*/
void InitSqlist(Sqlist &L)
{
    /*初始化顺序表L*/

    L.length = 0;
}
/*------------------------------------------------------------------------*/
bool CreatList(Sqlist &L, int n)
{
    /*创建表并初始化前n个数据元素*/

    /*先判断要初始的元素个数n的合法性*/
    if(n < 1 || n > MaxSize)
        return false;

    int i;    
    for(i = 0; i <n; ++i){
        cin>>L.data[i];
        L.length++;
    }
    return true;
}
/*------------------------------------------------------------------------*/
bool InsertElem(Sqlist &L, int i, ElemType e)
{
    /*在顺序表L下标为i的位置插入数据元素e*/

    /*先判断插入i位置的合法性，以及表是否已满*/
    if(i < 0 || i > L.length || L.length == MaxSize)
        return false;

    /*插入时，从最后一个元素起到第i个，依次往后移动一位*/
    int j;
    for(j = L.length - 1; j >= i; --j)
        L.data[j + 1] = L.data[j];
    L.data[j] = e;
    L.length++;
    return true;

    /*在顺序表上插入元素平均移动次数为n/2（n为插入前元素个数）*/

}
/*------------------------------------------------------------------------*/
bool DeleteElem(Sqlist &L, int i, ElemType &e)
{
    /*删除表L中下标为i的数据元素，并返回该元素的值到e*/

    /*先判断删除的位置是否合法,及表是否为空*/
    if(L.length == 0 || i < 0 || i > length - 1)
        return false;
    
    /*删除前，先把下表为i的数据取到e中，以免丢失
      删除时，从第i个元素起到倒数第二个，依次用后一个覆盖*/
    e = L.data[i];
    int j;
    for(j = i; i < L.length - 1; ++j)
        L.data[j] = L.data[j + 1];
    L.length--;
    return true;

/*在顺序表上删除元素平均移动次数为(n-1)/2（n为删除前元素个数）*/

}
/*------------------------------------------------------------------------*/
int FindElem(Sqlist L, int x)
{
    /*返回在顺序表L中找到的第一个比x大的元素的下标*/

    int i;
    for(i = 0; i < L.length; ++i){
        if(x < L.data[i])
            return i;
    }
}
/*------------------------------------------------------------------------*/
bool GetElem(Sqlist &L, int i, ElenType &e)
{
    /*返回表L指定位置i的数据元素到e*/

    /*先判断要查找元素的位置是否合法*/
    if(i < 0 || i > L.length - 1)
        return false;
    
    e = L.data[i];
    return true;
}
/*------------------------------------------------------------------------*/
void PrintList(SqList L)
{   
    /*按顺序打印表中所有元素*/

    /*先判断表是否空*/
    if(L.length = 0)
        cout<<"此表为空！"<<endl;

    /*以空格为分割打印元素*/    
    else{
        for(int i = 0; i < L.length; i++)
            cout<<L.Data[i])<<" ";
    }
}


/*天勤第二章07例题1：将一长度为n的数组的前端k(k<n)个元素逆序移动到数组后端，且数据不丢失*/
void ReverseSqlist(Sqlist &L, int left, int right, int k)
{
    /*left和right移动的最左边的元素和最右边的元素*/
    int i, j;
    ElemType tmp;
    for(i = left, j = right; i < left + k && i < j; ++i, --j){
        tmp = L.data[i]
        L.data[i] = L.data[j]
        L.data[j] = tmp;
    }
}


/*天勤第二章07例题2：将一长度为n的数组的前端k(k<n)个元素保持原序移动到数组后端，且数据不丢失*/
void ReverseSqlist(Sqlist &L, int left, int right, int k)
{
    int i, j;
    ElemType tmp;
    for(i = left, j = right; i < left + k && i < j; ++i, --j){
        tmp = L.data[i]
        L.data[i] = L.data[j]
        L.data[j] = tmp;
    }
}
void MoveToEnd(Sqlist &L, int n, int k)
{   
    /*n是当前数组元素个数，先将最左边k个逆置*/
    ReverseSqlist(L, 0, k - 1, k);

    /*再将最左边的k个与最右边k个逆置，由于最左边逆置两次，所以回复原序*/
    ReverseSqlist(L, 0, n - 1, k);
}

/*
** 天勤第二章真题1： 设将n(n>1)个整数存放在一维数组R中，试设计一个在时间和空间两方面
**   尽可能高效的算法，将R中保存的序列循环左移p(0<p<n)个位置，并计算复杂度。
*/ 
void ReverseSqlist(Sqlist &L, int left, int right, int k)
{
    int i, j;
    ElemType tmp;
    for(i = left, j = right; i < left + k && i < j; ++i, --j){
        tmp = L.data[i]
        L.data[i] = L.data[j]
        L.data[j] = tmp;
    }
}
void RotateLeft(Sqlist &L, int n, int p)
{
    ReverseSqlist(L, 0, p - 1, p);
    ReverseSqlist(L, p, n - 1, n - p);
    ReverseSqlist(L, 0, n - 1, n);
    
    /*复杂度为O(N)*/
}

/*天勤第二章08例题1：顺序表中找最值,返回下标*/
int FindMax(Sqlist L)
{
    ElemType max = L.data[0];
    int maxIndex = 0;
    for (int i = 0; i < n; ++i){
        if (max < L.data[i]){
            max = L.data[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}


 /*天勤第二章09例题1：归并顺序表*/
 void MergeSqlist(Sqlist L1, int len1, Sqlist L2, int len2, Sqlist &L3)
 {
     int i, j, k;
     i = j = k = 0;
     while (i < len1 && j < len2){
         if (L1.data[i] >= L2.data[j]){
             L3.data[k++] = L1.data[i++];
            /*此处k++,j++指先运算k再运算k自增*/
         }
         else
            L3.data[k++] = L2.data[j++];
     }
     while (i < len1)
        L3.data[k++] = L1.data[i++];
     while (j < len2)
        L3.data[k++] = L2.data[j++];
 }

 /*天勤第二章10例题1，以顺序表第一个元素a为轴心，划分表，使得a前面元素的值都小
 **于a，a后面元素得值都大于a
 */
void Partition(Sqlist &L)
{
    ElemType tmp = L.data[0]
    int i = 0;
    int j = L.length - 1;

    while (i < j){

        while (L.data[j] >= tmp && i < j)
            --j;
        if(i < j){
            L.data[i] = L.data[j];
            ++i;
        }

        while (i < j && L.data[i] < tmp)
            ++i;
        if(i < j){
            L.data[j] = L.data[i];
            --j;
        }
    }
    L.data[i] = tmp;
}


/*天勤第二章10例题2，以不在表中得一个元素comp为比较标准，第一个元素仍为轴心划分表，
**使得划分后前一部分元素的值都小于comp，一部分值都大于comp：

** 分析：分界线于comp的位置没有关系（即便它存在于表中），而与数轴位置有关系；
** 若 comp > 轴元素值，分界线则在右边，反之在左边；
 */
void Partition(Sqlist &L, ElemType comp)
{
    ElemType tmp = L.data[0]
    int i = 0;
    int j = L.length - 1;

    while (i < j){

        while (L.data[j] >= comp && i < j)
            --j;
        if(i < j){
            L.data[i] = L.data[j];
            ++i;
        }

        while (L.data[i] < comp && i < j)
            ++i;
        if(i < j){
            L.data[j] = L.data[i];
            --j;
        }
    }
    L.data[i] = tmp;
}

/*天勤第二章10例题3，以数组中任何一个元素a作为轴进行划分，前一部分小于a,后一
**部分大于a
**
**分析：即先将轴心交换到第一个位置，然后以第一个位置为轴心进行交换顺序（例1）
*/
void Partition(Sqlist &L, int k)
{
    ElemType tmp;
    int i = 0;
    int j = L.length - 1;

    tmp = L.data[0];
    L.data[0] = L.data[k];
    L.data[k] = tmp;
    tmp = L.data[0];

    while (i < j){

        while (L.data[j] >= tmp && i < j)
            --j;
        if(i < j){
            L.data[i] = L.data[j];
            ++i;
        }

        while (i < j && L.data[i] < tmp)
            ++i;
        if(i < j){
            L.data[j] = L.data[i];
            --j;
        }
    }
    L.data[i] = tmp;
}




typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode;
LNode *Head;//最先创建的是头指针
Head = (LNode*)malloc(sizeof(LNode));//为头指针分配结点，有可能是头节点或第一个结点


bool IsEmpty(LNode *Head)
{//带头结点的单链表判空
    if(H->next == NULL)
        return true;
    /*不带头结点的单链表判空直接是：
         if(H == NULL) */
    
    else 
        return false;
}



typedef struct DLNode
{
    ElemType data;
    struct DLNode *prior;
    struct DLNode *next;
}DLNode;
DLNode *L;
L = (DLNode*)malloc(sizeof(DLNode));

bool IsEmpty(DLNode *Head)
{//带头结点的双链表判空
    if(H->next == NULL)
        return true;
    /*不带头结点的双链表判空直接是：
         if(H == NULL) */
    
    else 
        return false;
}

bool HeadInsert(LNode *Head, int e)
{//带头结点的单链表头插

}

bool CreatLinkListR(LNode *&Head， int n)
{//带头结点的单链表尾插法建表,n为建立时要初始的元素个数
    //先初始化头结点(若头结点没有被初始化过的话)
    Head = (LNode*)malloc(sizeof(LNode));
    Head->next = NULL;

    LNode *r = Head;//始终指向最后一个结点的指针
    LNode *p = NULL;//定义一个用来建立新结点的指针

    int i;
    for(i = 0; i < n; ++i){
        p = (LNode*)malloc(sizeof(LNode));
        p->next = NULL;
        /*让新建的空指针先指向NULL(好的编码习惯)*/
       
        cin>>p->data; 
        r->next = p;
        r = p;
    }
    
    return true;
}

bool CreatLinkListH(LNode *&Head, int n)
{//带头结点的单链表头插法建表,n为建立时要初始的元素个数
    //先初始化头结点(若头结点没有被初始化过的话)
    Head = (LNode*)malloc(sizeof(LNode));
    Head->next = NULL;

    LNode *p = NULL;//定义一个用来建立新结点的指针

    int i;
    for(i = 0; i < 0; ++i){
        p = (LNode*)malloc(sizeof(LNode));
        p->next == NULL;
        /*让新建的空指针先指向NULL(好的编码习惯)*/

        cin>>p->data;
        p->next = Head->next;
        Head->next = p;
    }
    
    return true;
}


/*天勤>第二章>06>【例题1】
**键盘输入n个英文字母，输入格式为n、c1、c2.....cn，其中n表示字母个数/
**请以这些输入数据建立一个单链表，并要求字母不重复的存入链表。
*/
bool CreatLinkListH(LNode *&Head, int n)
{
    /*用头插法实现*/
    char ch;
    Head = (LNode*)malloc(sizeof(LNode));
    Head->next = NULL;
    LNode* p;

    /*n次循环，共初始化n个元素*/
    int i;
    for(i = 0; i <n; i++){
        cin>>ch;
        p = head->next;

        /*每次插入时，先扫描一遍头结点后的所有节点，直到结束，
        遇到重复的值则直接退出整个循环*/
        while(p != NULL){
            if(p->data == ch)
                break;
            p = p->next;
        }

        p = (LNode*)malloc(sizeof(LNode));
        p->data = ch;
        p->next = head->next;
        head->p;
    }

    return true;
}


/*链表逆置*/
void ReverseLinkList(LNode *&L, LNode *l, LNode *r)

/*天勤第二章08例题1链表中找最值*/
LNode* FindMax(LNode *Head)
{
    ElemType max = Head->next->data;
    LNode *p, *q;
    p = Head->next;
    q = Head->next;
    while(p != NULL){
        if(max < p->data){
            max = p->data;
            q = p;/*本例子中q只起到标记作用*/
        }
        p = p->next;
    }
    return q;
}

/*天勤第二章08例题2: 一双链表非空，由head头结点指出，结点结构为{link，data，rlink}
** 设计将结点数据域data值最大的那个结点移动到链表最前面的算法，要求不得重新申请空间。
*/
void MaxToHead(DLNode *Head)
{
    ElemType max = Head->rlink->data;
    LNode *p, *q;
    p = Head->rlink;
    q = Head->rlink;

    /*先找最值结点，用q指针标出*/
    while(p != NULL){
        if(max < p->data){
            max = p->data;
            q = p;/*本例子中q只起到标记作用*/
        }
        p = p->rlink;
    }
    
    /*删除*/
    q->link->rlink = q->rlink;
    /*如果q已经是最后一个结点，则不用后指向前*/
    if(q->rlink != NULL)
        q->rlink->llink = q->llink;

    /*插入*/
    q->rlink = head->rlink;
    head->rlink = q;
    q->llink = head;
    q->rlink->llink = q;
}


/*
**天勤第二章08真题
**  假设采用带头结点的单链表保存单词，当两个单词有相同后缀时，则可共享后缀
**的存储空间，如图所示：
**  设str1和str2分别指向两个单词所在的单链表头结点，链表结点结构为{data,
** next}，请设计一个算法，找出由str1和str2指向两个链表共同后缀的起始位置，
**及分析其复杂度。
*/

LNode *FindFirstCommon(LNode *str1, LNode *str2)
{
    
    LNode *p, *q;
    p = str1;
    q = str2;

    /*先求表长之差*/
    int len1, len2;
    len1 = len2 = 0;
    while(str1->next != NULL){
        ++len1;
        str1 = str1->next;
    }
    while(str2->next != NULL){
        ++len2;
        str2 = str2->next;
    }

    /*让较长的表先移动长度的差值，以实现后续同步移动*/
    if(len1 > len2){
        for(int i = 0; i < len1 - len2; ++i)
            p = p->next;
    }
    else if (len2 > len1)
    {
        for(int i = 0; i < len2 - len1; ++i)
            q = q->next;
    }

    /*让两表同步移动，遇到相同或到达表末尾结束*/
    while(p != q && q != NULL){
        p = p->next;
        q = q->next;
    }
    
    return p;
}


 /*天勤第二章09例题2：按原序归并两个有序链表*/
void MergeLinkList(LNode *head1, LNode *head2, LNode *&head3)
{
    /*尾插法是原序，头插法是逆序,故用尾插*/
    LNode *p = head1->next;
    LNode *q = head2->next;
    LNode *r;
    head3 = head1;
    head3 -> next = NULL
    r = head3;
    
    while (p != NULL && q != NULL)
    {
        if (p->data <= q->data)
        {
            r->next = p;
            p = p->next;
            r = r->next;
        }
        else
        {
            r->next = q;
            q = q->next;
            r = r->next;
        }
    }
    if (p != NULL)
        r->next = p;
    if (q != NULL)
        r->next = q;
}

void MergeLinkListR(LNode *head1, LNode *head2, LNode *&head3)
{
    /*尾插法是原序，头插法是逆序，故用头插*/
    LNode *p = head1->next;
    LNode *q = head2->next;
    LNode *s;
    head3 = head1;
    head3->next = NULL;

    while (p != NULL && q != NULL)
    {
        if (p->data <= q->data)
        {
            s = p;
            p = p->next;
            s->next = head3->next;
            head3->next = s;
        }
        else
        {
            s = q;
            q = q->next;
            s->next = head3->next;
            head3->next = s;
        }
    }

    while (p != NULL)
    {
        s = p;
        p = p->next;
        s->next = head3->next;
        head3->next = s;
    }
    
    while (q != NULL)
    {
        s = q;
        q = q->next;
        s->next = head3->next;
        head3->next = s;
    }

}
    

/*双链表的尾插法建表*/
bool InsertDLinkList(DLNode *&Head, int n)
{
    DLNode *p, *r;
    head = (DLNode*)malloc(sizeof(DLNode));
    head->prior = NULL;
    head->next = NULL;
    r = head;
    cin>>n;

    ElemType e;
    for (int i = 0; i < n; i++){
         cin>>e;
         p = (DLNode*)malloc(sizeof(DLNode));
         p->data = e;
         r->next = p;
         p->prior = r;
         r = s;
    }
    r->next = NULL;
}