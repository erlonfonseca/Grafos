#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ListaSimples.h"
#if WIN32 || win32
    #include <windows.h>
#elif linux || UNIX
    #include <time.h>
#endif
#define MAX 100

//Lista de Adjacencia para grafo direcionado

typedef struct TipoGrafo {
  int NumVertices;
  lista **list;
} TipoGrafo;

//--------------------------------------------------------------------------------
//strucs para a busca em profundidade
typedef struct Caminho{
	int tempo,*descoberta,*termino,*antecessor;
	TipoCor *cor;
}Caminho;
//------------------------------------------------------------------------------

//A função faz um grafo vazio a aprtir de um grafo passado como parametro
void fGVazio(TipoGrafo *g){
	int i;
	for(i = 0; i < g->NumVertices; i++){
		//g->list[i] = (node*)malloc(sizeof(node));
		g->list[i] = (lista*)malloc(sizeof(lista));
		if(g->list[i]==NULL){
			printf("\nERRO DE MEMORIA\n");
			exit(0);
		}
		flvazia(g->list[i]);
	}
}

void inicializa(TipoGrafo *aux, int vert){
	aux->NumVertices = vert;
	aux->list = (lista**)malloc(sizeof(lista*)*vert);
	if(aux->list == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	fGVazio(aux);
}
// A função verifica se um aresta existe
//Se existir a função retorna a posição em que vertive v2
//se encontra na lista de adjacencia de v1
//caso contrario a função retor 0
int verificarAresta(int v1, int v2, TipoGrafo *g){
	int posicao = buscar(v2, g->list[v1]);
	if(posicao != -1){
		return posicao;
	}else{
		return 0;
	}
}

//A função vai acessar o peso de uma aresta
int acessarAresta(int v1, int v2, TipoGrafo *g){
	int aux = verificarAresta(v1,v2,g);
	if(aux != 0){
		return acessaPeso(aux,g->list[v1]);
	}else{
		printf("A aresta nao existe\n");
		return -1;
	}
}

//A funcao retorna o grau de um vertice(v1) pertencente ao
//grafo(g) orientado


int grauVertOrientado(int v1, TipoGrafo *g){
	int entrada=0,saida = g->list[v1]->tamanho;
	int i;
	for(i=0;i<g->NumVertices;i++){
		int aux = buscar(v1, g->list[i]);
			if(aux != -1){
				entrada++;
			}
	}
	return entrada+saida;
}



//A funcao retorna o grau de um vertice(v1) pertencente ao
//grafo(g) nao orientado
 int grauVertice(int v1, TipoGrafo *g){
 	int aux;
 	aux = buscar(v1,g->list[v1]);
 	if(aux==-1){
 		return g->list[v1]->tamanho;
	 }else{
	 	return (g->list[v1]->tamanho)+1;
	 }
 }



//Imprime a lista de adjacencia de cada vertice
void imprimirLAdj(TipoGrafo *g){
	int i;
	for(i = 0; i<g->NumVertices; i++){
		printf("Adjacente a V%d: ",i+1);
		if(g->list[i]->tamanho > 0){
			imprimir(g->list[i]);
		}
		printf("\n");
	}
}

//Funçoes de adicionar e remover aresta para grafo orientado

// A função adiciona uma aresta ao grafo
// Recebe como parametro dois inteiros(v1 e v2) representando os vertives
//outro inteiro(peso) representando o peso da aresta
//e um TipoGrafo que repesenta o grafo
void addArestaOrientada(int v1, int v2, int peso, TipoGrafo *g){
	if(v1<g->NumVertices || v2 < g->NumVertices){
		insere(v2,peso, g->list[v1]);
	}else{
		printf("Vertice invalido\n");
	}
}

//A função remove a aresta que liga dois vertices
// Recebe como parametro dois inteiros(v1 e v2) representando os vertives
//e um TipoGrafo que repesenta o grafo
void removerArestaOrientada(int v1, int v2, TipoGrafo *g){
	int posicao = buscar(v2, g->list[v1]);
	if(posicao != -1){
		retira(posicao, g->list[v1]);
		printf("A aresta foi removia\n");
	}else{
		printf("A aresta nao existe\n");
	}
}


//A funçao rebece um grafo(g) como parametro e rotorna o seu transpoosto
TipoGrafo* transposto(TipoGrafo *g){
	TipoGrafo *gAux = (TipoGrafo*)malloc(sizeof(TipoGrafo));
	gAux->NumVertices = g->NumVertices;
	gAux->list = (lista**)malloc(sizeof(lista*)*g->NumVertices);
	if(gAux->list == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	fGVazio(gAux);
	int i,j;
	for(i=0;i<g->NumVertices;i++){
		for(j=0;j<g->list[i]->tamanho;j++){
			int vertAux= acessar(j+1, g->list[i]);
			int auxPeso = acessarAresta(i,vertAux , g);
			addArestaOrientada(vertAux,i,auxPeso,gAux);
		}
	}
	return gAux;
}

//funçoes de adicionar e remover aresta para grafo não orientado

// A função adiciona uma aresta ao grafo
// Recebe como parametro dois inteiros(v1 e v2) representando os vertives
//outro inteiro(peso) representando o peso da aresta
//e um TipoGrafo que repesenta o grafo
void addAresta(int v1, int v2, int peso, TipoGrafo *g){
	if(v1 < g->NumVertices || v2 < g->NumVertices){
		if(v1 == v2){
			insere(v2,peso, g->list[v1]);
		}
		else{
			insere(v2,peso, g->list[v1]);
			insere(v1,peso, g->list[v2]);
		}
	}else{
		printf("Vertice Invalido\n");
	}
}

//A função remove a aresta que liga dois vertices
// Recebe como parametro dois inteiros(v1 e v2) representando os vertives
//e um TipoGrafo que repesenta o grafo
void removerAresta(int v1, int v2, TipoGrafo *g){
	int posicao1 = buscar(v2, g->list[v1]), posicao2 =  buscar(v1, g->list[v2]);
	if(posicao1 != -1){
		retira(posicao1, g->list[v1]);
		retira(posicao2, g->list[v2]);
		printf("A aresta foi removia\n");
	}else{
		printf("A aresta nao existe\n");
	}
}

//----------------------------------------------------------------------------------------
// Busca em profundidade.
//Esta funcinado, mas falta um finalidade para a função.


//Função para inicializar os a tributos do Struct Caminho
//Se for um vetor de inteiros, entao o vetor será inicializado
//com -1(no caso do vetor antecessor o -1 assume o papel do NULL)
//O vetor do TipoCor seráinicializado com branco
void inicializaCaminho(Caminho *c, int tamanho){
	int i;
	c->antecessor = (int*)malloc(sizeof(int)*tamanho);
	if(c->antecessor == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	c->cor = (TipoCor*)malloc(sizeof(TipoCor)*tamanho);
	if(c->cor == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	c->descoberta = (int*)malloc(sizeof(int)*tamanho);
	if(c->descoberta == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	c->termino = (int*)malloc(sizeof(int)*tamanho);
	if(c->termino == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	for(i=0; i<tamanho; i++){
		c->antecessor[i]= -1;
		c->cor[i] = branco;
		c->termino[i]= -1;
		c->descoberta[i]= -1;
		c->tempo=0;
	}
}

//A função vizitar recebe como parametro um inteiro(v1)
//que corresponde ao vertice que será vizitado, recebe
//um TipoGrafo(*g) que corresponde ao grafo que contem v1,
//e recebe uma variavel do tipo Caminho(*c) que vai armazenar
//o antecessor, e em qual tempo o vertice foi vizitado;
void visitar(int v1, TipoGrafo *g, Caminho *c){
	c->cor[v1] = cinza;//quando um vertice é vizitado a sua cor muda para cinza
	c->tempo++;//Incrementa o tempo
	c->descoberta[v1] = c->tempo;//Salva o tempo
	int i;
	printf("Vertice V%d descoberto em tempo %d.\n", v1 + 1, c->descoberta[v1]);
	for(i=0;i<g->list[v1]->tamanho;i++){
		//a função acessar() retorna o elemento (i+1) da lista do vertice v1
		int vert = acessar(i+1,g->list[v1]);
		if(c->cor[vert] == branco){
			c->antecessor[vert] = v1;
			printf("Apartir de V%d visita-se V%d.\n",v1 + 1,vert+1);
			visitar(vert, g, c);
		}
	}
	c->cor[v1] = preto;
	c->tempo++;
	c->termino[v1] = c->tempo;
	printf("Vertice V%d terminado em tempo %d.\n", v1 + 1, c->termino[v1]);
}

void imprimeVetor(int *vet, int t){
	int i;
	for(i=0;i<t;i++){
		printf("%d  ",vet[i]);
	}
	printf("\n");
}

Caminho* buscaProfundidade(TipoGrafo *g){
	Caminho *caminho = (Caminho*)malloc(sizeof(Caminho));
	if(caminho == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	inicializaCaminho(caminho,g->NumVertices);
	int cont = 0;
	int i ;
	for(i=0;i<g->NumVertices;i++){
		if(caminho->cor[i] == branco){
			visitar(i,g,caminho);
		}
	}
	return caminho;
}

//----------------------------------------------------------------------------
//Algoritmo para verificar coponentes fortementes conexo

//Retorna a posição do maior elemento do vertor
int ondeEstaMaior(int vet[], int tam){
	int maior = vet[0], i, local=0;
	for(i=1;i<tam;i++){
		if(vet[i]>maior){
			maior = vet[i];
			local=i;
		}
	}
	return local;
}

//Retorna a posição de maior elemento do vetor e que é menor que o teto
int ondeEstaMaiorTeto(int vet[], int tam, int teto){
	int maior = -1, i, local = 0;
	for(i=0;i<tam;i++){
		if(maior < vet[i] ){
			if(vet[i] < teto){
				maior = vet[i];
				local = i;
			}
		}
	}
	return local;
}

//Não consegui pensar em um nome para essa função
//A função verifica se todas os vertices foram vizitados
//Se todos os vertices forem vizitados a função retorna 1
//se não retorna 0
int ncpenpef(TipoCor *ccor, int tam){
	int cont = 0,i;
	for(i=0;i<tam;i++){
		if(ccor[i] == preto){
			cont++;
		}
	}
	if(cont == tam){
		return 1;
	}
	return 0;
}

//Algoritmo para obter os componetes fortemente conexos
void fortConexos(TipoGrafo *g, Caminho *caminho){
	printf("\nBusca em Profundidade\n");
	Caminho *c = buscaProfundidade(g);//faz a busca em profundidade em g
	TipoGrafo *gTrans = (TipoGrafo*)malloc(sizeof(TipoGrafo));
	if(gTrans == NULL){
		printf("\nERRO DE MEMORIA\n");
		exit(0);
	}
	printf("\n\nBusca em Profundidade no Grafo Transposto\n");
	gTrans = transposto(g);//Cria um grafo transposto a g
	inicializaCaminho(caminho,g->NumVertices);
	int cont = 0;
	int i ;
	//Vertice Com o Maior Termino
	int vcmt = ondeEstaMaior(c->termino, g->NumVertices),aux=0;
	//Faz a busca em profundidade a apartir do vertice com maior tempo de termino
	while(ncpenpef(caminho->cor, g->NumVertices) == 0){
		int aux2 = c->termino[vcmt];
		if(caminho->cor[vcmt] == branco){
			visitar(vcmt,gTrans,caminho);
		}
		vcmt = ondeEstaMaiorTeto(c->termino, g->NumVertices, aux2);
		printf("\n");
		aux++;
	}
	printf("Quant %d",aux);
	free(c);
}

void impComForte(Caminho *c, int tam){
	int aux1, aux2, cont = tam;
	aux1 = ondeEstaMaior(c->descoberta, tam);
	printf("V%d ",aux1+1);
	cont--;
	if(c->antecessor[aux1]!=-1){
		printf(" - ");
	}else{
		printf("\n");
	}
	while(cont>0){
		aux2 = ondeEstaMaiorTeto(c->descoberta, tam, c->descoberta[aux1]);
		cont--;
		if(c->antecessor[aux2]!=-1){
			printf("V%d - ", aux2+1);
			aux1 = aux2;
		}else{
			printf("V%d \n",aux2+1);
			aux1 = aux2;
		}
	}
}
int quantComForte(Caminho *c, int tam){
	int i,cont = 0;
	for(i=0;i<tam;i++){
		if(c->antecessor[i] == -1){
			cont++;
		}
	}
	return cont;
}
int buscaVet(int *vet, int valor, int t){
	int i;
	 for(i=0; i<t; i++){
	 	if(vet[i] == valor){
	 		return i;
		 }
	 }
	 return -1;
}


void fullGrafo(TipoGrafo *g){
	inicializa(g,100);
	int i,j;
	for(i=0; i<g->NumVertices;i++){
		for(j=0; j<g->NumVertices; j++){
			addArestaOrientada(i, j, 0, g);
		}
	}
}

//---------------------------------------------------------------------------
//===================================================================================
//===================Menu===========================


void caseAddArestas(int op1, TipoGrafo *grafo,int v1, int v2, int peso){
	//int v1,v2,peso;
	printf("Digite o valor dos Vertices\nV1: ");
    scanf("%d",&v1);
    printf("V2: ");
    scanf("%d",&v2);
    if(!(v1 > grafo->NumVertices || v1 < 1 ||
		v2 > grafo->NumVertices || v2 < 1)){

		switch(op1){
     	case 1:
     		printf("Peso da Aresta: ");
     		//int peso;
     		scanf("%d",&peso);
     		if(verificarAresta(v1-1, v2-1, grafo)==0){
     			addArestaOrientada((v1-1), (v2-1), peso, grafo);
     			printf("A Aresta foi Adicionada\n");
			}else{
			 	printf("A Aresta Já existe\n");
			}
			break;
     	case 2:
		 	if(verificarAresta(v1-1, v2-1, grafo)==0){
     			addArestaOrientada((v1-1), (v2-1), 0, grafo);
     			printf("A Aresta foi Adicionada\n");
			}else{
			 	printf("A Aresta Já existe\n");
	 		}
     		break;
     	case 3:
     		printf("Peso da Aresta: ");
     		//int peso1;
     		scanf("%d",&peso);
     		if(verificarAresta(v1-1, v2-1, grafo)==0){
     			addAresta((v1-1), (v2-1), peso, grafo);
		     	printf("A Aresta foi Adicionada\n");
			}else{
			 	printf("A Aresta Já existe\n");
			}
			break;
   		case 4:
   			if(verificarAresta(v1-1, v2-1, grafo)==0){
     			addAresta((v1-1), (v2-1), 0, grafo);
     			printf("A Aresta foi Adicionada\n");
			}else{
			 	printf("A Aresta Já existe\n");
	 		}
     		break;
     	default:
     		printf("Opcao invalida\n");
     		break;
		}
	}else{
		printf("\nErro Vertice Invalido\n");
	}

}

void CaseRemAresta(int op1,TipoGrafo *grafo,int v1, int v2){
	printf("Digite o valor dos Vertices\nV1: ");
    scanf("%d",&v1);
    printf("V2: ");
    scanf("%d",&v2);
    if(v1 > grafo->NumVertices || v1 < 1 ||
		v2 > grafo->NumVertices || v2 < 1){
		printf("\nErro Vertice Invalido\n")	;
	}else{
	    if(op1 == 1 || op1 == 2){
	    	removerArestaOrientada(v1-1, v2-1, grafo);
	    	printf("\nAresta REmovida\n");
		}
		if(op1 == 3|| op1 == 4){
			removerAresta(v1-1, v2-1, grafo);
			printf("\nAresta REmovida\n");
		}
		if(op1 > 4 || op1 < 1){
			printf("Opcao invalida\n");
		}
	}
}

void CaseGrau(int op1,TipoGrafo *grafo,int v1){
	printf("Digite o valor do Vertice\nV1: ");
    scanf("%d",&v1);
	if(v1 > grafo->NumVertices || v1 < 1){
		printf("\nErro Vertice Invalido\n")	;
	}else{
		if(op1 == 1 || op1 == 2){
	    	printf("\nGrau de V%d: %d\n",v1,grauVertOrientado(v1-1, grafo));
		}
		if(op1 == 3|| op1 == 4){
			printf("\nGrau de V%d: %d\n",v1,grauVertice(v1-1, grafo));
		}
		if(op1 > 4 || op1 < 1){
			printf("\nOpcao invalida\n");
		}
	}
}

void menuListAdj(){
	TipoGrafo *gTransposto, *grafo = (TipoGrafo*)malloc(sizeof(TipoGrafo));
	Caminho *caminho, *auxCaminho ;
	setlocale(LC_ALL, "portuguese");
	int op1=1,op2;
	while(op1!=0){
		op2=1;
		printf("\n1. Grafo Orientado Valorado\n");
		printf("2. Grafo Orientado Não Valorado\n");
		printf("3. Grafo Não Orientado Valorado\n");
		printf("4. Grafo Não Orientado Não Valorado\n");
		printf("0. Sair\n");
		scanf("%d",&op1);
		printf("\n\n");
		if(op1 < 1 || op1 > 4){
			break;
		}
		while(op2 !=0){
			printf("\n1. Criar Grafo Vazio\n");
			printf("2. Adicionar Aresta\n");
			printf("3. Remover Aresta\n");
			printf("4. Verificar Aresta\n");
			printf("5. Grau de Vertive\n");
			printf("6. Imprime as Listas de Adjacencia\n");
			printf("7. Grafo Transposto\n");
			printf("8. Busca em Profundidades\n");
			printf("9. Componentes Fortemente Conexos\n");
			printf("0. Sair\n");
			scanf("%d", &op2);
			printf("\n\n");
			int v1,v2,peso;
			switch (op2){
				//Opcao criar grafo vazio
			   case 1:
			    printf("Digite o numero de Vertices: ");
			    int vert;
			    scanf("%d",&vert);
			    if(vert <= MAX){
			    	inicializa(grafo,vert);
				}else{
					printf("Numero de Vertices Estrapolados\n");
				}

			    printf("\n");
			   break;
				//Inserir arestas
			    case 2:
					caseAddArestas(op1, grafo, v1,  v2,  peso);
					printf("\n");
			   		break;
				case 3:
					CaseRemAresta(op1, grafo, v1, v2);
					//int v1,v2;

					break;
				case 4:
					printf("Digite o valor dos Vertices\nV1: ");
				    scanf("%d",&v1);
				    printf("V2: ");
				    scanf("%d",&v2);
				    if(v1 > grafo->NumVertices || v1 < 1 ||
						v2 > grafo->NumVertices || v2 < 1){
						printf("\nErro Vertice Invalido\n");
					}else{
						if(verificarAresta(v1-1, v2-1, grafo)){
							printf("\nA Aresta Exites\n");
						}else{
							printf("\nA Aresta Nao Exites\n");
						}
					}
					break;
				case 5:
					CaseGrau(op1,grafo, v1);
					printf("\n");
					break;
				case 6:
					imprimirLAdj(grafo);
					break;
				case 7:
					gTransposto = (TipoGrafo*)malloc(sizeof(TipoGrafo));
					gTransposto = transposto(grafo);
					imprimirLAdj(gTransposto);
					free(gTransposto);
					break;
			   case 8:
			   		caminho = buscaProfundidade(grafo),
					auxCaminho = (Caminho*)malloc(sizeof(Caminho));
					printf("\nAntecessores: ");
					imprimeVetor(caminho->antecessor, grafo->NumVertices);
					printf("\nTempo de Descoberta: ");
					imprimeVetor(caminho->descoberta,grafo->NumVertices);
					printf("\nTempo de Termino: ");
					imprimeVetor(caminho->termino,grafo->NumVertices);
					break;
			   case 9:

					auxCaminho = (Caminho*)malloc(sizeof(Caminho));
					fortConexos(grafo,auxCaminho);
					printf("\nComponentes Fortementes Conexo:\n");
					impComForte(auxCaminho, grafo->NumVertices);
					printf("\nQuantidades de Componentes Fortementes Conexo: %d\n",quantComForte(auxCaminho,grafo->NumVertices));
					break;
			   default:
			    printf("\n>...<\n");
			    op2=0;
			    break;
			}
		}
	}
}
