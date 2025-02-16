#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
    Matrix A(3,3,10);
    Matrix B(5,6,10.69);
    A.print();
    B.print();
    A.set(2,2,69.69);
    A.print();
    B.set(3,4,420.42);
    B.print();
    cout<<"(2,2) "<<A.get(2,2)<<endl;
    //B.save("output.txt");
    B.load("input.txt");
    B.print();
    cout<<"BREAKPOINT"<<endl;
    B.transpose();
    B.print();
    A.eye();
    A.print();
    B.eye();
    A.zero();
    A.print();
    cout<<"addition breakpoint"<<endl;
    Matrix C(4,10,3);
    Matrix D(4,10,4);
    D.set(2,2,0);
    C.add(D);
    C.print();
    A.add(B);
    C.sub(D);
    C.print();
    C.sub(D);
    C.print();
    cout<<"mult breakpoint"<<endl;
    Matrix E(2,4,4);
    Matrix F(4,2,2);
    E.print();
    F.print();
    F.lMult(E);
    F.print();
    Matrix G(2, 3, 1); // A 2x3 matrix filled with 1s
    Matrix H(3, 2, 2); // A 3x2 matrix filled with 2s
    G.print();
    H.print();
    G.rMult(H);
    G.print();
    cout<<"yet another breakpoint"<<endl;
    H.print();
    H.sMult(3.3);
    H.print();
    cout<<"det breakpoint"<<endl;
    Matrix I(2,2,5);
    I.set(2,2,4);
    cout<<I.det()<<endl;
    I.inv();
    I.print();
    Matrix J(3,3,3);
    J.set(2,2,2);
    J.set(3,3,5);
    J.print();
    J.inv();
    J.print();
    cout<<"gaussian breakpoint"<<endl;
    Matrix K(3,3,0);
    Matrix L(3,1,0);
    Matrix X(3,1,0);
    K.set(1,1,0);
    K.set(1,2,2);
    K.set(1,3,-1);
    K.set(2,1,2);
    K.set(2,2,-1);
    K.set(2,3,1);
    K.set(3,1,1);
    K.set(3,2,3);
    K.set(3,3,4);
    L.set(1,1,3);
    L.set(2,1,5);
    L.set(3,1,10);
    K.print();
    L.print();
    X.gaussian(K,L);
    cout << "Solution vector x:" << endl;
    X.print();
    return 0;
}
