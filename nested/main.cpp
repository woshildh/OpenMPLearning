//
// Created by liudonghui on 2020/10/14.
//

#include <stdio.h>
#include <omp.h>

int main()
{
    // 允许嵌套并行
    omp_set_max_active_levels(2);

#pragma omp parallel num_threads(2)
{
    printf("ID: %d, Max threads: %d, Num threads: %d \n",omp_get_thread_num(), omp_get_max_threads(), omp_get_num_threads());
#pragma omp parallel num_threads(5)
    printf("Nested, ID: %d, Max threads: %d, Num threads: %d \n",omp_get_thread_num(), omp_get_max_threads(), omp_get_num_threads());
}
    return 0;
}
