//the body of the program, contains the function definition of the class from the header file

#include<iostream>
#include <bits/stdc++.h>
#include <iomanip>
#include "functions.h"

//this function opens a file named the input and reads the numeric data from it
//and puts it into two arrays of floats, the bin and the freq
//this function will check for if the data in the file is an actual float or not and exiting if not
void histogram::readHistFile(string argv){
    // filestream variable file
    fstream file;
    string word;
    float buf;
    int k=0;

    // opening file
    file.open(argv);
    if (!file.is_open()){
        cout << "Failed to open the file " <<argv<< endl;
        state=0;
    }else{
        // extracting words from the file
        while (file >> word){
            //the atof() function converts the input from ASCII format to string format, hence a to f
            buf=atof(word.c_str());
            if (buf!=0.0 || (buf== 0.0 && word[0]=='0')){ //check if the conversion was successful by comparing the result to 0.0. If it's not equal to 0.0,
                                            // or if it's 0.0 and the first character in the input is '0', we consider the input to be convertible to a float.
                bin[k]=buf;
                file >> word; // scans for the freq value
                buf=atof(word.c_str());
                if (buf!=0.0 || (buf== 0.0 && word[0]=='0')){
                freq[k]=buf;
                }
                else {
                    cout<<"the input "<< word<<" is not able to be converted to float, terminating this part of the program "<<endl;//message when input is not float
                    state=-1;//changes the value of state to cancel function afterwards
                    break;
                }
            }
            else {
                cout<<"the input "<< word<<" is not able to be converted to float, terminating this part of the program "<<endl;
                state=-1;
                break;
            }
            k++;//increment index value
        }
        length=k;
        if (state==0){
            state=1;
        }
    }
    file.close();
}

//this function takes the values of bin and freq and prints it in a neatly manner
void histogram::printHistData(){
    //length is used to show the max number of datas
    for (int l=0;l!=length;l++){  //this for loop is used to ensure the data in bin and freq is correct
        cout<< setprecision(1)<< fixed; //formatting
        cout<<setw(5)<<bin[l]<<setw(8)<<freq[l]<<endl;
    }
}

//this function takes the data from the bin and freq and plots a horizontal histogram
void histogram::plotHorizontalHist(){
    float raw_data2; // a float that stores 2 times the freq value
    int amount;// initialisations
    for(int l=0;l!=length;l++){
        cout<<setw(4)<<bin[l]<<" /"<<setw(5)<<freq[l]<<" ";
        raw_data2=(freq[l])*2;//makes the number of * double
        if (raw_data2-floor(raw_data2)>0){ // used to make the value that has decimal to +1
            raw_data2+=1;
        }
        amount=(int)raw_data2;// assigns amount as int
        for (int p=1;p<=amount;p++){
            cout<<"*"; //prints the data in histogram style
        }
        cout<<endl;
    }
}

//this function takes the data from the bin and freq and plots a vertical histogram
void histogram::plotVerticalHist(){
//this function plots a vertical histogram
    int max=0;
    int amount[30];
    int number[30];//initialisations
    for(int l=0;l!=length;l++){
        amount[l]=(freq[l]);
        if(freq[l]-floor(freq[l])>0){
            amount[l]+=1;
        }//get the int value of freq, +1 if there is decimal value
    amount[l]=(int)amount[l];//assigns amount as int
        if (amount[l]>max){
            //determine the max amount of * in one column
            max=amount[l];
        }
        number[l]=(int)bin[l];//makes bin int via number
    }
    for (int row = max; row > 0; row--) {
        // the way the printing works is by checking whether the corresponding freq is >= to the row
        //which is first initialised to be the max and decrements every iteration
        //if the freq is >= to the row number, it prints * if not it leaves a blank space
        for (int i = 0; i < length; i++) {
            if (amount[i] >= row) {
                cout<<" *  ";
            } else {
                cout<<"    ";
            }
        }
        cout<<endl;
    }
    for (int i = 0; i < length; i++) {
        cout<<setw(2)<<number[i]<<"  ";
        //this loop prints the int value of bin in a neatly manner
    }
}

//this function takes a text file and records the length of each word and stores it in the
//correct bin and freq array
void histogram::readTextFile(string argv){
    fstream file;
    string word;
    int word_length;
    //initializing the freq array to ensure the value in it is known
    for (int i=0;i<100;i++){
        freq[i]=0;
    }
    file.open(argv);
    if (!file.is_open()){
            cout << "Failed to open the file " <<argv<< endl;
            state=-1;
        }else {
        while (file >> word){
            //scans for a string
            word_length=word.length();//obtain the length of string
            if (word_length <= 20){
                freq[word_length]+=1;
            }else {
                cout<<"the word "<<word<<" is longer than 20 characters long, the program is programmed to only handle words with 20 characters"<<endl;
                state=-1;
                break;
            }
            // increments the freq of set word length
        }
        file.close();
        if (state==0){
            state=1;
        }
    }
    for(int w=0;w!=100;w++){
        if (freq[w]!=0)length=w+1;
        // checks for what is the longest number of char a word has and assign the value to length
    }
    for (int k=0;k!=length;k++){
        bin[k]=k;
        // makes the bin value 0,1,2,3... until the word with the most chars
    }
}

//this function makes obtaining the value of the state of the histogram possible since the state variable is private
int histogram::gethiststate(){
    return state;
}

//this function makes changing the value of the state of the histogram possible since the state variable is private
void histogram::sethiststate(int newstate){
    state=newstate;
}
