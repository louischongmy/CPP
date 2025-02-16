#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
    circuit X;
    X.help();
    X.calc();
    circuit Y(12,1,1,18);
    Y.calc();
    circuit W(12,1,1,30);
    W.calc();
    return 0;
}
