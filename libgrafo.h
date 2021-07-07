#include <stdlib.h>
#include <stdio.h>
//#include "Structs.h"
#if WIN32 || win32
    #include <windows.h>
#elif linux || UNIX
    #include <time.h>
#endif

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define TRUE 1
#define FALSE 0

/**
* Biblioteca de definição de grafo
* e suas operações.
*/

/**
* Definição da estrutura Grafo_m.
* n_vert: número de vértices do grafo
* n_arst: inteiro para contagem
* em tempo de execução do número de arestas
* **p_mat: ponteiro para matriz de adjacências em
* indireção múltipla: p_mat é indexado na memória
* por vários *p_mat[i] (0 <= i <= n_vert) e cada um
* deles é um ponteiro de inteiros, que serão
* indexados na memória por p_mat[i][j] (0 <= j <= n_vert),
* originando uma matriz n_vert x n_vert com
* alocação dinâmica de memória.
* @author Lakshamana
*/
typedef struct t_grafo_amat{
    int n_vert;
    int n_arst;
    int mode;
    int **p_mat;
} Grafo_m;

/**
* Definição da TAD Lista
* e suas operações básicas
*/
typedef struct t_node{
    int data;
    int idx;
    struct t_node *prox;
}Lista;

//Struct para armazenar arestas (Kruskal)
typedef struct Aresta{
	int v1, v2, peso;
}Aresta;

typedef enum {
  branco, cinza, preto
} TipoCor;

typedef struct CaminhoProfundo{
	int tempo,*cor, *termino,*descoberta,*antecessor ;
}CaminhoProfundo;

#define INF 9999999
typedef struct CaminhoMinimo{
	int *antecessor, *custo;
}CaminhoMinimo;

//Struct para armazenar os antecessores e 0
//custo de sair de um vertice A para um vertice B
typedef struct CMFloydWarshall{
	int *antecessor, **matCusto;
}CMFloydWarshall;

int len(Lista *l);

void l_show(Lista *l);

Lista * get(Lista *l, int i);

void add(Lista **l, int data, int i);

void rmv(Lista **l, int i);

int indexof(Lista *l, int data);

int l_indexof(Lista *l, int data);

int l_min(Lista *l);

int * int_array(Lista *l);

/* ------ Funções relacionadas a conceitos básicos de grafos ------ */

/**
* Alocação dinâmica do Grafo_m
* e sua matriz de adjacências,
* preenchendo-a com zeros inicialmente.
* @param nv - número de vétices
* @return Grafo_m *
*/
Grafo_m * a_gamat(int nv, int mode);

/**
* Liberação (destruição) do grafo da memória,
* sua matriz de adjacências e seus ponteiros.
* @param g - um grafo qualquer
* @return NULL
*/
Grafo_m * f_gamat(Grafo_m *g);

/**
* Libera um grafo da memória se
* não estiver vazio, e aloca um
* novo grafo na memória.
* @param g - um grafo qualquer
* @param nv - número de vérices
*/
void n_grafo(Grafo_m **g, int nv, int m);

/**
* Leitura do novo
* grafo alocado na memória
* @param g - um grafo previamente
* alocado na memória
*
*/
int ler_grafo(Grafo_m **g);

/**
* Apresentar menu de grafo
* @author Lakshamana
* @return 1 - grafo direcionado.
* @return 2 - grafo não-direcionado.
*/
int menu_n_grafo();

/**
* Mostrar matriz de adjacências
* de um dado grafo
* @author Lakshamana
*/
void g_show(Grafo_m *g);

/**
* Insere aresta de um grafo
* @author Lakshamana
*/
void ins_amat(Grafo_m *g, int p, int v1, int v2);

/**
* Remove aresta de um grafo
* @author Lakshamana
*/
void rmv_amat(Grafo_m *g, int v1, int v2);

/**
* Existe aresta de um dado grafo
* @author Lakshamana
*/
int ex_amat(Grafo_m *g, int v1, int v2);

/**
* Grau de um vértice
* @author Lakshamana
*/
int grau(Grafo_m *g, int v);

/**
* Verificar se grafo é regular
* @author Lakshamana
*/
int reg(Grafo_m *g);

/**
* Retorna o conjunto de vértices
* adjacentes a um dado vértice
* @author Lakshamana
*/
Lista * conj_adj_amat(Grafo_m *g, int v);


/* ------ Funções relacionadas a caminhamento em grafos ------ */

/**
* Verifica se a lista de
* adjacências está vazia
* @author Ziviani
*/
int ls_vazia_amat(Grafo_m *g, int vert);

