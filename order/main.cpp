//
// Created by liudonghui on 2020/10/14.
//
#include <stdio.h>
#include <omp.h>

using namespace std;

int main() {
    int N = 20;
#pragma omp parallel for ordered num_threads(4)
    for(int i =0; i < N; i++) {
        printf("Unordered: %d --> %d\n",omp_get_thread_num(),i);
#pragma omp ordered
        printf("Ordered: %d --> %d\n",omp_get_thread_num(),i);
    }
    return 0;
}
