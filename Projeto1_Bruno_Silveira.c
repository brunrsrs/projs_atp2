#include <stdio.h>

int main()  {
FILE *entrada, *saida;
int n, k;   //Sendo n: largura da imagem (em pixeis); k: altura da imagem (em pixeis)
int R, G, B;    //Sendo RGB as cores do pixel da imagem (red, green, blue)

entrada = fopen ("figura.dat", "r");
saida = fopen ("cinza.dat", "w");

    if (entrada == NULL)    //Verificando se ha o arquivo "figura.dat"
        printf ("\n\tNao foi encontrado \"figura.dat\" para ser aberto\n");
    
    else    {
        printf ("\n\tArquivo aberto e criado com sucesso\n");   //Resposta ao usuario

        fscanf(entrada,"%d %d\n", &n, &k);
        fprintf (saida,"%d %d\n", n, k);    //Forma a primeira linha mostrando largura/altura

        for (int aux_linha=0; aux_linha<k; aux_linha++)   {
            for (int aux_coluna=0; aux_coluna<n; aux_coluna++) {
                fscanf(entrada,"%d %d %d ", &R, &G, &B);
                fprintf (saida, "%d ", (R+G+B)/3);  //Mostra os valores em escalas de cinza
            }
        fprintf (saida, "\n");  //Passa para a proxima linha do arquivo de saida
        }
    }

fclose(entrada);    //Garantir que o arquivo será encerrado
fclose(saida);

return 0;
}