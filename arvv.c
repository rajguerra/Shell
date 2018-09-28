/* arvv.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvv.h"

#define N_CHAR 122

struct arvvar {
	int ver;
	char info[N_CHAR];
	struct arvvar* prim; /* ponteiro para eventual primeiro filho */
	struct arvvar* prox; /* ponteiro para eventual irm�o */
	struct arvvar* pai;
};

/* Fun��o cria
** Cria uma folha isolada para guardar um caractere e retorna seu ponteiro
*/
ArvVar* arvv_cria (char* c) {
	ArvVar *a = (ArvVar*) malloc(sizeof(ArvVar));
	int i;
	a->pai = NULL;
	a->ver = 1;
	strcpy(a->info,c);
	a->prim = NULL;
	a->prox = NULL;
	return a;
}

/* Fun��o insere
** Insere um n� pr�-existente na (sub)�rvore 'a'
*/
void arvv_insere (ArvVar* a, ArvVar* sa) {
	sa->prox = a->prim;
	a->prim = sa;
}

/* Fun��o imprime
** Percorre a �rvore, imprimindo sua estrutura, seguindo a formata��o textual
*/
void arvv_imprime (ArvVar* a) {
	ArvVar* p;
	printf(" <%c",a->info);
	for (p = a->prim; p != NULL; p = p->prox)
		arvv_imprime(p);
	printf(">");
}

/* Fun��o pertence
** Percorre a �rvore, buscando um valor. Retorna um inteiro (l�gico) indicando se encontrou ou n�o
*/
int arvv_pertence (ArvVar* a, char* c) {
	ArvVar* p;
	if (!strcmp(a->info,c))
		return 1;
	else {
		for (p = a->prim; p != NULL; p = p->prox) {
			if (arvv_pertence(p,c))
				return 1;
		}
		return 0;
	}
}


/* Fun��o libera
** Libera a mem�ria alocada para a �rvore, n� a n�
*/
void arvv_libera (ArvVar* a) {
	ArvVar* p = a->prim;
	while (p != NULL) {
		ArvVar* t = p->prox;
		arvv_libera(p);
		p = t;
	}
	free(a);
}

int arvv_altura (ArvVar* a) {
	int hmax = -1; /* -1 para arv. sem filhos */
	ArvVar* p;
	for (p=a->prim; p!=NULL; p=p->prox) {
		int h = arvv_altura(p);
		if (h > hmax)
		hmax = h;
	}
	return hmax + 1;
}

void tree(ArvVar* a,int i,int j) {
	ArvVar* p=a->prim;
	int t;
	int u = i-j;
	for(t=0;t<u;t++)
		printf("-");
	printf("%s\n",a->info);
	while(p!=NULL){
		j--;
		tree(p,i,j);
		j++;
		p = p->prox;
	}
}

ArvVar* cd(ArvVar* a,char* c){
	ArvVar* p;
	ArvVar* k;
	if(!strcmp(c,"..")){
		if(a->pai == NULL){
			printf("Voc� j� est� no diret�rio Raiz!\n");
			return a;
		}else{
			p = a->pai;
			return p;
		}
	}else{
		if(!strcmp(a->info,c)){
			return a;
		}else{
			for(p=a->prim;p!=NULL;p=p->prox){
				if(!strcmp(p->info,c)){
					p->pai = a;
					return p;
				}
			}
			return a;
		}
	}
}

void mkdir(ArvVar* a,char* nom){
	if(arvv_pertence(a,nom)){
		printf("Diret�rio com esse nome j� existente!\n");
	}else{
		if(a->ver == 0){
        	printf("%s � um arquivo, n�o pode ter diret�rios!\n",a->info);
		}else{			
        	ArvVar* novo = arvv_cria(nom);
        	arvv_insere(a,novo);
		}
	}
}

void touch(ArvVar* a,char* nom){
    ArvVar* arq = arvv_cria(nom);
    arq->ver = 0;
	arvv_insere(a,arq);
}
char* veInfo(ArvVar* a){
	return a->info;
}
