#include <iostream>

using namespace std;

class Matrix{
private:
    double x[3][3];//array to store the values for a matrix
public:
    //methods declaration for matrix processing
    //definitions are in the functions file
    void print();
    void set(double A, double B, double C, double D, double E, double F, double G, double H, double I);
    void set(int m, int n, double A);
    double get(int m, int n);
    void transpose();
    void eye();
    void zero();
    void save(string filename);
    void load(string filename);
    void add(Matrix B);
    void sub(Matrix B);
    double rcMult(Matrix B, int row, int col);
    void lMult(Matrix B);
    void rMult(Matrix B);
    void sMult(double s);
    double det();
    void inv();
};
