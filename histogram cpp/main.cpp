//main function for a program that draws histograms based on hist files
//and calculates the number of alphabets in a word and does the same
//files are split into a functions file and a header file to promote modularity

#include <iostream>
#include <cstring>
#include "functions.h"

using namespace std;

int main(int argc, char **argv){
    //creating variable of type histogram
    histogram histnum;
    histogram histtext;

    //a for loop used to check if the user command input contains the relevant files and passes it on
    for(int i=1;i!=argc;i++){
        //if loop used to check if the specific file name is correct
        if (strcmp(argv[i],"inputFile.hist")==0 || strcmp(argv[i],"inputFile.txt")==0){
            //part 1 of the program
            if (strcmp(argv[i],"inputFile.hist")==0){
                cout<<"===========Part 1(data)==========="<<endl;
                histnum.readHistFile(argv[i]);
            }

            //if the reading of the file is correctly done, execute the next part, which consists of printing the datas
            if (histnum.gethiststate()==1){
                histnum.printHistData();
                cout<<endl<<endl;
                histnum.plotHorizontalHist();
                cout<<endl<<endl;
                histnum.plotVerticalHist();
                cout<<endl<<endl;
                histnum.sethiststate(0);
            }

            //part 2 of the program
            if (strcmp(argv[i],"inputFile.txt")==0){
                cout<<"===========Part 2(text)==========="<<endl;
                histtext.readTextFile(argv[i]);
            }
            if (histtext.gethiststate()==1){
                histtext.printHistData();
                cout<<endl<<endl;
                histtext.plotHorizontalHist();
                cout<<endl<<endl;
                histtext.plotVerticalHist();
                cout<<endl<<endl;
                histtext.sethiststate(0);
            }
        }
        //error message
        else cout<<"cannot open "<<argv[i]<<endl;
    }
    return 0;
}
