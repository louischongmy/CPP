//functions file for the program
//mainly includes the method definition in the header file
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <sstream>
#include "functions.h"

using namespace std;


int convert(int x){
    //func that converts 0,1,2 from ascii to int
    if (x==48)x=0;
    else if(x==49)x=1;
    else x=2;
    return x;
}

void Matrix::print(){
    cout<<"======================="<<endl;//formatting
    for (int i=0;i<3;i++) {//iterating each element in the array
        cout<<"|";//formatting
        for (int j=0;j<3;j++) {
            cout<<setprecision(2)<<fixed<<setw(7)<<x[i][j];//printing
        }
        cout<<" |"<<endl;//formatting
    }
    cout<<"======================="<<endl;//formatting
}

void Matrix::set(double A, double B, double C, double D, double E, double F, double G, double H, double I){
    x[0][0]=A;
    x[0][1]=B;
    x[0][2]=C;
    x[1][0]=D;
    x[1][1]=E;
    x[1][2]=F;
    x[2][0]=G;
    x[2][1]=H;
    x[2][2]=I;//just straight assigning since a lot of inputs and due to the way the inputs are handled
}

void Matrix::set(int m, int n, double A){
    x[m-1][n-1]=A;//-1 is to take into account that humans start counting from 1
}

double Matrix::get(int m, int n){
    return x[m-1][n-1];//-1 is to take into account that humans start counting from 1
}

void Matrix::transpose(){
    double temp[3][3];//creating a temp array with the size of the matrix
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            temp[i][j]=x[i][j];//transposing
        }
    }
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            x[i][j]=temp[j][i];//getting back the values from temp
        }
    }
}

void Matrix::eye(){
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (i==j){//diagonal check
                x[i][j]=1;
            }
            else x[i][j]=0;
        }
    }
}

void Matrix::zero(){
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            x[i][j]=0;//iterating each elements and set to 0
        }
    }
}

void Matrix::save(string filename){
    fstream file;//create filestream
    file.open(filename);//open file
    if (!file.is_open()){//check if file is opened correctly
        cout << "Failed to open the file " <<filename<< endl;//error message
    }else{
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
            file<<setprecision(2)<<fixed<<setw(7)<<x[i][j];//writing to file with formatting
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
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (file>>word){//reading from file
                    buf=atof(word.c_str());//ascii to float into buffer
                    if (buf!=0.0 || (buf== 0.0 && word[0]=='0')){//checking to ensure input is float
                    x[i][j]=buf;//insertion
                    }
                else cout<<"the input "<<word<<" is not a float, converting it to 0.00"<<endl;//error message
                }
            }
        }
    }
    file.close();//closing the file
}

void Matrix::add(Matrix B){
    for (int i=0;i<3;i++) {//iterating
        for (int j=0;j<3;j++) {
            x[i][j]=x[i][j]+B.x[i][j];//adding
        }
    }
}

void Matrix::sub(Matrix B){
    for (int i=0;i<3;i++) {//iterating
        for (int j=0;j<3;j++) {
            x[i][j]=x[i][j]-B.x[i][j];//substracting
        }
    }
}

double Matrix::rcMult(Matrix B, int row, int col){
    return ((x[row-1][0]*B.x[0][col-1])+(x[row-1][1]*B.x[1][col-1])+(x[row-1][2]*B.x[2][col-1]));//-1 is to account for human, refer to report for alg logic
}

void Matrix::lMult(Matrix B){
    double temp[3][3];//creating temp as buffer
    for (int i=0;i<3;i++) {//iterating
        for (int j=0;j<3;j++) {
                temp[i][j]=((B.x[i][0]*x[0][j])+(B.x[i][1]*x[1][j])+(B.x[i][2]*x[2][j]));//calc, refer to report for alg logic
        }
    }
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            x[i][j]=temp[i][j];//insertion
        }
    }
}

void Matrix::rMult(Matrix B){
    double temp[3][3];
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
                temp[i][j]=((x[i][0]*B.x[0][j])+(x[i][1]*B.x[1][j])+(x[i][2]*B.x[2][j]));//calc
        }
    }
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            x[i][j]=temp[i][j];//insertion
        }
    }
}

void Matrix::sMult(double s){
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            x[i][j]=x[i][j]*s;//s is the scalar
        }
    }
}

double Matrix::det(){
    return ((x[0][0]*x[1][1]*x[2][2])+(x[0][1]*x[1][2]*x[2][0])+(x[0][2]*x[1][0]*x[2][1])-(x[0][0]*x[1][2]*x[2][1])-(x[0][1]*x[1][0]*x[2][2])-(x[0][2]*x[1][1]*x[2][0]));
    //calc logic is based on lab sheet
}

void Matrix::inv(){
    double buf=det();//find the det of said matrix
    if (buf==0){
        cout<<"the matrix is singular and does not have an inverse."<<endl;//if the det is 0 there is no inv
    }else{//calc for inv if det is not 0
        double temp[3][3];//create buffer
        int a,b,c,d;//create placeholders
        const char lookup[]="012012";//string manip for minor
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {//iterating
                a=convert(lookup[i+1]);
                b=convert(lookup[i+2]);
                c=convert(lookup[j+1]);
                d=convert(lookup[j+2]);//calcing the values to be used for indexing, refer to report for alg logic
                temp[i][j]=(x[a][c]*x[b][d])-(x[a][d]*x[b][c]);//calcing minor
            }
        }

        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                x[i][j]=temp[i][j];//replacing buffer
            }
        }
        transpose();//transposing
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                x[i][j]=x[i][j]/buf;//dividing by det
            }
        }
    }
}
