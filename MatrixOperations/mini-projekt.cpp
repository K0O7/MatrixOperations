#include <iostream>
#include "CMatrix.cpp"


int main()
{
    CMatrix<int>* test = new CMatrix<int>();
    CMatrix<int>* test2 = new CMatrix<int>(3,3);
    CMatrix<double>* test3 = new CMatrix<double>();
    test3->create("mat_float_double_example.txt");
    test->create("mat_int_example.txt");
    test->PrintMat();
    test->PrintTMat();
    test3->PrintMat();
    test3->PrintTMat();
    test2->toIdentityM();
    test2->PrintMat();
    test2->PrintTMat();
    delete test3;
    delete test2;
    delete test;
}