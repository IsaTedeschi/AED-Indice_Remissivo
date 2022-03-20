#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "arvore.h" //inclui os Protótipos
#include "indice.h"

struct NO{
    Indice info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc (sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}



int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void escreveIndiceConsole(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        escreveIndiceConsole(&((*raiz)->esq));
        printf("\n%s: ",(*raiz)->info.palavra);
        for(int k=0;k<(*raiz)->info.tam;k++)
            printf("%d ", (*raiz)->info.linhas[k]);
        escreveIndiceConsole(&((*raiz)->dir));
    }
}

void escreveIndice(ArvAVL *raiz, FILE *file){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        escreveIndice(&((*raiz)->esq), file);
        fprintf(file, "\n%s: ",(*raiz)->info.palavra);
        for(int k=0;k<(*raiz)->info.tam;k++)
            fprintf(file, "%d ", (*raiz)->info.linhas[k]);
        escreveIndice(&((*raiz)->dir), file);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, Indice valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(strcmp(valor.palavra, atual->info.palavra)==0){
            return 1;
        }
        if(strcmp(valor.palavra, atual->info.palavra)>0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}



//=================================
int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void RotacaoDireita(ArvAVL *A){//LL
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoEsquerda(ArvAVL *A){//RR
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoDuplaDireita(ArvAVL *A){//LR
    RotacaoEsquerda(&(*A)->esq);
    RotacaoDireita(A);
}

void RotacaoDuplaEsquerda(ArvAVL *A){//RL
    RotacaoDireita(&(*A)->dir);
    RotacaoEsquerda(A);
}


int insere_ArvAVL(ArvAVL *raiz, Indice valor){
    int r;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(strcmp(valor.palavra, atual->info.palavra)<0){
        r = insere_ArvAVL(&(atual->esq), valor);
        if(r == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(strcmp(valor.palavra, (*raiz)->esq->info.palavra)<0 ){
                    RotacaoDireita(raiz);
                }else{
                    RotacaoDuplaDireita(raiz);
                }
            }
        }
    }else{
        if(strcmp(valor.palavra, atual->info.palavra)>0){
            r = insere_ArvAVL(&(atual->dir), valor);
            if(r == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(strcmp((*raiz)->dir->info.palavra, valor.palavra)<0){
                        RotacaoEsquerda(raiz);
                    }else{
                        RotacaoDuplaEsquerda(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return r;
}


struct NO* procuraMenor(struct NO* raiz){
    struct NO *atual, *prox;
    if (estaVazia_ArvAVL(&raiz)) return NULL;
    atual = raiz;
    prox = raiz->esq;
    while(prox != NULL){
        atual = prox;
        prox = prox->esq;
    }
    return atual;
}


// Correção nas linhas 301/302, conforme apontamento em aula!!
int iguais_ArvAVL(ArvAVL *r1, ArvAVL *r2){
   //struct NO *elem;
   if (*r1 == NULL && *r2 == NULL)
      return 1;
   else {
      if (*r1 == NULL || *r2 == NULL)
         return 0;
      if (strcmp((*r1)->info.palavra, (*r2)->info.palavra)==0){
        return ((iguais_ArvAVL(&(*r1)->esq,&(*r2)->esq)) &&
                (iguais_ArvAVL(&(*r1)->dir,&(*r2)->dir)));
      }
      else return 0;
   }
}
