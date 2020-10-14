//
// Created by liudonghui on 2020/10/14.
//

#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main() {
#pragma omp parallel sections num_threads(4) // 有一个线程不会执行
{
#pragma omp section
        {
            int thr = omp_get_thread_num();
            printf("section 1, thread %d - sleeping 1 second\n", thr);
            sleep(1);
            printf("section 1 done\n");

        }
#pragma omp section
        {
            int thr = omp_get_thread_num();
            printf("section 2, thread %d - sleeping 2 second\n", thr);
            sleep(1);
            printf("section 2 done\n");
        }
#pragma omp section
        {
            int thr = omp_get_thread_num();
            printf("section 3, thread %d - sleeping 3 second\n", thr);
            sleep(1);
            printf("section 3 done\n");
        }
}
    return 0;
}