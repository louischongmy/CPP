#include <iostream>

using namespace std;

class circuit{
private:
    double V,Ri,Rt,Pl,I,Rl,I2,Rl2;
    int disc;
public:
    //function declaration
    void discCheck(double Ri, double Rt, double Pl, double V);
    void calcRl();
    void calcI();
    void calc();
    void printAll();
    void help();

    //constructers
    circuit(){V=12;Ri=1;Rt=1;Pl=1;I=0;Rl=0;I2=0;Rl2=0;}//default constructor
    circuit(double V,double Ri, double Rt, double Pl){this->V=V;this->Ri=Ri;this->Rt=Rt;this->Pl=Pl;this->Rl=0;this->I=0;this->Rl2=0;this->I2=0;}//parameterised constructor

    //getters
    double getV(){return V;}
    double getRi(){return Ri;}
    double getRt(){return Rt;}
    double getPl(){return Pl;}
    double getI(){return I;}
    double getRl(){return Rl;}
    double getI2(){return I2;}
    double getRl2(){return Rl2;}


    //setters
    void setV(double V){this->V=V;}
    void setRi(double Ri){this->Ri=Ri;}
    void setRt(double Rt){this->Rt=Rt;}
    void setPl(double Pl){this->Pl=Pl;}

    //destructor
    ~circuit(){}
};
