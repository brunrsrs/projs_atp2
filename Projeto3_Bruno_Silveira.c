#include <stdio.h>
#include <stdlib.h>

    //Prototypes
void recebe_valores(int*, int*, int, int);
void bubble_sort_decrescente(int*, int);
int remove_elemento(int*, int*);
void p_usados(int);
int balanca(int, int*, int);
int balanca_rec(int, int, int*, int);

    //Global variables
int p_salva[20];
int n_pesos=0;

    //Functions
int main()  {
    int N, M, *prod, *pesos;

    scanf ("%d %d", &N, &M);

    pesos = (int*)malloc(M * sizeof(int));
    prod = (int*)malloc(N * sizeof(int));

    recebe_valores(prod, pesos, M, N);  //Recieve the weights and products
    bubble_sort_decrescente(pesos, M);  //Organize in descending order

    printf ("\n");
    for (int i=0; i<N; i++) {
        n_pesos=0;
        if (balanca(prod[i], pesos, M)) {   //Caso seja retornado 1 para essa função, significa que achou solução
            bubble_sort_decrescente(p_salva, n_pesos);  //Organiza os vetores para facilitar visualização
            for (int j=0; j<n_pesos; j++)
                printf ("%d ", p_salva[j]); //Mostra os pesos usados
        printf ("\n");
        }

        else
            printf ("0\n"); //Caso nao seja encontrada resposta
    }

return 0;
}

    //Recebe os valores dos pesos e dos produtos
void recebe_valores(int *prod, int *pesos, int M, int N)  {

    printf ("\nDigite os valores dos pesos:\n");
    for (int i=0; i<M; i++)
    scanf ("%d", &pesos[i]);

    printf ("\nDigite os valores dos produtos:\n");
    for (int i=0; i<N; i++)
    scanf ("%d", &prod[i]);
}


    //Transforma o vetor em ordem decrescente
void bubble_sort_decrescente(int *vet, int M)   {
int aux;

    for (int i = 0 ; i < M-1; i++)
        for (int j=0 ; j<M-i-1; j++)
            if (vet[j] < vet[j+1])  {
        aux = vet[j];
        vet[j] = vet[j+1];
        vet[j+1] = aux;
        }
}

    //remove o elemento "0" de um vetor e retorna esse elemento (equivalente a pop() em python)
int remove_elemento(int *vet, int *posi)    {
int removido = *(vet);

    for (int i=0; i<(*posi); i++)
        *(vet+i) = *(vet+i+1);

    *posi= (*posi)-1;
return (removido);
}

    //armazena o vetor dos pesos usados
void p_usados(int valor) {  //Usado para facilitar a mostra de resultados
    p_salva[n_pesos] = valor;
    n_pesos++;
}

    //torna 0 o valor a direita da balança
int balanca(int Pi, int *pesos, int M)  {
    return balanca_rec(Pi, 0, pesos, M);
}

    //faz as operações recursivas
int balanca_rec(int esquerda, int direita, int *v_pesos, int M)   {
int vet_recebe[20], loc=M;  //Vetor do tamanho "máximo" pra receber os pesos e nao mudar os pesos originais

    for(int i=0; i<M; i++)  //Teste se a solução já não se encontra dentro dos vetores de pesos
        if (esquerda == *(v_pesos+i)) {
            printf ("%d", *(v_pesos+i));
            return 1;
        }

    for (int i=0; i<M; i++) //Passando os pesos originais para esse vetor auxiliar
        vet_recebe[i] = *(v_pesos+i);

    if ((esquerda == direita) || esquerda == 0) //Caso seja encontrada solução ou nao
        return 1;

    if (loc == 0)   //Contador chegando no valor minimo possivel
        return 0;

    int del = remove_elemento(vet_recebe, &loc);    //Equivalente a função pop() em python, retorna o valor vet[0] e o tira do vetor

    if (balanca_rec(esquerda+del, direita, vet_recebe, loc)==1) {   //Caso subtração da esquerda
        p_usados(-1*del);
    return 1;
    }

    if (balanca_rec(esquerda, direita, vet_recebe, loc)==1)  {  //Caso que ignora o peso
    return 1;
    }

    if (balanca_rec(esquerda, direita+del, vet_recebe, loc)==1) {   //Caso soma da esquerda
        p_usados(del);
    return 1;
    }

return 0;
}
