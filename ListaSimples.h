#include <stdio.h>
#include <stdlib.h>

//Define um struct nodo que possui um inteiro e um struc nodo proximo
typedef struct nodo{
	int valor;
	int peso;
	struct nodo *proximo;
}node;

//Define um struct lista que possui dois ponteiro node(primeiro e ultimo)
//e um inteiro tamanho(tamanho da lista)
typedef struct{
	node *primeiro;
	node *ultimo;
	int tamanho;
}lista;

//Faz um lista vazia
void flvazia(lista *l){
	l->ultimo = l->primeiro = NULL;
	l->tamanho = 0;
}
//Verifica se a lista esta vazia
int vazia(lista *l){
	if(l->primeiro == NULL){
		//lista esta vazia
		return 1;
	}else{
		//lista não esta vazia
		return 0;
	}
}

//Insere na lista um valor(int x) no final da lista(lista *l)
void insere(int x,int peso1, lista *l){
	node *novo = (node*) malloc(sizeof(node));
	novo->valor = x;
	novo->peso = peso1;
	novo->proximo = NULL;
	if(vazia(l)){
		l->primeiro = l->ultimo = novo;
		l->tamanho++;
	}else{
		l->ultimo->proximo = novo;
		l->ultimo = novo;
		l->tamanho++;
	}
}

//Insere na lista um valor(int x) no inicio da lista(lista *l)
void insereinicio(int x,int peso1, lista *l){
	node *novo = (node*) malloc(sizeof(node));
	novo->valor = x;
	novo->peso = peso1;
	novo->proximo = NULL;
	if(vazia(l)){
		l->primeiro = l->ultimo = novo;
		l->tamanho++;
	}else{
		novo->proximo = l->primeiro;
		l->primeiro = novo;
		l->tamanho++;
	}
}

//Retorna o valor que esta localizado em uma posição da lista
//int p é a posição que será acessada
//lista *l é a lista que será acessada
int acessar(int p, lista *l){
	node *atual;
	atual  = l->primeiro;
	if(p<1 || p>l->tamanho){
		return -1;
	}else{
		int cont =1;
		while(cont != p){
			cont++;
			atual =atual->proximo;
		}
        return atual->valor;
	}
}
int acessaPeso(int p, lista *l){
	node *atual;
	atual  = l->primeiro;
	if(p<1 || p>l->tamanho){
		return -1;
	}else{
		int cont =1;
		while(cont != p){
			cont++;
			atual =atual->proximo;
		}
        return atual->peso;
	}
}
int buscar(int valor, lista *l){
	node *atual;
	 atual = l->primeiro;
	 int cont = 1;
	 while(cont <= l->tamanho){
	 	if(atual->valor == valor){
	 		return cont;
		 }else{
		 	cont++;
		 	atual = atual->proximo;
		 }
	 }
	 return -1;
}
//Remove um valor de um determinado local da lista(lista *l)
//int p é a posição da lista que será removida
int retira(int p, lista *l){
	if(vazia(l)){
		return 0;
	}else{
		if(p<1 || p>l->tamanho){
			return -1;
		}else{
			if(p==1){
				node *aux;
				aux = l->primeiro;
				l->primeiro = aux->proximo;
				int a = aux->valor;
				free(aux);
				l->tamanho--;
				return a;
			}else{
				if(p == l->tamanho){
					int i;
					node *atual,*proximo;
					atual = l->primeiro;
					proximo = atual->proximo;
					for(i = 1; i < l->tamanho -1;i++){
						atual = atual->proximo;
						proximo = proximo->proximo;
					}
					l->ultimo = atual;
					l->ultimo->proximo = NULL;
					l->tamanho--;
					int a = proximo->valor;
					free(proximo);
					return a;
				}else{
					node *atual,*proximo;
					atual = l->primeiro;
					proximo = atual->proximo;
					int cont =1;
					while(cont != p-1){
						cont++;
						atual = atual->proximo;
						proximo = proximo->proximo;
					}
					int a = proximo->valor;
					atual->proximo=proximo->proximo;
					free(proximo);
					l->tamanho--;
					return a;
				}
			}
		}
	}
}

//imprime os elementos de uma lista
void imprimir(lista *l){
	node *aux;
	aux = l->primeiro;
	while(aux != NULL){
		printf("%d ",aux->valor+1);
		aux= aux->proximo;
	}
}
