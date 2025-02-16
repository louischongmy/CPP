//functions file for the program
//mainly includes the method definition in the header file
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <vector>
#include "functions.h"

using namespace std;

void Matrix::print(){
    cout<<string(n*7+3,'=')<<endl;//formatting, printing n*7+3 of '=', n due to number of col, 7 due to setw, 3 is offset
    for (int i=0;i<m;i++) {//iterating each element in the vector
        cout<<"|";//formatting
        for (int j=0;j<n;j++) {
            cout<<setprecision(2)<<fixed<<setw(7)<<x.at(i*n+j);//printing
        }
        cout<<" |"<<endl;//formatting
    }
    cout<<string(n*7+3,'=')<<endl;//formatting
}

void Matrix::set(int j, int k, double z){
    x.at(((j-1)*n)+k-1)=z; //formula is based on the fact that row coord need to mult by total row, -1 is for human offset
}

double Matrix::get(int j, int k){
    return x.at(((j-1)*m)+k-1);//-1 is to account for human offset, since humans usually start counting from 1
}

void Matrix::save(string filename){
    ofstream file;//create filestream
    file.open(filename);//open file
    if (!file.is_open()){//check if file is opened correctly
        cout << "Failed to open the file " <<filename<< endl;//error message
    }else{
        file.clear();
        for (int i=0;i<m;i++) {
            for (int j=0;j<n;j++) {
            file<<setprecision(2)<<fixed<<setw(7)<<x.at(i*n+j);//writing to file with formatting
            if (j<(n-1)){file<<",";}//only print a , if it is not the last element of the row
            }
        file<<endl;
        }
    }
    file.close();//closing the file
}

void Matrix::load(string filename){
    fstream file;//create filestream
    string word;
    double buf;//buffer
    file.open(filename);//open file
    if (!file.is_open()){//checking if file is opened correctly
        cout << "Failed to open the file " <<filename<< endl;//error message
    }else{
        for (int i=0;i<m;i++) {
            for (int j=0;j<n;j++) {
                if (file>>word){//reading from file
                    buf=atof(word.c_str());//ascii to float into buffer
                    if (buf!=0.0 || (buf== 0.0 && word[0]=='0')){//checking to ensure input is float
                        x.at(i*n+j)=buf;//insertion
                    }
                else cout<<"the input "<<word<<" is not a float, converting it to 0.00"<<endl;//error message
                }
            }
        }
    }
    file.close();//closing the file
}

void Matrix::transpose() {
    // Create a temporary vector to store transposed values
    vector<double> temp(n*m);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            temp[j*m+i] = x[i*n+j];
        }
    }
    // Swap dimensions
    swap(m,n);
    x = move(temp);
}


void Matrix::eye(){
    if (m!=n){//dimension check
        cout<<m<<" is not equal to "<<n<<" thus cannot be eye'd"<<endl;
        return;
    }
    else{
        for (int i=0;i<m;i++) {
            for (int j=0;j<n;j++) {
                if (i==j){//diagonal check
                    x.at(i*m+j)=1;
                }
                else x.at(i*m+j)=0;
            }
        }
    }
}

void Matrix::zero(){
    x.assign(m*n,0);
}

void Matrix::add(Matrix B){
    if((this->m!=B.m)||(this->n!=B.n)){//dimension check
        cout<<"the dimensions of the two matrices are not the same, thus cannot do addition"<<endl;
        return;
    }
    else{
        for (int i=0;i<m;i++) {
            for (int j=0;j<n;j++) {
                x.at(i*n+j)=x.at(i*n+j)+B.x.at(i*n+j);
            }
        }
    }
}

void Matrix::sub(Matrix B){
    if((this->m!=B.m)||(this->n!=B.n)){
        cout<<"the dimensions of the two matrices are not the same, thus cannot do subtraction"<<endl;
        return;
    }
    else{
        for (int i=0;i<m;i++) {
            for (int j=0;j<n;j++) {
                x.at(i*n+j)=x.at(i*n+j)-B.x.at(i*n+j);
            }
        }
    }
}

void Matrix::lMult(Matrix B) {
    if (B.n != this->m) {
        cout << "The number of columns of B does not equal the number of rows of this matrix. Cannot multiply." << endl;
        return;
    }
    // Create a temporary matrix to store the result
    Matrix temp(B.m, this->n,0);
    double sum = 0;
    // Perform matrix multiplication
    for (int i = 0; i < B.m; i++) {              // Rows of B
        for (int j = 0; j < this->n; j++) {      // Columns of this
            sum = 0;
            for (int k = 0; k < this->m; k++) {  // Common dimension
                int indexThis = k * this->n + j; // Access F[k][j]
                int indexB = i * B.n + k;        // Access E[i][k]
                // Accumulate product
                sum += this->x[indexThis] * B.x[indexB];
            }
            // Store result in temp
            int indexTemp = i * temp.n + j;      // Row `i`, column `j` in temp
            temp.x[indexTemp] = sum;
        }
    }
    // Update the current matrix with the result
    *this = temp;
}

void Matrix::rMult(Matrix B) {
    if (this->n != B.m) {
        cout << "The number of columns of this matrix does not equal the number of rows of B. Cannot multiply." << endl;
        return;
    }
    // Create a temporary matrix to store the result
    Matrix temp(this->m, B.n, 0);
    double sum = 0;
    // Perform matrix multiplication
    for (int i = 0; i < this->m; i++) {          // Rows of this
        for (int j = 0; j < B.n; j++) {          // Columns of B
            sum = 0;
            for (int k = 0; k < this->n; k++) {  // Common dimension
                // Compute indices
                int indexThis = i * this->n + k; // Access A[i][k]
                int indexB = k * B.n + j;        // Access B[k][j]
                // Accumulate product
                sum += this->x[indexThis] * B.x[indexB];
            }
            // Store result in temp
            int indexTemp = i * temp.n + j;      // Row `i`, column `j` in temp
            temp.x[indexTemp] = sum;
        }
    }
    // Update the current matrix with the result
    *this = temp;
}

