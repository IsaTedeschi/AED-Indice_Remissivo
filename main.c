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

	start = clock(); //COMEÇA A CONTAR O TEMPO

    ArvAVL *avl; //CRIAÇÃO DA ÁRVORE
    avl = cria_ArvAVL();

    // ABRE O ARQUIVO
    FILE *file = fopen("texto.txt", "r"); //ARQUIVO LIDO
    FILE *file2 = fopen("texto2.txt", "w"); //ARQUIVO ESCRITO COM O ÍNDICE

    if (file == NULL){
        fprintf(stderr, "Arquivo de leitura nao pode ser aberto!!!\n");
        return -1;
    }

    if (file2 == NULL){
        fprintf(stderr, "Arquivo de leitura nao pode ser aberto!!!\n");
        return -1;
    }

    // COMEÇO DA LEITURA DO ARQUIVO
    while (fscanf(file, "%[^\n] ", linha) != EOF){
        novaPalavra = strtok(linha, " ,.;!?/");

        while (novaPalavra != NULL) {
            minusculo(novaPalavra, palavra); //PASSAGEM PARA LETRA MINÚSCULA
            strcpy(aux.palavra, palavra);
            aux.tam = 0;

            int cont = 0;

            //CONFIRMAÇÃO SE A PALAVRA JÁ EXISTE
            for(i=0;i<numDistintas;i++){
                if(strcmp(aux.palavra, palavrasDist[i].palavra)==0){ //CASO A PALAVRA EXISTA
                    if(palavrasDist[i].tam != numLinhas){ //SE ELA NÃO ESTIVER DUAS VEZES NA MESMA LINHA
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

    //ELEMENTOS SÃO INSERIDOS NA ÁRVORE
    printf("\n");
    for(int j=0; j<numDistintas; j++){
        insere_ArvAVL(avl,palavrasDist[j]);
    }

	stop = clock(); //HORÁRIO FINAL
    tempo = ((double)(stop - start) / CLOCKS_PER_SEC); //CONTAGEM DE QUANTO TEMPO O PROGRAMA DEMOROU PARA EXECUTAR

    //IMPRESSÃO NA TELA
    printf("Índice:\n");
    escreveIndiceConsole(avl);
    printf("\n\n\nNúmero total de palavras: %d\n", numDistintas);
    printf("Número de palavras distintas: %d\n", numTotal);
    printf("Tempo de construção do índice usando árvore AVL: %.3fs\n\n", tempo);

    //IMPRESSÃO NO ARQUIVO
    fprintf(file2, "Índice:\n");
    escreveIndice(avl, file2);
    fprintf(file2, "\n\n\nNúmero total de palavras: %d\n", numDistintas);
    fprintf(file2, "Número de palavras distintas: %d\n", numTotal);
    fprintf(file2, "Tempo de construção do índice usando árvore AVL: %.3fs", tempo);

    return 0;
}

//FUNÇÃO DE CONVERSÃO DE CARACTERES EM MAIUSCULA PARA MINUSCULAS
void minusculo(char s1[], char s2[]){
    int i = 0;

    while(s1[i] != '\0'){
        s2[i] = tolower(s1[i]);
        i++;
    }
    s2[i] = '\0'; // caracter que indica o fim da string
}




