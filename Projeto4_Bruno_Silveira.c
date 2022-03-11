#include <stdio.h>
#include <stdlib.h>

//estrutura que armazenará os valores
typedef struct armazena_pessoas {
    int idade, instante, tempo;
    struct armazena_pessoas *anterior;
    struct armazena_pessoas *proximo;
} lista_pessoas;

lista_pessoas *head;
int tamanho;

//estrutura que marca a fila do caixa
typedef struct fila_caixa   {
    int idade_caixa, instante_caixa, tempo_caixa;
    struct fila_caixa *anterior;
    struct fila_caixa *proximo;
} f_caixa;

f_caixa *cabeca;

//prototipos de funções
void inicializa_lista();    //operações com a lista
void insere_lista(lista_pessoas**);
void remove_elem_lista(lista_pessoas**);

void insere_fila(f_caixa**, lista_pessoas*);    //operações com a fila
void inserir_prioridade(f_caixa**, lista_pessoas*); 
void remove_elem_fila(f_caixa**);
void exibe_fila(f_caixa*);

void caixa(int, lista_pessoas*);   //operação do caixa
int caixa_disponivel(int*, int);

//funções
int main()  {
int N, M; //numero de pessoas e caixas disponíveis
lista_pessoas *LISTA = NULL;

    scanf("%d %d", &N, &M); //recebe o numero de pessoas e o numero de caixas
    inicializa_lista();

    for (int i=0; i<N; i++) //recebe e coloca os valores em ordem crescente de tempo de chegada
    insere_lista(&LISTA);

    caixa(M, LISTA);

printf("\n");
return 0;
}

//função que inicializa a lista_pessoas
void inicializa_lista()  {
head = NULL;
tamanho = 0;

cabeca = NULL;
}

//função que insere ordenadamente elementos na fila
void insere_lista(lista_pessoas **LISTA)  {
lista_pessoas *aux, *novo = malloc(sizeof(lista_pessoas));

    scanf("%d %d %d", &novo->idade, &novo->instante, &novo->tempo); //recebe valores

    if (*LISTA == NULL)   {   //caso lista esteja vazia
        novo->anterior = head;
        *LISTA = novo;
        tamanho++;
    }

    else if(novo->instante <= (*LISTA)->instante)  { //caso seja menor que o primeiro valor inserir no 1° elem
        novo->proximo = *LISTA;
        novo->anterior = head;
        *LISTA = novo;
        tamanho++;
    }

    else    {   //inserir no meio/fim da lista
    aux = *LISTA;
    
    while ((aux->proximo!=NULL) && (novo->instante > aux->proximo->instante))
        aux = aux->proximo;
    
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    tamanho++;
    }
}

//função que remove um elemento da lista
void remove_elem_lista(lista_pessoas **LISTA)  {
lista_pessoas *removido;

    if (*LISTA != NULL) {
    removido = *LISTA;
    *LISTA = (*LISTA)->proximo;
    head = *LISTA;
    free (removido);
    tamanho--;
    }

}

//função que insere no final da fila
void insere_fila(f_caixa **FILA, lista_pessoas *LISTA)  {
    f_caixa *aux, *novo;
    
    novo = malloc(sizeof(f_caixa));

    novo->idade_caixa = LISTA->idade;
    novo->instante_caixa = LISTA->instante;
    novo->tempo_caixa = LISTA->tempo;
    novo->proximo = NULL;
    
    if (*FILA == NULL)   {   //caso a fila esteja vazia
        *FILA = novo;
        cabeca = *FILA;
    }

    else    {   //inserindo no final da fila
        aux = *FILA;
        while (aux->proximo != NULL)
            aux = aux->proximo;

        aux->proximo = novo;
    }
}

//função que insere com prioridade no caixa
void inserir_prioridade(f_caixa **FILA, lista_pessoas *LISTA) {
    f_caixa *aux, *novo = malloc(sizeof(f_caixa));
    
    novo->idade_caixa = LISTA->idade;
    novo->instante_caixa = LISTA->instante;
    novo->tempo_caixa = LISTA->tempo;

    if (*FILA == NULL)  {  //caso esteja vazia
        novo->anterior = cabeca;
        novo->proximo = NULL;
        *FILA = novo;
        cabeca = *FILA;
    }

    else    {
        if ((*FILA)->idade_caixa < novo->idade_caixa)   {   //inserir no primeiro elemento
            novo->proximo = *FILA;
            novo->anterior = cabeca;
            *FILA = novo;
            cabeca = *FILA;
        }

        else    {   //inserir no resto caso o 1° elem seja mais velho
            aux = *FILA;
            
            while ((aux->proximo != NULL) && (novo->proximo->idade_caixa > aux->idade_caixa))
                aux = aux->proximo;
            
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    }

}

//função que remove um elemento da fila
void remove_elem_fila(f_caixa **FILA) {
f_caixa *removido;

if ((*FILA) != NULL)    {
    removido = *FILA;
    *FILA = (*FILA)->proximo;
    cabeca = *FILA;
    free (removido);
    }

}

//função que exibe a fila do caixa
void exibe_fila(f_caixa *FILA)  {
f_caixa *aux;

printf("\n");
    aux = FILA;
    if (aux == NULL)
        printf("NULL");
    else
        while (aux!=NULL)   {
            printf ("%d ", aux->idade_caixa);
            aux = aux->proximo;
        }
}

//função que verifica se tem caixa disponivel
int caixa_disponivel(int *caixas, int n_caixas)   {
int livre;

livre = 0;

    for (int i=0; i<n_caixas; i++)
        if (caixas[i] == 0)
            livre = 1;

return (livre);
}

//função que faz as operações na fila do caixa
void caixa(int n_caixas, lista_pessoas *LISTA)    {
int timer=0; //marcador de tempo
int n_p_fila=0, mostrar=0; // marcador do n° de pessoas na fila e se houve mudança para o printf
int c_livres=0; //contador de caixas livres
int *caixas;    //ponteiro que armazenará os tempos de utilização dos caixas
int aux=0; //auxiliar para as operações de caixa livre

caixas = (int*)malloc(n_caixas * sizeof(int));
for (int i=0; i<n_caixas; i++)  //inicializa os timers dos caixas
    caixas[i] = 0;

f_caixa *FILA = NULL;

    aux = 0;
    while ((tamanho != 0) || (n_p_fila != 0))   {

        //verifica e insere no caixa se tiver alguem na fila
        aux=0;
        c_livres = caixa_disponivel(caixas, n_caixas);
        if (FILA!=NULL)
        while ((n_p_fila!=0) && (c_livres == 1))  {
            if (caixas[aux] == 0)   {
                caixas[aux] = FILA->tempo_caixa;
                remove_elem_fila(&FILA);
                n_p_fila--;
            }
        aux++;
        c_livres = caixa_disponivel(caixas, n_caixas);
        }

        if (mostrar == 1)
            exibe_fila(FILA);
        
        mostrar = 0;
        
            while ((LISTA!=NULL) && (LISTA->instante == timer))   {    //pegar da lista (se nao for NULL) e inserir na fila
            mostrar = 1;
                if (LISTA->idade > 65) {
                    inserir_prioridade(&FILA, LISTA);
                    n_p_fila++;
                    remove_elem_lista(&LISTA);
                }
                else    {
                    insere_fila(&FILA, LISTA);
                    n_p_fila++;
                    remove_elem_lista(&LISTA);
                    }
            }

        for (aux=0; aux<n_caixas;aux++) {   //passar o tempo nos caixas
            if (caixas[aux]!=0)
                caixas[aux]--;
        }

        timer++; //passar o tempo do programa
    }
}