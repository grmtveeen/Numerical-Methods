//Matveev Igor

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define L 1         //Parameter lambda
#define Yo 1        //Initial condition
#define Xo 0        //Initial condition and left border of the range
#define Xstop 1     //Right border of the range
#define EPS 1e-5    //Epsilon (Specified accuracy)

double f (double x, double y){
    return 2*x*y*L;
}
double analytical (double x) {
    return Yo * exp (L * x * x);
}

void Euler1 (double dX){ //Euler's method (given step)
    FILE *a;
    double Yn = Yo, Xn = Xo, Ynn;
    int i=0;
    a = fopen ("Eiler1.txt", "w");
    if (a==NULL) {printf ("Eiler1.txt NULL"); exit(2);}
    fprintf (a, "%f\t%f\t%f\n",Xn, Yn, analytical (Xn));
    for (i=0; i<(1/dX); i++){
        Ynn = Yn + f(Xn,Yn)*dX;
        Yn=Ynn;
        Xn += dX;
        fprintf (a, "%f\t%f\t%f\n",Xn, Yn, analytical (Xn));
    };
    fclose(a);
}

void Euler2 (double eps){   //Euler's method (specified accuracy)
    FILE *a;
    double Yn, Ynn, YnP, YnnP, Xn, XnP, splitting1 = 0.1, splitting2;   //XnP, YnP, YnnP the same that Xn, Yn, Ynn but just for checking greater partitioning.
    int i = 0, k = 0;
    a = fopen ("Euler2.txt", "w");
    if (a == NULL) {printf ("Euler2.txt NULL"); exit(2);}
    Yn = Yo, YnP = Yo, Xn = Xo, XnP = Xo;
    for (i = 0; Xn < Xstop; i++){

        Ynn = Yn + f(Xn, Yn) * splitting1;  //It is Euler's method with splitting = splitting1.
        Xn += splitting1;
        Yn = Ynn;

        splitting2 = splitting1/2;
        if (i != 0){                //It is Euler's method with splitting = splitting1 / 2.
            for (k = 0; k < 2; k ++){
            YnnP = YnP + f(XnP, YnP) * splitting2;
            YnP = YnnP;
            XnP += splitting2;
            }; k = 0;
        };
        //Here we compare the result with splitting splitting1 and splitting1 / 2. If this condition is met we have to delete all data and start again with splitting = splitting1/2.
        if (fabs(YnP - Ynn) > eps) {
            splitting1 = splitting2;
            Yn = Yo,  YnP = Yo;
            Xn = Xo, XnP = Xo;
            i = 0;
            fclose(a);
            a = fopen ("Euler2.txt", "w");
            if (a == NULL) {printf ("Euler2.txt NULL"); exit(2);}
        }
        else fprintf (a, "%f\t%f\t%f\n", Xn, Yn, analytical(Xn));
    };
    fclose (a);
    printf ("The method Euler took        %d steps to achieve the specified accuracy\n", i);
};

void EulerCauchy1 (double dX){  //Euler - Cauchy method (given step)
    FILE *a;
    double Yn = Yo, Xn, Ynn;
    double Yn_n, Xn_n;
    int i = 0;
    a = fopen ("EulerCauchy1.txt", "w");
    if (a == NULL) {printf ("EulerCauchy1.txt NULL");exit(2);}
    for (i = 0; i < (1 / dX); i++){
        Xn = Xo + i * dX;
        Ynn = Yn + f(Xn, Yn) * dX;

        Xn_n = Xn + dX;
        Yn_n = Yn + (f(Xn, Yn) + f(Xn_n, Ynn)) * dX / 2;
        Yn = Ynn;

        fprintf (a, "%f\t%f\t%f\n", Xn_n, Yn_n, analytical(Xn_n));
    };
    fclose(a);
}

void EulerCauchy2 (double eps){
    FILE *a;
    double Xn_n, Xn, Ynn, Yn_n, Yn, Xn_nP, XnP, YnnP, Yn_nP, YnP; //XnP, Xn_nP, YnP, Yn_nP, YnnP the same that Xn_n, Xn, Ynn, Yn_n, Yn but just for checking greater partitioning.
    int i = 0;
    double splitting1 = 0.1,splitting2;
    a = fopen ("EulerCauchy2.txt", "w");
    if (a==NULL) {printf ("EulerCauchy2 NULL");exit(2);}
    Yn = Yo, Xn = Xo, YnP = Yo, XnP = Xo;
    for (i = 0; Xn_n < Xstop; i++){

        Ynn = Yn + f(Xn,Yn)*splitting1; //It is Euler Cauchy method with splitting = splitting1.

        Xn_n = Xn+splitting1;
        Yn_n = Yn + (f(Xn, Yn) + f(Xn_n, Ynn)) * splitting1 / 2;

        Yn = Yn_n;
        Xn += splitting1;


        splitting2 = splitting1 / 2;    //It is Euler Cauchy method with splitting = splitting1 / 2.
        if (i != 0){
            for (int k = 0; k < 2; k++){
            YnnP = YnP + f(XnP, YnP) * splitting2;


            Xn_nP = XnP + splitting2;
            Yn_nP = YnP + (f(XnP, YnP) + f(Xn_nP, YnnP)) * splitting2 / 2;

            YnP = Yn_nP;
            XnP += splitting2;
            };
        };
        //Here we compare the result with splitting splitting1 and splitting1 / 2. If this condition is met we have to delete all data and start again with splitting = splitting2.
        if (fabs(Yn_n - Yn_nP) > eps){
            splitting1 = splitting2;
            Yn = Yo, YnP = Yo;
            Xn = Xo, XnP = Xo;
            i = 0;
            fclose(a);
            a = fopen ("EulerCauchy2.txt", "w");
            if (a == NULL) {printf ("EulerCauchy2 NULL");exit(2);}
        }
        else fprintf (a, "%f\t%f\t%f\n",Xn_n, Yn_n, analytical(Xn_n));
    };
    fclose(a);
    printf ("The method Euler Cauchy took %d steps to achieve the specified accuracy\n", i);
}

int main (void){
    Euler1 (0.05);
    Euler2 (EPS);
    EulerCauchy1 (0.05);
    EulerCauchy2 (EPS);
    return 0;
}
