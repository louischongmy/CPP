#include <iostream>
#include <vector>

using namespace std;

class Matrix{
private:
    int m,n;
    vector<double> x;//array to store the values for a matrix
public:
    //constructors
    Matrix(){m=3; n=3; x.assign(m*n,0);}// Default constructor, set m and n to 3 and fill with 0
    Matrix(int m, int n, double z){this->m=m; this->n=n; x.assign(m*n,z);}// parameterized constructor, initialize a Matrix with dimension mxn with value z
    //methods declaration for matrix processing
    //definitions are in the functions file
    void print();
    void set(int j, int k, double z);
    double get(int j, int k);
    void save(string filename);
    void load(string filename);
    void transpose();
    void eye();
    void zero();
    void add(Matrix B);
    void sub(Matrix B);
    void lMult(Matrix B);
    void rMult(Matrix B);
    void sMult(double s);
    double det();
    void inv();
    void gaussian(Matrix A,Matrix B);

    //getters, no setters due to not recommend changing dimensions after it has been set
    int getm(){return m;}
    int getn(){return n;}

    //destructors
    ~Matrix(){}
};

