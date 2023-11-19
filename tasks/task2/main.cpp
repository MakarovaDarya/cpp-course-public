#include "matrix.h"

#include "iostream"
#include "matrix.cpp"

int main()
{
    double array[3] = { 3,4,5 };
    RowMatrix r(array, 3);
    r[0] = 10;
    r[1] = 20;
    r[2] = 30;
    std::cout << r[0] << " " << r[1] << " " << r[2] << std::endl;
    return 0;
}
