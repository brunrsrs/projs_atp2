#include <stdio.h>
#include <math.h>

void serie (int, long double*);
long double termo1 (int);
long double termo2 (int);
long double termo3 (int, long double);
long double loc_P (long double, int);

int main () {
    int P;
    long double pi=0;

    printf ("Digite um valor P de acuracidade para pi: ");
    scanf (" %d", &P);

    serie(P, &pi);

    printf ("\n%.*Lf\n", P, 6*pi); //The series discover pi/6, so you need to multiply pi by 6

return 0;
}

void serie (int P_aux, long double *pi_aux)   {
    int contador=0, expoente=3; //"expoente" will be used in "termo 1" and "termo 2", "contador" will verify the accuracy
    int num_aux=1; //"num_aux" will be used on "termo 3" to keep the number's linearity
    long double aux_termo3=1; //"aux_termo3" will be used on "termo 3" to save the current value of the operation
    long double anterior;   //if "anterior" == pi until the decimal number P, "contador" +=1

    *pi_aux+=0.5;   //First call, the unique result possible is 1/2

    while (contador!=3) {
        anterior=loc_P(*pi_aux, P_aux);   //Saves pi actual value

        *pi_aux += (termo1(expoente) * termo2(expoente) * termo3(num_aux, aux_termo3)); //Calculate pi

        aux_termo3 = termo3(num_aux, aux_termo3); //"aux_termo" saves last "termo 3" value
        num_aux+=2;
        expoente+=2;    //increases their values to follow a pattern

        if (anterior == loc_P(*pi_aux, P_aux)) //Verify if there was any changes in "pi_aux" in decimal P
            contador++;
        else
            contador = 0;
            }
}

////////////////////////////////////////

long double termo1(int exp)   {
long double valor1;

    valor1 = pow(0.5, exp);

return (valor1);
}

////////////////////////////////////////

long double termo2(int exp)   {
long double valor2;

    valor2 = (1.0/exp);

return (valor2);
}

////////////////////////////////////////

long double termo3(int num, long double aux_termo)   {
long double valor3;

    valor3 = (long double)num/((long double)num+1) * aux_termo;

return (valor3);
}

////////////////////////////////////////

long double loc_P (long double ant_pi, int ant_P)   {
long double local;

    local = floor(ant_pi * pow(10.0,(long double)ant_P));

return (local);
}
