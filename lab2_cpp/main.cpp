//main file of the matrix program that processes a 3x3 matrix
//relevant functions and header files are included
#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
    Matrix A;
    Matrix B;
    Matrix C;
    A.set(1.2,3.42345,5.6,7.8,9.0,6.9,4.20,8.7,6.5);
    A.print();
    A.set(2,1,23.3);
    A.print();
    cout<<A.get(3,2)<<endl;
    A.transpose();
    A.print();
    B.eye();
    B.print();
    B.zero();
    B.print();
    C.load("input.txt");
    C.print();
    A.save("output.txt");
    cout<<"1-----------------"<<endl;
    A.print();
    C.print();
    A.add(C);
    A.print();
    cout<<"2-----------------"<<endl;
    A.print();
    C.print();
    A.sub(C);
    A.print();
    cout<<A.rcMult(C,1,1)<<endl;
    cout<<"3-----------------"<<endl;
    A.set(1,2,3,4,5,6,7,8,9);
    B.set(2,3,4,5,6,7,8,9,10);
    A.print();
    B.print();
    A.lMult(B);
    A.print();
    A.set(1,2,3,4,5,6,7,8,9);
    A.rMult(B);
    cout<<"4-----------------"<<endl;
    A.print();
    cout<<"5-----------------"<<endl;
    B.print();
    B.sMult(2.2);
    B.print();
    A.set(1,2,3,0,1,4,5,6,0);
    A.set(1,2,3,4,5,6,7,8,9);
    cout<<A.det()<<endl;
    cout<<"6-----------------"<<endl;
    A.print();
    A.inv();
    A.print();
    return 0;
}
