#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include "indice.h"

typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, Indice data);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, Indice valor);
void emOrdem_ArvAVL(ArvAVL *raiz);
int iguais_ArvAVL(ArvAVL *r1, ArvAVL *r2);


#endif // ARVORE_H_INCLUDED
