//a header file for the program, consists of the declaration of the class
using namespace std;

class histogram{
    //private part of the class, mainly just the elements or members of the class
    private:
    float bin[100]; // an array of floats for storing the bin values
    float freq[100];// an array of floats for storing the freq values
    int length=0;// an int to store the number of set of datas
    int state=0;// an int that is used as a flag

    //public part of the class, mainly the methods of the class
    public:
    void readHistFile(string argv);
    void printHistData();
    void plotHorizontalHist();
    void plotVerticalHist();
    void readTextFile(string argv);
    int gethiststate();
    void sethiststate(int newstate);
};
