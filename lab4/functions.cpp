#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "functions.h"

using namespace std;

// Function to check the discriminant of the quadratic equation
// This helps determine whether the quadratic equation has real solutions
void circuit::discCheck(double Ri, double Rt, double Pl, double V){
    double b=2*(Ri+Rt)-(V*V)/Pl; // Coefficient 'b' in the quadratic equation
    double a=1.0;  // Coefficient 'a' in the quadratic equation (always 1)
    double c =(Ri+Rt)*(Ri+Rt); // Coefficient 'c' in the quadratic equation

    // Calculate the discriminant (b^2 - 4ac) and classify the discriminant
    if (b*b-4*a*c>0)disc = 1;// Two real solutions exist
    else if (b*b-4*a*c ==0.0)disc=0;// One real solution exists (discriminant is zero)
    else{disc=-1;}// No real solutions exist (discriminant is negative)
};

// Function to calculate the load resistance (Rl) based on the discriminant
void circuit::calcRl(){
    double b=Ri+Ri+Rt+Rt-(V*V)/Pl; // Coefficient 'b' for the quadratic formula
    double a=1.0; // Coefficient 'a' (same as before)
    double c=(Ri+Rt)*(Ri+Rt); // Coefficient 'c' for the quadratic formula
    double temp; // Temporary variable to store the solution

    // If the discriminant indicates two real solutions
    if (disc == 1){
        // Calculate the first solution using the quadratic formula
        temp=(-b+sqrt(b*b-4*a*c))/(2*a);
        if (temp > 0)Rl=temp; // Only assign Rl if the solution is positive
        // Calculate the second solution using the quadratic formula
        temp=(-b-sqrt(b*b-4*a*c))/(2*a);
        if (temp>0)Rl2=temp; // Only assign Rl2 if the solution is positive
    }
    // If there is only one solution (discriminant is zero)
    if (disc==0)Rl=-b/(2*a); // Only one solution for Rl
};

// Function to calculate the current (I) based on the load resistance
void circuit::calcI(){
    // If both Rl and Rl2 are non-zero, calculate two currents
    if (Rl!=0&&Rl2!=0){
        I=V/(Ri+Rt+Rl);  // First current
        I2=V/(Ri+Rt+Rl2); // Second current
    }
    // If only Rl is non-zero, calculate only one current
    if (Rl!=0&&Rl2==0){
        I=V/(Ri+Rt+Rl); // Only one current
    }
};

// Function to print all the results (voltage, resistances, currents, etc.)
void circuit::printAll(){
    cout<<fixed;  // Use fixed-point notation for floating-point output
    // Print separator line
    cout<<string(18,'=')<< endl;
    // Print all values with formatting (3 digits of precision)
    cout<<"| V:   "<<setprecision(3)<<setw(9)<<V<<" |"<< endl;
    cout<<"| Ri:  "<<setprecision(3)<<setw(9)<<Ri<<" |"<< endl;
    cout<<"| Rt:  "<<setprecision(3)<<setw(9)<<Rt<<" |"<<endl;
    cout<<"| Pl:  "<<setprecision(3)<<setw(9)<<Pl<<" |"<<endl;
    cout<<"| Rl:  "<<setprecision(3)<<setw(9)<<Rl<<" |"<<endl;
    cout<<"| I:   "<<setprecision(3)<<setw(9)<<I<<" |"<<endl;
    // If there are two possible values for Rl, print both of them along with their currents
    if (disc != 0) {
        cout<<"| Rl2: "<<setprecision(3)<<setw(9)<<Rl2<<" |"<< endl;
        cout<<"| I2:  "<<setprecision(3)<<setw(9)<<I2<<" |"<<endl;
    }
    // Print separator line
    cout << string(18, '=') << endl;
}

// Main function to orchestrate the calculations and printing
void circuit::calc(){
    // Check the discriminant to determine the number of solutions
    discCheck(Ri, Rt, Pl, V);

    // If the discriminant is valid (i.e., there are real solutions)
    if (disc > -1) {
        calcRl(); // Calculate Rl values based on the discriminant
        calcI();  // Calculate currents based on Rl values
        printAll(); // Print the results
    }
    else cout << "The set of values does not make sense" << endl;// If the discriminant is negative, no real solutions exist
}

void circuit::help() {
    cout << string(40, '=') << endl;
    cout << "HELP: Description of Circuit Elements" << endl;
    cout << string(40, '=') << endl;

    // Describe each element
    cout << "V  : Voltage source in the circuit (in volts).\n";
    cout << "Ri : Internal resistance of the voltage source (in ohms).\n";
    cout << "Rt : Resistance of the transmission line (in ohms).\n";
    cout << "Pl : Power consumed by the load (in watts).\n";
    cout << "Rl : Load resistance calculated to satisfy the circuit.\n";
    cout << "Rl2: Second possible load resistance (if applicable).\n";
    cout << "I  : Current flowing through the circuit for Rl (in amperes).\n";
    cout << "I2 : Current flowing through the circuit for Rl2 (if applicable).\n";
    cout << string(40, '=') << endl;

    // Describe the calc() function
    cout << "The calc() function performs the following steps:\n";
    cout << "1. Computes the discriminant of the quadratic equation\n";
    cout << "   to determine the number of valid solutions.\n";
    cout << "2. Calculates the load resistance(s) (Rl and Rl2).\n";
    cout << "3. Computes the current(s) (I and I2) for the circuit.\n";
    cout << "4. Prints all computed values in a readable format.\n";
    cout << string(40, '=') << endl;
}
