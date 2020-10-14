//
// Created by liudonghui on 2020/10/14.
//
#include <stdio.h>
#include <omp.h>

#define CHUNK_SIZE 5

// scheduling:
//   static  -> statically preassign iterations to threads
//   dynamic -> each thread gets more work when its done at runtime
//   guided  -> similar to dynamic with automatically adjusted chunk size
//   auto    -> let the compiler decide!

int main()
{
    const int niter = 25;

#pragma omp parallel for schedule(static, CHUNK_SIZE) num_threads(4)
    for (int i = 0; i < niter; i++) {
        int thr = omp_get_thread_num();
        printf("Static iter %d of %d on thread %d\n", i, niter, thr);
    }

#pragma omp parallel for schedule(dynamic, CHUNK_SIZE) num_threads(4)
    for (int i = 0; i < niter; i++) {
        int thr = omp_get_thread_num();
        printf("Dynamic iter %d of %d on thread %d\n", i, niter, thr);
    }
    return 0;
}
