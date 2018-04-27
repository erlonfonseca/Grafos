#include <stdlib.h>

/**
* Biblioteca de definição de grafo
* e suas operações.
* @author Lakshamana
*/

/**
* Definição da estrutura Grafo.
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
*/
typedef struct t_grafo{
    int n_vert;
    int n_arst;
    int **p_mat;
} Grafo;


/* ------ Funções relacionadas a conceitos básicos de grafos ------ */

/**
* Alocação dinâmica do Grafo
* e sua matriz de adjacências,
* preenchendo-a com zeros inicialmente.
* @param nv - número de vétices
* @return Grafo *
*/
Grafo * a_gamat(int nv);

/**
* Liberação (destruição) do grafo da memória,
* sua matriz de adjacências e seus ponteiros.
* @param g - um grafo qualquer
* @return NULL
*/
Grafo * f_gamat(Grafo *g);

/**
* Libera um grafo da memória se
* não estiver vazio, e aloca um
* novo grafo na memória.
* @param g - um grafo qualquer
* @param nv - número de vérices
*/
void n_grafo(Grafo **g, int nv);

/**
* Leitura do novo
* grafo alocado na memória
* @param g - um grafo previamente
* alocado na memória
*/
int ler_grafo(Grafo **g);

/**
* Apresentar menu de grafo
* @return 1 - grafo direcionado.
* @return 2 - grafo não-direcionado.
*/
int menu_n_grafo();

/**
* Mostrar matriz de adjacências
* de um dado grafo
*/
void g_show(Grafo *g);

/**
* Insere aresta de um
* grafo direcionado
*/
void ins_dir_amat(Grafo *g, int p, int v1, int v2);

/**
* Insere aresta de um
* grafo não-direcionado
*/
void ins_ndir_amat(Grafo *g, int p, int v1, int v2);

/**
* Remove aresta de um
* grafo direcionado
*/
void rmv_dir_amat(Grafo *g, int v1, int v2);

/**
* Remove aresta de um
* grafo não-direcionado
*/
void rmv_ndir_amat(Grafo *g, int v1, int v2);

/**
* Existe aresta de um dado grafo
*/
int ex_amat(Grafo *g, int v1, int v2);

/**
* Grau de um vértice
*/
int grau(Grafo *g, int v);

/**
* Verificar se grafo é regular
*/
int reg(Grafo *g);


/* ------ Funções relacionadas a caminhamento em grafos ------ */

/**
* Verifica se a lista de
* adjacências está vazias
*/
int ls_vazia_amat(Grafo *g, int vert);

/**
* Primeiro adjacente da lista de adjacências
* de um dado vértice
*/
int primeiro_ls_amat(Grafo *g, int v);

/**
* Próximo adjacente de um dado vértice
* Implementação Ziviani
*/
void prox_adj_amat(Grafo *g, int *v, int *adj,
    int *peso, int *prox, int *fim_ls);

/**
* Algoritmo de busca em profundidade
*/
void visita_dfs(Grafo *g, int u, int *tmp, int *d,
    int *t, int *cor, int *ant);

/**
* Inicializador e invólucro do
* algoritmo visita_dfs
*/
void busca_dfs(Grafo *g);

/**
* Estrutura de fila para
* uso da busca em largura
*/

typedef struct t_fila{
    int v;
    struct t_fila *prox;
}Fila;

/**
* Enfileirar
*/
void enq(Fila **f, int v);

/**
* Desenfileirar, retornando o
* valor do vértice
*/
void deq(Fila **f, int *v);

/**
* Verifica se a fila está vazia
*/
int empty_q(Fila *f);

/**
* Retorna primeiro vértice da fila
*/
void primeiro_f(Fila *f, int *v);
