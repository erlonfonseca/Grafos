#include "libgrafo.h"
#include <stdio.h>

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
    printf("Digite uma opção: ");
    int op; scanf("%d", &op);
    return op;
}

int ler_grafo(Grafo **g){
    int nv, na, m;
    m = menu_n_grafo();
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

int lvad_amat(Grafo *g, int vert){
    int i;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[--vert][i] > 0) return 1;
    return 0;
}
