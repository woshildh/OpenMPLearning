OpenMP 学习教程

1. OpenMP 介绍与安装
  无
2.常用函数

  | 函数名                            |         作用          |   返回值    |
  | :---:                            | ------                | :---:      |
  |  omp_get_max_threads_num | 获取最大的线程数量，取决于 cpu 最大并行线程数|int|
  | omp_get_thread_num | 当多线程并行计算时，获取当前线程的 id |  int|
  |omp_get_num_threads | 当多线程并行计算时，获取线程的数量 | int |
  | num_threads( int)  | 设置使用多少个线程, 与 #pragma omp parallel (for) 一起用 | 无 |
  | private(i,j,k) | 定义omp私有的变量，内部改变之后，外部不会被改变，与 #pragma omp parallel (for) 一起用, 不会被初始化, 只能被传入外部以及定义的变量|无| 
  | reduction(operation:variable) | 见 使用方式7 | 无 | 
  |shedule(kind[,chunk_size])|见 使用方式8 | 无 |

3.使用方式\
&nbsp;&nbsp;&nbsp; 1). 并行运行代码块中的内容
      
 ````       
  #pragma omp parallel  // 使用最多的线程
  { 
     ...
  }
  #pragma omp parallel num_threads(2) //使用两个线程
  {
    ...
  }
 ````
&nbsp;&nbsp;&nbsp; 2). 并行运行 for 循环\
在这个例子中, OpenMP 会对 for 循环的 40 次执行过程进行拆分，
每个线程执行 10 次循环，第一个线程执行 0 ~ 10 次循环，以此类推。
````
#pragma omp parallel for num_threads(4)
for (int i = 0; i < 40; i++) {
    ...
}
````
&nbsp;&nbsp;&nbsp; 3). 作用域\
在 omp 执行块中定义的变量是局部的，不可被外部所调用。另外，这些变量对各个线
程来说不是共享的，每个线程都有一份自己的拷贝。
````
#pragma omp parallel
{
    int b; //只在块中可见，且各个线程都有自己的拷贝。
}
int c = b; //这个是错误的，b不可见
````
&nbsp;&nbsp;&nbsp; 4). 临界区\
omp parallel中多个线程并行执行可能会造成一些混乱，因此可以设置临界区，保证每一次只有一个线程可以进入。注意不能用到 omp for 中。
````
#pragma omp critical // 设置临界区同一时刻只有一个线程可以执行，可能执行多次
#pragma omp single  // 表示代码区，只能被一个线程执行，只能执行一次，可能是主线程也可能是其它线程
#pragma omp master  // 表示代码区，只能被主线程执行，因此只能执行一次
````
&nbsp;&nbsp;&nbsp; 5). mutex 线程互斥锁
````
omp_lock_t lock; // 声明锁
omp_init_lock(&lock); //初始化锁
omp_set_lock(&lock); //申请锁
omp_unset_lock(&lock); //释放锁
omp_destroy_lock(&lock); //销毁锁
````
&nbsp;&nbsp;&nbsp; 6). barrier 格栅
````
#pragma omp barrier // 先到的线程需要在此等待，直到所有的线程到达此处
````
&nbsp;&nbsp;&nbsp; 7). reduction
reduction([op]:[variable]) 是专为循环并行构造的时候使用的子句，可以完成类似于**累积运算**的功能。
```
    int results = 1;
    const int n = 8;
#pragma omp parallel for reduction(+:results) num_threads(4)
    for(int i = 0; i < n; i++)
    {
        results += i;
    }
    cout<<"sum: "<<results<<endl;
```
以上的代码完成 0 ~ 7 累加的功能，再单独加个 1。reduction 具体的实现步骤应当是:\
(1) 每一个线程拷贝一份 results，且初始值为 0。\
(2) 开始并行，线程0 计算0，1的累加，线程1 计算 2，3的累加，线程2 计算4，5的累加，线程3 计算6，7的累加。\
(3) 计算 results = results0 + results1 + results2 + results3，进行合并所有线程结果。\
可以到 reduction 工程中查看中间输出。注意不同的操作，每个线程初始化的值是不同的，最后进行合并的操作也有所区别。
不同的操作对应的初始值：+(0),*(1),-(0),&~(0),|(0),^(0),&&(1),||(0), max(INT_MIN), min(INT_MAX)
由于 OpenMP 这种独特的并行方式有些操作是不可以用的，会报错，**除法和取余操作是不可行的**。

&nbsp;&nbsp;&nbsp; 8). schedule\
schedule(kind[,chunk_size]) 是专为循环并行构造的时候使用的子句。其作用是控制循环并行结构的任务调度，
比如我的for循环要执行 1000 次，8个线程如何分配，每个线程执行哪些迭代等。
kind可以取值为static，dynamic，guided，auto。
* static，顾名思义就是静态分配，也是OpenMP默认采用的分配方式，即我们之前介绍的，0 ~ chunk_size分配给线程0，以此类推，循环往复。可以预测每个线程执行哪个迭代。
* dynamic 意思为动态分配，大白话来说就是先给每个线程chunk_size个迭代，进程执行完之后再分配chunk_size个迭代，直到执行完毕。无法预测每个线程执行哪个迭代。
* guided 是dynamic的改进，类似于动态调度，但每次分配的循环次数不同，
开始比较大，以后逐渐减小。chunk_size表示每次分配的迭代次数的最小值，
由于每次分配的迭代次数会逐渐减少，减少到chunk_size时，将不再减少。
如果不知道size的大小，那么默认chunk_size为1，即一直减少到1。具体是如何减少的，需要去参考手册。
* auto 是由编译器决定。

&nbsp;&nbsp;&nbsp; 9). ordered
ordered 是用于控制循环的每个迭代的执行顺序，让每个迭代按照顺序执行，等价于让不同的线程串行的执行代码。
```
#pragma omp parallel for ordered num_threads(4)
    for(int i =0; i < N; i++) {
        cout<<"Unordered: "<<omp_get_thread_num()<<"-->"<<i<<endl;
#pragma omp ordered
        cout<<"Ordered: "<<omp_get_thread_num()<<"-->"<<i<<endl;
    }
```

&nbsp;&nbsp;&nbsp; 9). section
parallel for 实现数据并行，parallel sections 实现功能并行。
将相互独立的功能分成几个块，由不同的线程执行。如果omp后面不加parallel，
默认section是按照串行的顺序执行的，**只有加了parallel，才会按照并行的方式执行section**。
当并行时，应当保证各个功能块是相互独立的。以之后的代码为例，
4个线程并行执行3个代码块，由于线程数多于代码块数，所有会有一个线程不执行。
```
#pragma omp parallel sections num_threads(4)
{
#pragma omp section
   {
   }
#pragma omp section
   {
   }
#pragma omp section
   {
   }

} 
```
&nbsp;&nbsp;&nbsp; 10). 注意事项
* 循环依赖。parallel 多个线程并行执行时，要让各个线程的数据和功能相互独立，一旦有依赖，会产生错误。
* 调试。在openmp并行程序中调试时，建议使用 printf进行输出，使用cout进行输出可能会不同线程的输出混杂。
