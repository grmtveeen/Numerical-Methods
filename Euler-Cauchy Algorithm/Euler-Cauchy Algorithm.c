//Матвеев Игорь 118


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define L 1
#define Yo 1
#define I 10
#define Xo 0
#define Xstop 1
#define EPS 1e-5

double dif (double x, double y){
    return 2*x*y*L;
}
double adif (double x) {
    return Yo * exp (L * x * x);
}

void eiler1 (double dX){
    FILE *a;
    double Yn, Xn, Ynn;
    int i=0;
    a=fopen ("eiler 1.txt", "w");
    if (a==NULL) printf ("eiler 1 - NULL");
    Yn = Yo; Xn = Xo;
        fprintf (a, "%f\t%f\t%f\n",Xn, Yn, adif (Xn));
        for (i=0; i<(1/dX); i++){
//            Xn = Xo+i*dX;
            Ynn = Yn + dif(Xn,Yn)*dX;
            Yn=Ynn;
            Xn += dX;
            fprintf (a, "%f\t%f\t%f\n",Xn, Yn, adif (Xn));

        };
        fclose(a);
}





void eiler2 (double eps){
       FILE *a;
double Yn, Xn, Ynn, Ynp, e=0.1, YnP, YnnP, XnP, tochnost;
int i=0, k=0;
a=fopen ("eiler 2.txt", "w");
if (a==NULL) printf ("eiler 2 - NULL");
Yn = Yo, YnP=Yo, Xn=Xo, XnP=Xo;
    for (i=0; Xn<Xstop; i++){

        Ynn = Yn + dif(Xn,Yn)*e;
        Xn +=e;
        Yn=Ynn;


        tochnost = e/2;
        if (i!=0){
            for (k=0; k<2; k++){
            YnnP = YnP + dif(XnP,YnP)*tochnost;
            YnP=YnnP;
            XnP+=tochnost;
            }; k=0;
        };
       // printf ("%d\t%f\t%f\n", i ,Xn, Yn);
        if (fabs(YnP-Ynn)>eps) {
                e=e/2;
                Yn=Yo,  YnP = Yo;
                Xn= Xo, XnP=Xo;
                i=0;
                fclose(a);
                a=fopen ("eiler 2.txt", "w");
                if (a==NULL) printf ("eiler 2 - NULL");
                }
        else fprintf (a, "%f\t%f\t%f\n",Xn, Yn, adif(Xn));
};
fclose (a);
printf ("Eiler            %d\n", i);
};

void eiler_kochi1 (double dX){
    FILE *a;
    double Yn, Xn, Ynn;
    double Yn_n, Xn_n;
    int i=0;
    a=fopen ("eiler_kochi1.txt", "w");
    if (a==NULL) printf ("a=NULL");
    Yn = Yo;
    for (i=0; i<(1/dX); i++){
            Xn = Xo+i*dX;
            Ynn = Yn + dif(Xn,Yn)*dX;


    Xn_n = Xn+dX;
    Yn_n = Yn + (dif(Xn,Yn)+dif(Xn_n,Ynn))*dX/2;

            Yn=Ynn;



    fprintf (a, "%f\t%f\t%f\n",Xn_n, Yn_n,adif(Xn_n));

    };
     fclose(a);
}


void eiler_kochi2 (double eps){
    FILE *a;
    double Xn_n, Xn, Ynn, Yn_n, Yn, Xn_nP, XnP, YnnP, Yn_nP, YnP;
    double tochnost;
    int i=0,k=0;
    double e =0.1;
    a=fopen ("eiler_kochi2.txt", "w");
    if (a==NULL) printf ("eiler_kochi2 - NULL");
    Yn = Yo, Xn=Xo, YnP = Yo, XnP=Xo;
    for (i=0; Xn_n<Xstop; i++){

            Ynn = Yn + dif(Xn,Yn)*e;


            Xn_n = Xn+e;
            Yn_n = Yn + (dif(Xn,Yn)+dif(Xn_n,Ynn))*e/2;

            //Ynp=Yn;
            Yn=Yn_n;
            Xn+=e;
                tochnost = e/2;
                if (i!=0){
                    for (k=0; k<2; k++){
                    YnnP = YnP + dif(XnP,YnP)*tochnost;


                    Xn_nP = XnP+tochnost;
                    Yn_nP = YnP + (dif(XnP,YnP)+dif(Xn_nP,YnnP))*tochnost/2;

            //Ynp=Yn;
                    YnP=Yn_nP;
                    XnP+=tochnost;
                    }; k=0;
                };

               //printf ("%d\t%f\t%f\n", i ,Xn_n, Yn_n);
                if (fabs(Yn_n-Yn_nP)>eps){
                        e=e/2;
                        Yn=Yo, YnP=Yo;
                        Xn=Xo, XnP=Xo;
                        i=0;
                        fclose(a);
                        a=fopen ("eiler_kochi2.txt", "w");
                        if (a==NULL) printf ("eiler_kochi2 - NULL");

                        }
                else fprintf (a, "%f\t%f\t%f\n",Xn_n, Yn_n, adif(Xn_n));




    };
     fclose(a);
     printf ("Eiler - Kochi    %d", i);
}


int main (void){
double e = 0.1;
eiler1 (0.05);
eiler2 (EPS);
eiler_kochi1 (0.05);
eiler_kochi2 (EPS);
return 0;
}
