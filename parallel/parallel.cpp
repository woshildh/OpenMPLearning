//
// Created by liudonghui on 2020/10/13.
//
#include <stdio.h>
#include <omp.h>

using namespace std;

int main() {

#pragma omp parallel  // 默认会使用 最多的线程数
{
    printf("This is %d of %d\n",omp_get_thread_num(),omp_get_num_threads());
};

    #pragma omp parallel num_threads(2) // 设置只使用一个线程
{
    printf("This is %d of %d\n",omp_get_thread_num(),omp_get_num_threads());
}

    int nums[50];
#pragma omp parallel for num_threads(4)
    for(int i = 0; i < 50; i++) {
        nums[i] = omp_get_thread_num();
    }
    for(int i = 0; i < 50; i++) {
        printf("%d ",nums[i]);
    }
    printf("\n");

    int i = 10, j = 18, k = 20;
#pragma omp parallel private(i,j,k) num_threads(4) // i 不会被初始化，每个线程有一个自己的拷贝
{
    printf("Thread num is %d, i = %d\n",omp_get_thread_num(),i);
    i = omp_get_thread_num() + 2;
}
    printf("i: %d\n",i);
#pragma omp parallel for private(i) num_threads(4)
    for( int i = 0;i < 50; i++)
        nums[i] = i;
    printf("i: %d\n",i);  // 外部 i 的值也不会被改变
    return 0;
}
