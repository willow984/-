/************************************************************************
 * 数据结构代码总结：
 * 第六章-树
 * 目录：
 *  1.二叉树
 *      ①二叉树的基本操作
 *      ①二叉树的顺序/链式存储
 *      ③二叉树的前/中/后/层序遍历的递归算法
 *      ④二叉树的前/中/后/层序遍历的非递归算法
 *  2.线索二叉树
 *      ①线索二叉树的存储结构
 *      ②前/中/后序线索二叉树的构造算法
 *      ③前/中/后序线索二叉树的遍历算法
 *  3.二叉排序树
 *      ①BST的构造
 *      ①BST的插入、查找、删除等操作
 *  4.平衡二叉树
 *      ①四种调整策略：LL/RR/LR/RL
 *  5.树和森林
 *      ①树的三种表示法双亲表示法(顺序)，孩子表示法、孩子兄弟表示法(链式)
 *      ③树的先根、后根遍历
 *      ②树与森林的转换
 * 
 * 最后更改:
 *     2020/8/6
 * 
 * 备注: 本章上述代码都是难点重点                                                            
 *
========================================================================*/


/*树*/
typedef struct BinaryTreeNode
{   
    /*二叉树结点的数据结构*/
    ElemType data;  //数据域
    struct BinaryTreeNode *lchild, *rchild;
                    //左孩子指针和右孩子指针
}BinaryTreeNode;

/*二叉树的先、中、后序遍历（递归实现）*/
void PreOrder(BinaryTreeNode *T){
    
    /*前序遍历*/
    if (T != NULL){
     Visit(T);
     PreOrder(T->lchild);
     PreOrder(T->rchild);
    }
}

void MidOrder(BinaryTreeNode *T){
    
    /*中序遍历*/
    if (T != NULL){
     PreOrder(T->lchild);
     Visit(T);
     PreOrder(T->rchild);
    }
}

void PostOrder(BinaryTreeNode *T){
    
    /*后序遍历*/
    if (T != NULL){
     PreOrder(T->lchild);
     PreOrder(T->rchild);
     Visit(T);
    }
}

/*二叉树的先、中、后序遍历（非递归实现）*/
void MidOrder(BinaryTreeNode *T){

    /*中序遍历先初始化一个栈和指针*/
    InitStack(S);
    BinaryTreeNode *p = T;

    while (p || !IsStackEmpty(S))
    {
        if (p){
        /*如果p存在，将p入栈,一路向左*/
            Push(S, p);
            p = p->lchild;
        }
        else{
        /*如果p已经走到最左边尽头*/
            Pop(S, p);  Visit(p);
            //出栈并访问上一个根节点
            p = p->rchild;
            //p指向其右孩子
        }
    }
}

void PreOrder(BinaryTreeNode *T){

    /*前序遍历先初始化一个栈和指针*/
    InitStack(S);
    BinaryTreeNode *p = T;

    while (p || !IsStackEmpty)
    {
        if (p){
        /*如果p不为空则先访问，再入栈*/
            Visit(p);  Push(S, p);
            p = p->lchild;
            //让p指向其左孩子
        }
        else{
        /*如果p走到最左边尽头*/
            Pop(S, p);
            p = p->rchild;
            //出栈上一个根并让p指向其右孩子
        }
    }
}

void PostOrder(BinaryTreeNode *T){

    /*后续非递归遍历，比前序中序多需要一个指针r*/
    InitStack(S);
    BinaryTreeNode *p = T;
    BinaryTreeNode *r = NULL;  //r标记最近访问过的结点

    while (p || !IsStackEmpty(S)){
        if(p){
        /*若p存在，一路向左，将沿路结点入栈*/
            push(S, p);
            p = p->lchild;
        }
        else{
            GetTop(S, p);  //读取栈顶，但不出栈
            if (p->rchild && p->rchild != r){
            /*若右子树存在且未被访问过*/
                p = p->rchild;  //转向其左子树
                push(S, p);     //入栈
                p = p->lchild;  //再一路向左
            }
            else{
                Pop(S, p);  //否则弹出节点并访问
                Visit(p->data);
                r = p;      //标记
                p = NULL;
            }
        }
    }
}

/*-----线索二叉树*/
/*线索二叉树的结点*/
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode * lchild, rchild;
    int ltag, rtag;
}ThreadNode, *ThreadTree;


/*以下内容开始线索二叉树*/
ThreadNode *pre = NULL;  
/*先定义全局变量pre是指向前驱的指针，起始时指向NULL，
  因为第一个访问的结点没有前驱*/

/*线索化操作，传入当前访问并要线索化的结点q*/
void Visit(ThreadNode *q)
{
    /*如果q指向的当前结点的左指针为空，则让左指针指向pre建立前驱线索*/
    if (q->lchild == NULL)
    {
        q->lchild = pre;
        q->ltag = 1;
    }

    /*如果此时pre指向的结点右指针为空，则让pre指向当前q建立后续线索*/
    if ( pre != NULL && pre->rchild == NULL)
    {
        pre->rchild = q;
        pre->rtag = 1;
    }

    /*对于每个结点建立完线索后，让pre指向q*/
    pre = q;
}

//中序-----------
void CreatInThread(Thread T)
{
    /*中序线索化的主函数接口*/

    pre = NULL;
    if (T != NULL)
        InThread(T);
    
    /*到了最后一个结点处要单独处理*/
    if (pre->rchild == NULL)
        pre->rtag = 1;
}

void InThread(ThreadTree T)
{
    /*二叉树的中序线索化，即在中序遍历的同时线索*/
    
    if (T != NULL)
    {   /*中序遍历，Visit()是线索操作*/
        InThread(T->lchild);
        Visit(T);  //访问并建立线索
        InThread(T->rchild);
    }
}


//前序-------------------------------------------------

void CreatPreThread(Thread T)
{
    /*先序线索化的主函数接口*/

    pre = NULL;
    if (T != NULL)
        PreThread(T);
    
    /*到了最后一个结点处要单独处理*/
    if (pre->rchild == NULL)
        pre->rtag = 1;
}

void PreThread(ThreadTree T)
{
    /*二叉树的先序线索化，即在先序遍历的同时线索*/
    
    if (T != NULL)
    {   /*先序遍历，Visit()是线索操作*/
        Visit(T);  //访问并建立线索
        
        /*如果ltag=1，说明左指针指向的并不是左子树而是前驱线索
          此时遍不必再去递归左子树，反之则继续递归左子树*/
        if (T->ltag == 0)
            PreThread(T->lchild);
        PreThread(T->rchild);
    }
}

//-----后序
void CreatPostThread(Thread T)
{
    /*后序线索化的主函数接口*/

    pre = NULL;
    if (T != NULL)
        PostThread(T);
    
    /*到了最后一个结点处要单独处理*/
    if (pre->rchild == NULL)
        pre->rtag = 1;
}

void PreThread(ThreadTree T)
{
    /*二叉树的后序线索化，即在后序遍历的同时线索*/
    
    if (T != NULL)
    {   /*先序遍历，Visit()是线索操作*/
        PreThread(T->lchild);
        PreThread(T->rchild);
        Visit(T);  //访问并建立线索
    }
}