/**
* Primeiro adjacente da lista de adjacências
* de um dado vértice
* @author Ziviani
*/
int primeiro_ls_amat(Grafo_m *g, int v);

/**
* Próximo adjacente de um dado vértice
* @author Ziviani
*/
void prox_adj_amat(Grafo_m *g, int *v, int *adj,
    int *peso, int *prox, int *fim_ls);

/**
* Algoritmo de busca em profundidade
* @author Ziviani
*/
void visita_dfs(Grafo_m *g, int u, int *tmp, int *d,
    int *t, int *cor, int *ant);

/**
* Algoritmo de verificação
* de ciclicidade de um grafo
* @author Lakshamana
*/
void gcic_amat(Grafo_m *g, int u, int *tmp, int *d,
    int *t, int *cor, int *ant, int *cic);

/**
* Invólucro de gcic_mat
*/
int cic_dfs(Grafo_m *g);

/**
* Inicializador e invólucro do
* algoritmo visita_dfs
* @author Ziviani
*/
void busca_dfs(Grafo_m *g);

/**
* Inicializador da Busca em Largura
* @author Lakshamana
*/
void bfs(Grafo_m *g);

/**
* Algoritmo Busca em Largura
* @author Lakshamana
*/
void visita_bfs(Grafo_m *g, int u, int *cor, int *ant, int *d);

/**
* Algoritmo para imprimir
* o caminho dada uma busca bfs
* já realizada
* @author Ziviani
*/
void print_paths(Grafo_m *g, int s, int v, int *ant);

void env_path_bfs(Grafo_m *g, int s, int f);

int euler(Grafo_m *g);

void rb_cic(Grafo_m *g, int *s, int v, int *ant, Lista **c, int *end);

Lista * h_busca_cic(Grafo_m *g, int v);

Lista * hierholzer(Grafo_m *g);

void dijkstra(Grafo_m *g, int s);


/**
* Estrutura de fila para
* uso da busca em largura
* @author Lakshamana
*/
typedef struct t_fila{
    int v;
    struct t_fila *prox;
}Fila;

/**
* Mostrar fila de trás para a frente
*/
void s_fila(Fila *f);

/**
* Versão recursiva de mostrar fila.
* Mostra a fila de tal forma que os
* elementos que foram inseridos primeiro
* ficam à esquerda
* @author Lakshamana
*/
void s_filar(Fila *f);

/**
* Enfileirar
* @author Lakshamana
*/
void enq(Fila **f, int v);

/**
* Desenfileirar, retornando o
* valor do vértice
* @author Lakshamana
*/
void deq(Fila **f, int *v);

/**
* Verifica se a fila está vazia
* @author Lakshamana
*/
int empty_q(Fila *f);

/**
* Função invólucro para a implementação
* de impressão de elementos da fila
*/
void p_fila(int op, Fila *f);

/* ------ Funções de contagem de tempo de execução ------ */

/* As funções de contagem de tempo de execução de
alguma função geralmente seguem a seguinte forma:
* double nome(Tipo arg1, ..., Tipo argN,
              (tipo) (*f)(Tipo arg1, ..., Tipo argN){
              #if linux
                iniciar_contagem_linux();
                f(arg1, ..., argN);
                concluir_contagem_linux();
                retornar tempo_total;
              #elif WIN32
                iniciar_contagem_windows();
                f(arg1, ..., argN);
                concluir_contagem_windows();
                retornar tempo_total;
              #else macosx
                iniciar_contagem_macosx();
                f(arg1, ..., argN);
                concluir_contagem_macosx();
                retornar tempo_total;
              #endif
* }
*/

/**
* Executa a contagem de tempo
* de execução da função da Questão I
* do trabalho de Grafos
* @author Lakshamana
* @param int (*f)(Grafo_m *, int, int) recebe
* @param Grafo_m *g o grafo para ser usado por f
* @param int v1 um vértice
* @param int v2 outro vértice
* ponteiro para função ex_amat(Grafo_m *, int, int)
* @return o tempo de execução
*/
double q1_timecount(Grafo_m *g, int v1, int v2,
                    int (*f)(Grafo_m *, int, int));

/** Executa a contagem de tempo
* de execução da função da Questão II
* do trabalho de Grafos
* @author Lakshamana
* @param int *(*f)(Grafo_m *g, int a)
* @return o tempo de execução
*/
//Expandir a assinatura da função.
double q2_timecount(Grafo_m *g, int v,
                    Lista *(*f)(Grafo_m *, int));
