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
* originando uma matriz n_vert x n_vert para
* alocação dinâmica de memória.
*/
typedef struct t_grafo{
    int n_vert;
    int n_arst;
    int **p_mat;
} Grafo;

/**
* Alocação dinâmica do Grafo
* e sua matriz de adjacências,
* preenchendo-a com zeros inicialmente.
* @param nv - número de vétices
* @return Grafo
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
*
*/
int menu_n_grafo();

/**
*
*/
void g_show(Grafo *g);

/**
*
*/
void ins_dir_amat(Grafo *g, int p, int v1, int v2);

/**
*
*/
void ins_ndir_amat(Grafo *g, int p, int v1, int v2);

/**
*
*/
void rmv_dir_amat(Grafo *g, int v1, int v2);

/**
*
*/
void rmv_ndir_amat(Grafo *g, int v1, int v2);

/**
*
*/
int ex_amat(Grafo *g, int v1, int v2);

/**
*
*/
int lvad_amat(Grafo *g, int vert);
