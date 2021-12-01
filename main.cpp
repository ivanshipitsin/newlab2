#include "menu.hpp"
#include<omp.h>

int main()
{
    omp_set_dynamic(0);
    omp_set_num_threads(256);
    Menu m(400,400);
    m.Init();
    m.start();

    return 0;
}