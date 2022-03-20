#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "indice.h"
#include "arvore.h"

void minusculo(char s1[], char s2[]);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    char *novaPalavra;
    char linha[100];
    char palavra[100];

    int numDistintas = 0;
    int numLinhas = 1;
    int numTotal = 0;
    int i;

    Indice palavrasDist[100];
    Indice aux;

    double tempo;
	clock_t start, stop;

	start = clock(); //COME�A A CONTAR O TEMPO

    ArvAVL *avl; //CRIA��O DA �RVORE
    avl = cria_ArvAVL();

    // ABRE O ARQUIVO
    FILE *file = fopen("texto.txt", "r"); //ARQUIVO LIDO
    FILE *file2 = fopen("texto2.txt", "w"); //ARQUIVO ESCRITO COM O �NDICE

    if (file == NULL){
        fprintf(stderr, "Arquivo de leitura nao pode ser aberto!!!\n");
        return -1;
    }

    if (file2 == NULL){
        fprintf(stderr, "Arquivo de leitura nao pode ser aberto!!!\n");
        return -1;
    }

    // COME�O DA LEITURA DO ARQUIVO
    while (fscanf(file, "%[^\n] ", linha) != EOF){
        novaPalavra = strtok(linha, " ,.;!?/");

        while (novaPalavra != NULL) {
            minusculo(novaPalavra, palavra); //PASSAGEM PARA LETRA MIN�SCULA
            strcpy(aux.palavra, palavra);
            aux.tam = 0;

            int cont = 0;

            //CONFIRMA��O SE A PALAVRA J� EXISTE
            for(i=0;i<numDistintas;i++){
                if(strcmp(aux.palavra, palavrasDist[i].palavra)==0){ //CASO A PALAVRA EXISTA
                    if(palavrasDist[i].tam != numLinhas){ //SE ELA N�O ESTIVER DUAS VEZES NA MESMA LINHA
                        palavrasDist[i].linhas[palavrasDist[i].tam] = numLinhas; //LINHA ADICIONADA AO INDICE DA PALAVRA
                        palavrasDist[i].tam++;
                    }
                    cont++;
                    break;
                }
            }
            if(cont == 0){ //CASO A PALAVRA NAO EXISTA AINDA
                aux.linhas[aux.tam] = numLinhas;
                palavrasDist[numDistintas] = aux; //PALAVRA ADICIONADA
                palavrasDist[numDistintas].tam++;
                numDistintas++;
            }

            numTotal++;
            novaPalavra = strtok(NULL," ,.;!?/");
        }


        numLinhas++;
    }

    //ELEMENTOS S�O INSERIDOS NA �RVORE
    printf("\n");
    for(int j=0; j<numDistintas; j++){
        insere_ArvAVL(avl,palavrasDist[j]);
    }

	stop = clock(); //HOR�RIO FINAL
    tempo = ((double)(stop - start) / CLOCKS_PER_SEC); //CONTAGEM DE QUANTO TEMPO O PROGRAMA DEMOROU PARA EXECUTAR

    //IMPRESS�O NA TELA
    printf("�ndice:\n");
    escreveIndiceConsole(avl);
    printf("\n\n\nN�mero total de palavras: %d\n", numDistintas);
    printf("N�mero de palavras distintas: %d\n", numTotal);
    printf("Tempo de constru��o do �ndice usando �rvore AVL: %.3fs\n\n", tempo);

    //IMPRESS�O NO ARQUIVO
    fprintf(file2, "�ndice:\n");
    escreveIndice(avl, file2);
    fprintf(file2, "\n\n\nN�mero total de palavras: %d\n", numDistintas);
    fprintf(file2, "N�mero de palavras distintas: %d\n", numTotal);
    fprintf(file2, "Tempo de constru��o do �ndice usando �rvore AVL: %.3fs", tempo);

    return 0;
}

//FUN��O DE CONVERS�O DE CARACTERES EM MAIUSCULA PARA MINUSCULAS
void minusculo(char s1[], char s2[]){
    int i = 0;

    while(s1[i] != '\0'){
        s2[i] = tolower(s1[i]);
        i++;
    }
    s2[i] = '\0'; // caracter que indica o fim da string
}




