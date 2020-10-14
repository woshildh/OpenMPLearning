//
// Created by liudonghui on 2020/10/14.
//

#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main() {

    int a = 0, b = 0, c = 0, d = 0;

    // 声明锁并初始化
    omp_lock_t lock;
    omp_init_lock(&lock);

#pragma omp parallel num_threads(4)
    {
#pragma omp single // 只能执行一次，可以任何线程执行
        {
            a++;
            printf("This is thread %d\n",omp_get_thread_num());
        };
#pragma omp critical //会执行多次，但是进入临界区是互斥的，不能多个线程共同进入
        b++;

#pragma omp master // 只能执行一次，但是只有主线程可以执行, omp_get_thread_num() 一定是 0
        {
            c++;
            printf("This is thread %d\n",omp_get_thread_num());
        };

        omp_set_lock(&lock); // 设置锁之后, 就可以实现互斥了
        d++;
        printf("Thread num: %d, d: %d\n", omp_get_thread_num(),d);
        omp_unset_lock(&lock); // 和 set 成对出现

        if(omp_get_thread_num() == 0) //让主线程休眠 5s
            sleep(5);
#pragma omp barrier // 要求所有先到达的线程在此等待直到所有线程到达才可以继续执行. 尝试注释掉这一行代码，看看有什么区别
        printf("Thread num: %d passed here.\n",omp_get_thread_num());
    }

    printf("a: %d, b: %d, c: %d, d: %d\n",a,b,c,d);
    // 销毁
    omp_destroy_lock(&lock);

    return 0;
}