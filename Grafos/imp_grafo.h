#include "libgrafo.h"
#include <stdio.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define TRUE 1
#define FALSE 0

Grafo * a_gamat(int nv){
    Grafo *g = NULL;
    g = (Grafo *) malloc(sizeof(Grafo));
    g->p_mat = (int **) malloc(nv * sizeof(int));
    if(!g || !g->p_mat){
        printf("Erro de memória!");
        exit(1);
    }
    int i;
    for(i = 0; i < nv; i++)
        g->p_mat[i] = (int *) calloc(nv, sizeof(int));
    g->n_arst = 0;
    g->n_vert = nv;
    return g;
}

Grafo * f_gamat(Grafo *g){
    if(g == NULL) return NULL;
    int i;
    for(i = 0; i < g->n_vert; i++) free(g->p_mat[i]);
    free(g->p_mat);
    free(g);
    return NULL;
}

void n_grafo(Grafo **g, int nv){
    if(*g != NULL)
        *g = f_gamat(*g);
    if(*g == NULL)
        *g = a_gamat(nv);
}

int menu_n_grafo(){
    printf("1. Grafo direcionado;\n");
    printf("2. Grafo não-direcionado.\n");
    printf("> Digite uma opção: ");
    int op; scanf("%d", &op);
    return op;
}

int ler_grafo(Grafo **g){
    int nv, na, m;
    m = menu_n_grafo();
    if(m < 1 || m > 2){
        printf("Opção inválida! Saindo...");
        exit(1);
    }
    printf("\nDigite o número de vértices: ");
    scanf("%d", &nv);
    printf("Digite o número de arestas: ");
    scanf("%d", &na);

    /*Liberando o grafo existente na memória e/ou
    alocando um novo grafo*/
    n_grafo(g, nv);

    //Preenchendo o grafo com arestas e pesos
    printf("Digite V1, V2 e PESO separando por espaços\n");
    int i, v1, v2, p;
    if(m == 1)
        for(i = 0; i < na; i++){
            printf("V1 V2 PESO: ");
            scanf("%d %d %d", &v1, &v2, &p);
            if(p == 0) {printf("\nPeso não pode ser 0!"); return -1;}
            ins_dir_amat(*g, p, v1, v2);
        }
    else
        for(i = 0; i < na; i++){
            printf("V1 V2 PESO: ");
            scanf("%d %d %d", &v1, &v2, &p);
            if(p == 0) {printf("\nPeso não pode ser 0!"); return -1;}
            ins_ndir_amat(*g, p, v1, v2);
        }
    return m;
}

void g_show(Grafo *g){
    int i, j;
    printf("\n ");
    for(i = 0; i < g->n_vert; i++)
        printf("%3s%d", "V", i + 1);
    printf("\n");
    for(i = 0; i < g->n_vert; i++){
        printf("%s%d", "V", i + 1);
        for(j = 0; j < g->n_vert; j++)
            printf("%3d ", g->p_mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void ins_dir_amat(Grafo *g, int p, int v1, int v2){
    g->p_mat[--v1][--v2] = p;
    g->n_arst++;
}

void ins_ndir_amat(Grafo *g, int p, int v1, int v2){
    g->p_mat[--v1][--v2] = p;
    g->p_mat[v2][v1] = p;
    g->n_arst++;
}

void rmv_dir_amat(Grafo *g, int v1, int v2){
    g->p_mat[--v1][--v2] = 0;
    g->n_arst--;
}

void rmv_ndir_amat(Grafo *g, int v1, int v2){
    g->p_mat[--v1][--v2] = 0;
    g->p_mat[v2][v1] = 0;
    g->n_arst--;
}

int ex_amat(Grafo *g, int v1, int v2){
    return g->p_mat[--v1][--v2] > 0;
}

int grau(Grafo *g, int v){
    int i, s = 0;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v - 1][i] != 0) s++;
    return s;
}

int reg(Grafo *g){
    int i;
    if(g->n_vert == 1) return TRUE;
    int gr = grau(g, 1); // retorna o grau do vértice 1 (na matriz: 0)
    for(i = 1; i < g->n_vert; i++) // Linhas da matriz
        if(grau(g, i + 1) != gr) return FALSE;
    return gr;
}

int ls_vazia_amat(Grafo *g, int v){
    int i;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v][i] != 0) return FALSE;
    return TRUE;
}

int primeiro_ls_amat(Grafo *g, int v){
    int i;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v][i] > 0) return i;
    return -1;
}

void prox_adj_amat(Grafo *g, int *v, int *adj, int *peso, int *prox, int *fim){
    *adj = *prox; //adjacente é o próximo
    *peso = g->p_mat[*v][*prox]; (*prox)++;
    //deixa selecionado o "próximo do próximo"
    while(*prox < g->n_vert && g->p_mat[*v][*prox] == 0) (*prox)++;
    if(*prox == g->n_arst) *fim = TRUE;
}

void visita_dfs(Grafo *g, int u, int *tmp, int *d,
    int *t, int *cor, int *ant){
    int fim_ls;
    int peso, aux, v;
    cor[u] = CINZA; (*tmp)++; d[u] = *tmp;
    printf("Vértice %d decoberto em tempo %d.\n", u + 1, d[u]);
    if(!ls_vazia_amat(g, u)){
        aux = primeiro_ls_amat(g, u);
        fim_ls = FALSE;
        while(!fim_ls){
            /* O próximo da lista de adjacentes é retornado por v
             e aux já recebe o próximo com relação a v */
            prox_adj_amat(g, &u, &v, &peso, &aux, &fim_ls);
            if(cor[v] == BRANCO){
                ant[v] = u;
                visita_dfs(g, v, tmp, d, t, cor, ant);
            }
        }
    }
    cor[u] = PRETO; (*tmp)++; t[u] = *tmp;
    printf("Vértice %d terminado em tempo %d.\n", u + 1, t[u]);
}

void busca_dfs(Grafo *g){
    int v, tmp, i;
    int d[g->n_vert], t[g->n_vert],
    cor[g->n_vert], ant[g->n_vert];
    tmp = 0;
    for(i = 0; i < g->n_vert; i++){
        cor[i] = BRANCO;
        ant[i] = -1;
    }
    for(i = 0; i < g->n_vert; i++)
        if(cor[i] == BRANCO) visita_dfs(g, v, &tmp, d, t, cor, ant);
}

int empty_q(Fila *f){
    return (f == NULL);
}

void enq(Fila **f, int v){
    Fila *p = NULL;
    p = (Fila *)malloc(sizeof(Fila));
    if(!p){
        p->prox = *f; p->v = v;
        *f = p;
    }
}

void deq(Fila **f, int *v){
    Fila *p1 = NULL; p1 = *f;
    if(empty_q(*f)){
        printf("Fila vazia!"); return;
    }
    else{
        Fila *p2 = NULL; p2 = *f;
        while(p2->prox != NULL){
            p1 = p2; p2 = p2->prox;
        }
        *v = p2->v;
        p2->prox = NULL; free(p2);
        if(p1 == p2) *f = NULL;
    }
}

void primeiro_f(Fila *f, int *v){
    if(!empty_q(f)){
        Fila *p = f;
        while(p->prox != NULL) p = p->prox;
        *v = p->v;
    } else printf("Fila vazia!"); v = NULL; return;
}
