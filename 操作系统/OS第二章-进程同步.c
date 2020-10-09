/*----------------------------------------------------------------------------------------------*
 *操作系统进程同步代码                                                                           
 * 0.境界资源的一般格式                                                                                                 
 * 1.实现互斥的软件方法                                                                                                             
 *    1.1 单标志法                                                                                                       
 *    1.2 双标志法先检查
 *    1.3 双标志法后检查
 *    1.4 皮特森算法
 * 2.信号线机制
 *    2.1 整型信号量
 *    2.2 记录型信号量
 * 3.经典同步问题
 *    3.1 生产者-消费者问题
 *    3.2 多生产者-多消费者
 *    3.3 读者-写者问题
 *    3.4 哲学家进餐问题
 *    3.5 吸烟者问题
 *---------------------------------------------------------------------------------------------*/

/*0.临界资源的一般格式：*/
do {
    entry section;          //进入区
    critical section;       //临界区
    exit section;           //退出区
    remainder section;      //剩余区
} while (true)

/*1.实现临界资源互斥的基本方法*/


//1.1 单标致法:保证互斥，但必须交替进入临界区，一方不进另一方也进不去，违背空闲让进
//进程P0：
while (turn != 0);          //标志为 1 时等待
critical section;           //访问临界区
turn = 1;
remainder section;
//进程P1：
while (turn != 1)           //标志为 0 时等待
critical section;           //访问临界区
turn = 0;
remainder section;


//1.2 双标志法先检查：不用交替，可以连续占用，但按顺序①②③④执行时，会同时进入临界区，违背慢则等待
//进程Pi：
while (flag[j]);            //①先检查临界区是否被其他进程占用，是则等待
flag[i] = TRUE;             //③其他进程用完后自己才能进入，设自己的标志为TRUE
critical section;           //访问临界区
flag[i] = FALSE;            //退出，把自己的标志改为FALSE
remainder section;
//进程Pj：
while (flag[i]);            //②先检查临界区是否被其他进程占用，是则等待
flag[j] = TRUE;             //④其他进程用完后自己才能进入，设自己的标志为TRUE
critical section;           //访问临界区
flag[j] = FALSE;            //退出，把自己的标志改为FALSE
remainder section;


//1.3 双标志法后检查:双方都把自己设置为TRUE，检查后都无法进入临界区访问，导致饥饿
//进程Pi：
flag[i] = TRUE;             //先表示自己要占用，将标志置为TRUE
while (flag[j]);            //然后检查临界区是否被其他进程占用，是则等待
critical section;           //访问临界区
flag[i] = FALSE;            //退出，把自己的标志改为FALSE
remainder section;
//进程Pj：
flag[j] = TRUE;             //先表示自己要占用，将标志置为TRUE
while (flag[i]);            //然后检查临界区是否被其他进程占用，是则等待
critical section;           //访问临界区
flag[j] = FALSE;            //退出，把自己的标志改为FALSE
remainder section;


//1.4 Peterson算法
//进程Pi：
flag[i] = TRUE;             //先将自己标志置为TRUE表示想要占用临界区
turn = j;                   //然后将turn设置为对方，表示谦让
while (flag[j] && turn == j);
    /*此处若谦让给对方后，对方也想使用(flag[j]=1)，则等待对方先使用
      若谦让给对方，但对方并不想使用，(flag[j]=0)则跳过等待，自己用*/
critical section;
flag[i] = FALSE;            //用完退出，把自己的标志改为FALSE
remainder section;


/*2.信号线机制*/

//2.1 整型信号量：用于表示资源数目的整型量S，有wait()和signal()两种操作
wait(S)
{
    while (S <= 0);         //若资源已用尽，则等待，但违背让权等待
    S = S - 1;              //若资源有剩余，则-1
}
signal(S)
{
    S = S + 1;              //归还一个资源
}


//2.2 记录型信号量：避免了忙等，采用了一个记录型数据结构(整型变量value+进程链表L)
typedef struct semaphore{
//记录型信号量的数据结构
    int value;              //整型变量value
    struct process *L;      //进程队链L
}semaphore
//记录型信号量对应的wait()操作
void wait(semaphore S){
    S.value--;              //请求一个资源
    if (S.value < 0)        //若资源已用尽
    {
        add this process to S.L;
                            //将此进程插入资源等待队列
        block(S.L);         //调用block原语让其自我阻塞
    }
}
void signal(semaphore S){
    S.value++;              //释放一个资源
    if (S.value <= 0)       //若资源已用尽(即有排队进程)
    {
        remove a process P to S.L;
                            //从等待队列中删去一个进程
        weakup(S.L);        //唤醒此进程
    }
}


