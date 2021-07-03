//Matveev Igor
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define EPS 1e-6                //Epsilon (Infinitesimal)
#define A 1                     //Left border of the range
#define B 1.5                   //Right border of the range

double df (double x){           //Derivative of a function
    return (cos( (x + EPS) * (x + EPS)) - cos((x - EPS) * (x - EPS))) / (2 * EPS);
};

double f (double x) {           //Function value
    return cos(x * x);
};

void Binary_Newton (double a, double b){ //Comparison binary search and Newton's method
    double x, Xnn = 3 * EPS, Xn = b, X = EPS;
    while (b - a > EPS){        //Binary search (dihotomia)
        x =((b - a) / 2) + a;
        if ((cos(x * x) < 0) && (cos(a * a) > 0) && (cos (b * b) < 0)) b = x;
        else a = x;
    };
    printf ("Binary search:\t\tX = %.16e\n", x);

    while( fabs(Xnn - X) > EPS){ //Newton's method
       X = Xn;
       Xnn = Xn - (f(Xn) / df(Xn));
       Xn = Xnn;
    };
    printf ("Newton's method:\tX = %.16e\n\n\n", Xnn);
};

int  main (void) {
    Binary_Newton (A,B);
    return 0;
}
