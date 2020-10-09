/************************************************************************
 * 数据结构代码总结：
 * 第七章-图
 * 目录：
 *  1.图的四种存储结构及相关操作
 *      ①邻接矩阵
 *      ②邻接链表
 *      ③邻接多重表(仅用于无向图)
 *      ④十字链表(仅用于有向图)
 *  2.图的遍历：
 *      ①图的广度优先遍历(BFS)算法 
 *      ②图的深度优先遍历(DFS)算法
 *  3.构造最小生成树：
 *      ①Prim算法
 *      ②Kruskal算法
 *  4.求最短路径：
 *      ①Dijkstra算法
 *      ②Floyd算法
 *      ③BFS算法求最短路径
 *  5.拓扑排序:
 *      ①拓扑排序算法
 *      ②用DFS实现逆拓扑排序
 *  6.关键路径：
 *      *求解关键路径
 *
 * 最后更改:
 *     2020/8/6
 * 
 * 备注: 408要求本章代码较少，多数为手算                                                              
 * 
========================================================================*/
#define MaxVertexNum 1000   //最大容量1000
typedef char VertexType;    //顶点数据类型定义为char
typedef int EdgeType;       //边数据类型定义为int
/*--------------------------1.图的四种存储结构---------------------------*/
//①用邻接矩阵存储：一维数组存顶点信息+二维数组存边的邻接关系
typedef struct MGraph
{
    VertexType Vertex[MaxVertexNum];            //一维数组存顶点
    EdgeType Edge[MaxVertexNum][MaxVertexNum];  //二维数组存边
    int vertexNum, edgeNum;                     //标示图中的顶点数、边数
}Mgraph;

//②用邻接链表存储：顺序表存顶点+单链表存该顶点邻接的边
typedef struct ArcNode
{/*弧结点(单链表结点)*/
    int adjVex;                 //指向哪个结点
    struct ArcNode *next;       //指向下一条弧的指针
    //InfoType info             //权(可选)
}ArcNode;
typedef struct VNode
{/*顶点结点(顺序表结点)*/
    VertexType data;            //顶点值
    ArcNode *first;             //顶点的第一条弧
}VNode,AdjList[MaxVertexNum];   //此步定义结构数组类型，即顶点顺序表类型
typedef struct ALGraph
{/*图的结构*/
    AdjList vertices;           //创建结构数组(顶点顺序表)
    int vexnum, arcnum;         //标示顶点数，弧数
}ALGraph;

//③邻接多重表

//④十字链表

/*------------------------------2.图的遍历------------------------------*/
//①图的广度优先遍历(BFS)
bool visited[MAX_Verter_num];  //访问标记数组，true表示已访问过；
Graph* FirstNeighbor();        //找某图中与顶点v相邻的第一个顶点
Graph* NextNeighboor();        //找某图中与顶点v相邻的下一个顶点
void BFSTraverse(Graph G)
{
    for (i = 0; i < G.vnexnum; ++i)
        visited[i] = false;         //先将标记数组全置false
    InitQueue(Q);                   //初始化一个辅助队列
    for (i = 0; i < G.vexnum; ++i)
    {//找标记数组中的false，即对未被遍历的连通分量再次遍历
        if (!visited[i])
            BFS(G,i);
    }
}
void BFS(Graph G, int v)
{/*v为起始结点*/
   visit(v);   visited[v] = true;  /*访问并将标记置为true*/
   Enqueue(Q,v);                   /*将起始顶点入队*/
   /*当队不空时循环，将队头出队，并使与其相接的顶点入队*/
   while (!IsEmpty(Q))
   {
       DeQueue(Q,v);  /*出队*/
       for (w = FirstNeighbor(G,v); w > 0; NextNeighbor(G,v,w))
       {/*w令为与v相邻的第一个顶点，依次找与v相邻的下一个顶点*/
           if (!visited[w])
           {/*若未被访问过，则访问、标记、入队*/
               visit(w);    
               visited[w] = true;
               Enqueue(Q,w);
           }//if
       }//for
   }//while
}

//②图的深度优先遍历(DFS)
bool visited[MAX_VERTEX_NUM];  //访问标记数组，true表示已访问过；
void DFSTraverse(Graph G)
{
    for (v = 0; v < G.vexnum; ++v)
        visited[i] = false;
    for (v = 0; v < G.vexnum; ++v)
        if (!visited[v])  //若某一顶点处未被访问，则从此节点开始依次DFS
            DFS(G, v);
}
void DFS(Grpah G, int v)
{
    //访问第一个顶点并标记
    visit(v);
    visited[v] = true;
    //开始递归的访问与第一个结点邻接的所有顶点
    for (w = FirstNeighbor(G, v), w >= 0; w = NextNeighbor(G, v, w))
    {
        if(!visited[w])
            DFS(G,w);
    }
}

/*-----------------------------3.最小生成树-------------------------------*/
//①Prim

//②Kruskal

/*------------------------------4.拓扑排序--------------------------------*/
//拓扑排序
bool TopologicalSort(Graph G)
{
    initStack(S);                       //初始化一个辅助栈
    for (int i = 0; i < G; i++)         
        if (indegree[i] == 0)
            Push(S, i);                 //当有入度为0的顶点，入栈

    int count = 0;                      //count用来计已打印的顶点数量
    while (!IsEmpty(S))
    {
        Pop(S, i);                      
        print[count++] = i;             //栈不为空时，栈顶元素出栈并打印
        for (p = G.vertices[i].firstarc; p = p->nextarc)
        {
            v = p->adjvex;
            if (!(--indegree[v]))       //与出栈顶点相连的所有顶点权值减1
                Push(S,v);              //若某顶点权值减1后为0，将其入栈
        }
    }
    if(count < G.vexnum)                //若count小于图的定点数，说明此图有环，不可拓扑排序
        return false;
    else
        return true;
}