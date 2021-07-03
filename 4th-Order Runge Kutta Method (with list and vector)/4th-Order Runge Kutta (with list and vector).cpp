//Matveev Igor

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

#define PI 3.14159265358979323846
#define L -1.5          //Parameter lambda.
#define Xleft 0         //Left border of the range.
#define Xright 2*PI     //Right border of the range.
#define Yfirst -1.0     //Initial condition.
#define deltaX 0.1      //Accuracy (step) of the solution.


double solution (double X, double Yo){  //Analytical solution.
    return (L*sin(X)+Yo);               //Yo is constant after integration.
}

double f (double X, double Y){          //This is the value of the function f at the point (x, y).
    return (L*cos(X));
}


void RungeKutt (double dX, double X1, double X2, double Yo){
    double X = X1, Y = Yo, Yn, k1, k2, k3, k4; // Yn - it is "Y next".
    ofstream ofile;
    vector<double> Func;            //Function value calculating.
    vector<double> :: iterator ff;  //Function value calculating iterator.
    vector<double> FuncS;           //Function value (analytical solution).
    vector<double> :: iterator fs;  //Function value (analytical solution) iterator.
    list<double> arg;               //Argument.
    list<double> :: iterator a;     //Argument iterator.
    while (X <= X2){
        k1 = f(X,Y);
        k2 = f(X + (dX/2),Y + ((dX / 2) * k1));
        k3 = f(X + (dX/2),Y + ((dX / 2) * k2));
        k4 = f(X + dX, Y + (dX * k3) );
        Yn = Y + (dX / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        arg.push_back(X);
        Func.push_back(Y);
        FuncS.push_back(solution(X,Yo));
        Y = Yn, X += dX;
    }
    ofile.open ("calculations.txt", ios_base::out);
    if(!ofile) {
            cerr<<"Error: file didn't open."<<endl;exit(2);
    }
    ff = Func.begin();
    fs = FuncS.begin();
    for (a = arg.begin(); a != arg.end(); a++, ff++, fs++){
        ofile << setw(5) << *a << "    " << setw(12) << *ff << "    " << setw(12) << *fs << endl;
    }
    ofile.close();
}


int main (void){
    RungeKutt(deltaX, Xleft, Xright, Yfirst);
    return 0;
}
