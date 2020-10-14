//
// Created by liudonghui on 2020/10/14.
//
#include <stdio.h>
#include <omp.h>

using namespace std;

int main() {
    int results = 1;
    const int n = 8;
    int nums[n] = {1,2,3,4,67,98,22,10};

//    omp_lock_t lock;
//    omp_init_lock(&lock);

#pragma omp parallel for reduction(+:results) num_threads(4)
    {
        for(int i = 0; i < n; i++)
        {
//            omp_set_lock(&lock);
//            printf("%d, %d, %d\n",omp_get_thread_num(),results,i);
//            omp_unset_lock(&lock);
            results += i;
        }
    }
    printf("sum: %d\n",results); //输出为 29
    results = 0;
#pragma omp parallel for reduction(max:results) num_threads(4)
    {
        for(int i = 0; i < n; i++)
        {
//            omp_set_lock(&lock);
//            printf("%d, %d, %d\n",omp_get_thread_num(),results,i);
//            omp_unset_lock(&lock);
            results = (results>nums[i]?results:nums[i]);
        }
    }
    printf("max value is: %d\n",results);

    //omp_destroy_lock(&lock);
    return 0;
}
