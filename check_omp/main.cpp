#include <iostream>
#include "omp.h"

int main() {
#ifdef _OPENMP
    std::cout<<"Hello, openmp."<<std::endl;
    std::cout<<"Max threads num is: "<<omp_get_max_threads()<<std::endl;
#else
    std::cout<<"OpenMP is not enabled."<<std::endl;
#endif
    return 0;
}
