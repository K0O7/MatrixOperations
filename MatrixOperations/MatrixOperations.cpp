#include <iostream>
#include "CMatrix.cpp"


int main()
{
    CMatrix<int>* test = new CMatrix<int>();
    CMatrix<int>* test2 = new CMatrix<int>(3, 3);
    CMatrix<double>* test3 = new CMatrix<double>();
    test3->bCreate("mat_float_double_example.txt");
    test->bCreate("mat_int_example.txt");
    test->vPrintMat();
    test->vPrintTMat();
    test3->vPrintMat();
    test3->vPrintTMat();
    test2->bToIdentityM();
    test2->vPrintMat();
    test2->vPrintTMat();
    delete test3;
    delete test2;
    delete test;
}
