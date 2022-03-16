#include <stdio.h>

int main()  {
FILE *entrada, *saida;
int n, k;   //n: "image's width" (in pixels); k: "image's length" (im pixels)
int R, G, B;    //RGB are the colours (red, green, blue)

entrada = fopen ("figura.dat", "r");
saida = fopen ("cinza.dat", "w");

    if (entrada == NULL)    //Verifying if "figura.dat" exists
        printf ("\n\tNao foi encontrado \"figura.dat\" para ser aberto\n");
    
    else    {
        printf ("\n\tArquivo aberto e criado com sucesso\n");   //Answering the user

        fscanf(entrada,"%d %d\n", &n, &k);
        fprintf (saida,"%d %d\n", n, k);    //Shows width and length on "cinza.dat"

        for (int aux_linha=0; aux_linha<k; aux_linha++)   {
            for (int aux_coluna=0; aux_coluna<n; aux_coluna++) {
                fscanf(entrada,"%d %d %d ", &R, &G, &B);
                fprintf (saida, "%d ", (R+G+B)/3);  //Converts the RBG image to a grayscale
            }
        fprintf (saida, "\n");  //Jumps to the next line
        }
    }

fclose(entrada);    //Garantee the archive will be closed
fclose(saida);

return 0;
}