void Matrix::sMult(double s){
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) {
            x.at(i*n+j)=x.at(i*n+j)*s;
        }
    }
}

double Matrix::det() {
    // Ensure the matrix is square
    if (m != n) {
        cout << "the input matrix is not a square matrix thus no determinant can be calculated"<<endl;
        return numeric_limits<double>::quiet_NaN();//return nan since cannot return 0 as it would affect inv()
    }

    // Handle 2x2 matrix
    if (m == 2) {
        double a=x[0], b=x[1];
        double c=x[2], d=x[3];
        return a*d-b*c;
    }

    // Handle 3x3 matrix
    if (m == 3) {
        double a=x[0],b=x[1],c=x[2];
        double d=x[3],e=x[4],f=x[5];
        double g =x[6],h=x[7],i=x[8];
        return a*(e*i-f*h)-b*(d*i-f*g)+c*(d*h-e*g);
    }
    // Handle unsupported sizes
    cout << "Determinant calculation is only supported for 2x2 or 3x3 matrices." <<endl;
    return numeric_limits<double>::quiet_NaN();
}

void Matrix::inv(){
    double buf=det();
    if (buf==0){
        cout<<"the matrix is singular and does not have an inverse."<<endl;//if the det is 0 there is no inv
        return;
    } if (isnan(buf)){
        cout<<"wrong size input, inverse cannot be calculated."<<endl;
        return;
    } if (m==2&&n==2){
        Matrix temp(m,n,0);
        temp.x.at(0)=this->x.at(3);
        temp.x.at(3)=this->x.at(0);
        temp.x.at(1)=-this->x.at(1);
        temp.x.at(2)=-this->x.at(2);
        for (int i=0; i<4; i++)temp.x.at(i)/=buf;
        this->x=temp.x;

    } if (m==3&&n==3){
        // Inverse for 3x3 matrix
        Matrix temp(m, n, 0);

        // Calculate cofactors
        double a = this->x[0],b=this->x[1],c=this->x[2];
        double d = this->x[3],e=this->x[4],f=this->x[5];
        double g = this->x[6],h=this->x[7],i=this->x[8];

        // Calculate cofactors
        double cofactor_a=e*i-f*h;
        double cofactor_b=-(d*i-f*g);
        double cofactor_c=d*h-e*g;

        double cofactor_d=-(b*i-c*h);
        double cofactor_e=a*i-c*g;
        double cofactor_f=-(a*h-b*g);

        double cofactor_g=b*f-c*e;
        double cofactor_h=-(a*f-c*d);
        double cofactor_i=a*e-b*d;

        // Adjugate (transpose of cofactor matrix)
        temp.x[0]=cofactor_a;
        temp.x[1]=cofactor_d;
        temp.x[2]=cofactor_g;
        temp.x[3]=cofactor_b;
        temp.x[4]=cofactor_e;
        temp.x[5]=cofactor_h;
        temp.x[6]=cofactor_c;
        temp.x[7]=cofactor_f;
        temp.x[8]=cofactor_i;

        // Scale the adjugate by the inverse of the determinant
        for (int j=0; j<9; j++) temp.x[j]/=buf;

        // Update the current matrix with the inverse
        this->x=temp.x;
    }
}

void Matrix::gaussian(Matrix A,Matrix B) {
    if (A.m != A.n || A.m != 3 || B.m != 3 || B.n != 1 || this->m != 3 || this->n != 1) {
        cout <<"Invalid matrix dimensions. A should be 3x3, B should be 3x1, and X should be 3x1."<< endl;
        return;
    }

    // Step 1: Create an augmented matrix [A | B]
    Matrix augmented(3,4,0);
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            augmented.x.at(i*4+j)=A.x.at(i*3+j);  // Copy A's values
        }
        augmented.x.at(i*4+3)=B.x.at(i);  // Copy B's values
    }

    // Step 2: Perform Gaussian-Jordan elimination
    for (int i=0; i<3; i++) {
        // Ensure the pivot is non-zero by swapping rows if necessary
        if (augmented.x.at(i*4+i)==0) {
            bool swapped = false;
            for (int j=i+1; j<3; j++) {
                if (augmented.x.at(j*4+i)!=0) {
                    // Swap row i with row j
                    for (int k=0;k<4; k++) {
                        swap(augmented.x.at(i*4+k), augmented.x.at(j*4+k));
                    }
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                cout << "RREF cannot be achieved (matrix is singular)." << endl;
                return;
            }
        }

        // Step 3: Make the pivot element 1 by dividing the row by the pivot element
        double pivot = augmented.x.at(i*4+i);
        for (int j=0; j<4; j++) {
            augmented.x.at(i*4+j)/=pivot;
        }

        // Step 4: Eliminate the current column in other rows
        for (int j=0; j<3; j++) {
            if (j!=i) {  // Don't eliminate the pivot row itself
                double factor = augmented.x.at(j*4+i);
                for (int k=0; k<4; k++) {
                    augmented.x.at(j*4+k)-=factor*augmented.x.at(i*4+k);
                }
            }
        }
    }
    //uncomment this two lines to display the augmented matrix after RREF has been achieved
    //cout<<"augmented matrix after RREF"<<endl;
    //augmented.print();
    // Step 5: Extract the solution vector from the augmented matrix into *this (X)
    for (int i=0; i<3; i++) {
        this->x.at(i)=augmented.x.at(i*4+3);  // The solution is in the last column of the augmented matrix
    }
}
