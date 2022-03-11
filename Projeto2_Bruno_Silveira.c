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

    printf ("\n%.*Lf\n", P, 6*pi);

return 0;
}

void serie (int P_aux, long double *pi_aux)   {
    int contador=0, expoente=3; //expoente sera usado nos termos 1 e 2, contador para verificar acuracidade
    int num_aux=1; //num_aux será utilizado no termo 3 para seguir a linearidade da contagem
    long double aux_termo3=1; //aux_termo3 será utilizado no termo 3 para armazenar o valor obtido para a prox operação
    long double anterior;   //caso o anterior seja igual ao pi até a casa decimal P, contador +=1

    *pi_aux+=0.5;   //Primeira chamada onde o unico parametro é 1/2

    while (contador!=3) {
        anterior=loc_P(*pi_aux, P_aux);   //Armazena o valor atual de pi

        *pi_aux += (termo1(expoente) * termo2(expoente) * termo3(num_aux, aux_termo3)); //Operação que calcula pi/6

        aux_termo3 = termo3(num_aux, aux_termo3); //aux_termo armazena o valor anterior para termo 3
        num_aux+=2;
        expoente+=2;    //aumenta os respectivos valores para seguir o padrão

        if (anterior == loc_P(*pi_aux, P_aux)) //Verificação se houve mudança até certa casa decimal P
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

long double termo3(int num, long double aux_termo)   { //nao foi passado por referencia devido a necessidade de chamar novamente essa função pro aux_termo
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