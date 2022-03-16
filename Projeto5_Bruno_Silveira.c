#include <stdio.h>
#include <time.h>

//struct global
typedef struct biggo    {
    int high, low;
}   BigInt;

//protótipos
void selection_sort(BigInt*);
void Shell_Sort(BigInt*);

//funções
int main()  {
FILE *entrada, *saida;
clock_t inicio, fim;    //função que calculará o tempo das operações

BigInt vetor[200000];

entrada = fopen("bigint.dat", "r");
saida = fopen("shell.dat", "w");


    for (int i=0; i<200000; i++)
        fscanf(entrada, "%d %d\n", &vetor[i].high, &vetor[i].low);

/*  //Essa parte deixei comentada pois ela é usada só para comparação e altera o resultado do tempo
    //do shell. Entretanto, caso queira testa-lá, apenas tirar o /* dessa linha e o da linha 38 

    //marca o timer para o select
    inicio = clock();

    selection_sort(&vetor[0]);
    
    fim = clock();

    printf("\nselection sort:\ntempo decorrido = %lf segundos\n\n", (double) (fim - inicio) / CLOCKS_PER_SEC);
*/

    //marca o timer pro shell
    inicio = clock();

    Shell_Sort(&vetor[0]);
    
    fim = clock();

    printf("\nshell sort:\ntempo decorrido = %lf segundos\n\n", (double) (fim - inicio) / CLOCKS_PER_SEC);

    //mostra os valores ordenados pelo shell para o programa
    for (int i=0; i<200000; i++)
        fprintf(saida, "%d %d\n", vetor[i].high, vetor[i].low);

    fclose(entrada);
    fclose(saida);

return 0;
}

//função selection sort
void selection_sort(BigInt *vetor) {
int menor;
int aux_high, aux_low;

    for (int loc = 0; loc < 199999; loc++) {
        menor = loc;
    for (int i = loc + 1; i < 200000; i++){
        if ((vetor+i)->high < (vetor+menor)->high)
            menor = i;

        else if ((vetor+i)->high == (vetor+menor)->high)    {
        if ((vetor+i)->high > 0)
            if ((vetor+i)->low < (vetor+menor)->low)
                menor = i;
        
        else
            if ((vetor+i)->low > (vetor+menor)->low)
                menor = i;
        }
    }

    //troca os valores high
    aux_high = (vetor+menor)->high;
    (vetor+menor)->high = (vetor+loc)->high;
    (vetor+loc)->high = aux_high;
    //troca dos valoes low
    aux_low = (vetor+menor)->low;
    (vetor+menor)->low = (vetor+loc)->low;
    (vetor+loc)->low = aux_low;
  }
}

//função shell sort
void Shell_Sort(BigInt *vetor) {
int j, passo, aux_high, aux_low;

    while (passo<200000/2)
        passo = 3*passo + 1;

    while (passo!=1)    {
        passo=passo/3;
        for (int l=0;l<passo; l++)  {
            for (int i = l+passo; i<200000; i+=passo) {
                aux_high = (vetor+i)->high;
                aux_low = (vetor+i)->low;
                j = i;

            while ((j-passo>=0) && ((vetor+j-passo)->high > aux_high)) {
                (vetor+j)->low = (vetor+j-passo)->low;
                (vetor+j)->high = (vetor+j-passo)->high;
                j-=passo;
                }

            while ((j-passo>=0) && ((vetor+j-passo)->high == aux_high) && ((vetor+j-passo)->high >= 0) && ((vetor+j-passo)->low > aux_low)) {
                    (vetor+j)->low = (vetor+j-passo)->low;
                    (vetor+j)->high = (vetor+j-passo)->high;
                    j-=passo;
                }
            while ((j-passo>=0) && ((vetor+j-passo)->high == aux_high) && ((vetor+j-passo)->high < 0) && ((vetor+j-passo)->low < aux_low)) {
                    (vetor+j)->low = (vetor+j-passo)->low;
                    (vetor+j)->high = (vetor+j-passo)->high;
                    j-=passo;
            }

            (vetor+j)->high = aux_high;
            (vetor+j)->low = aux_low;
            }
        }
    }
}