//3.1 生产者-消费者问题
semaphore mutex = 1;        //临界资源互斥信号量
semaphore empty = n;        //空闲缓冲区数量
semaphore full = 0;         //非空缓冲区数量，初始化为0
producer()
{
    while (1)
    {
        produce an item in nextp;           //生产一个资源
        P(empty);                           //对空缓冲区数量做P操作
        P(mutex);                           //访问临界区(上锁)
        add nextp to buffer;                //资源放入临界区
        V(mutex);                           //退出临界区(解锁)
        V(full);                            //对非空缓冲区做V操作
    }
}
consumer()
{
    while (1)
    {
        P(full);                            //对非空缓冲区做P操作
        P(mutex);                           //访问临界区(上锁)
        remove an item from buffer;         //从临界区取出资源
        V(mutex);                           //离开临界区(解锁)
        V(empty);                           //对空缓冲区做V操作
        consume the iteml                   //消耗资源
    }
}

//3.2 多生产者消费者问题
semaphore plate = 1, apple = 0, orange = 0;
dad()
{//“父亲”削苹果，互斥的放入盘子中
    while (1)
    {
        prepare an apple;                   //准备一个“苹果”(资源)
        p(plate);                           //互斥的对“盘子”(空缓冲区)信号量做P操作
        put the apple on the plate;         //将资源放入缓冲区
        V(apple);                           //对“苹果”类资源信号量做V操作
    }
}
mom()
{//“母亲”剥桔子，互斥的放入盘子中
    while (1)
    {
        prepare an orange;                  //准备一个“橘子”(资源)
        p(plate);                           //互斥的对“盘子”(空缓冲区)信号量做P操作
        put the orange on the plate;        //将资源放入缓冲区
        V(orange);                          //对“苹果”类资源信号量做V操作
    }
}
son()
{//“儿子”互斥的从盘子中拿走橘子吃掉
    while (1)
    {
        P(orange);                          //互斥的取走句子
        take an orange from the plate;      
        V(plate);                           //对“盘子”资源做V操作
        eat the orange;
    }
}
gaughter()
{//“女儿”互斥的从盘子中拿走苹果吃掉
    while (1)
    {
        P(apple);                          //互斥的取走句子
        take an apple from the plate;      
        V(plate);                           //对“盘子”资源做V操作
        eat the apple;
    }
}


//3.3 读者-写者问题
int count = 0;                  //记录当前读者的数量
semaphore mutex = 1;            //用于实现互斥
semaphore rw = 1;               //用于保证读者写者互斥的访问文件
remaphore w = 1;                //用于实现写优先
writer()
{//写者
    while (1)
    {
        P(w);                   //在无写进程请求时进入
        P(rw);                  //写前上锁
        writing;                //写
        V(rw);                  //写完解锁
        V(w);                   //恢复对共享文件的访问
    }
}
reader()
{//读者
    while (1)
    {
        P(w);
        P(mutex);               //访问count前上锁               
        if (count == 0)         //当第一个进程读文件时
            P(rw);              //阻止写进程写
        count++;                //读者计数器+1
        V(mutex);               //解锁
        V(w);
        reading;                //读取
        P(mutex);               //互斥访问count变量
        count--；               //读者计数器-1
        if (count == 0)          //当最后一个读进程读完
            V(rw);              //允许写
        V(mutex);               //释放互斥变量count
    }
    
}

//3.4 哲学家进餐
//规则1：当一名哲学家左右两边筷子都可用时才允许拿起：
semaphore chopstick[5] = {1, 1, 1, 1, 1};       //五根筷子信号量
semaphore mutex = 1;                            //互斥取筷子信号量
Pi()
{//第i号哲学家的进程
    do
    {
        P(mutex);                               //取筷子互斥上锁
        P(chopstick[i]);                        //取左边筷子
        P(chopstick[(i + 1) % 5]);              //取右边筷子
        V(mutex);                               //互斥解锁
        eat;
        V(chopstick[i]);                        //放下左边筷子
        V(chopstick[(i + 1) % 5]);              //放下右边筷子
        think;
    } while (1);
}


//3.5 抽烟者问题，三个抽烟者和一个材料提供者
int random;
semaphore offer1 = 0;                           //烟草和烟纸
semaphore offer2 = 0;                           //烟草和胶水
semaphore offer3 = 0;                           //胶水和纸
semaphore finish = 0;                           //抽烟完成信号
process P1()
{//材料提供者进程
    while (1)
    {
        random = random % 3;                    //随机提供一种材料组合
        if (random == 0)
        {
            V(offer1);                          //提供第一种组合信号量
        }
        else if (random == 1)
        {
            V(offer2);                          //提供第二种组合信号量
        }
        else
        {
            V(offer3);                          //提供第三种组合信号量
        }
        提供材料;
        P(finish);                              //消耗掉完成信号量
    }
}
process P2()
{
    while (1)
    {
        P(offer3);                              //消耗第三种信号量
        制作烟，并抽掉;
        V(finish);                              //提供完成信号量
    }
}
process P3()
{
    while (1)
    {
        P(offer2);                              //消耗第二种信号量
        制作烟，并抽掉;
        V(finish);                              //提供完成信号量
    }
}
process P4()
{
    while (1)
    {
        P(offer1);                              //消耗第一种信号量
        制作烟，并抽掉;
        V(finish);                              //提供完成信号量
    }
}
