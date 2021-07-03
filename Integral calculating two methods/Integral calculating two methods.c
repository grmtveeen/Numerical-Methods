#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-6            //Epsilon (Infinitesimal)
#define Xleft -1            //Left border of the range
#define Xright 2            //Right border of the range

double f (double x){        //Function on X
    return x/(1+(x*x*x*x));
};

double trapeze (double left, double right, int splitting){ //Integral trapezoidal method
    double y = 0, dX;
    int i = 1;
    dX = (right - left) / splitting;
    while (splitting > i) y += f(left + i * dX), i++;
return dX * (y + (f(left) + f(right)) / 2);
};


double simpson (double left, double right, int splitting){  //Simpson's method calculating integral
    double y = 0, Xn, dX;
    int i=0;
    dX = (right - left) / splitting;
    while (splitting > i){
        Xn = left + dX * i;
        y += (f(Xn) + 4 * f(Xn + dX / 2) + f(Xn +  dX)), i++;
    };
return (dX/6)*y;
};


int main (void){
    int splitting = 1;

    //Here the program chooses the smallest partition for which the integral is calculated with a given accuracy for the Simpson's method
    printf("Simpson's method calculating integral:\n");
    for (splitting = 2; fabs(simpson(Xleft, Xright, splitting) - simpson(Xleft, Xright, splitting * 2)) > EPS; splitting *= 2){
        printf ("Splitting on %3d \t Value %f\n", splitting, simpson(Xleft, Xright, splitting));
    };

    //Here the program chooses the smallest partition for which the integral is calculated with a given accuracy for the trapezoidal method
    printf ("\n\nIntegral trapezoidal method:\n");
    for (splitting = 2; fabs(trapeze(Xleft, Xright, splitting) - trapeze(Xleft, Xright, splitting * 2)) > EPS; splitting *= 2){
        printf ("Splitting on  %3d \t Value %f\n", splitting, trapeze(Xleft, Xright, splitting));
    };

    return 0;
}
