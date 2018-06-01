#include "libgrafo.h"

Grafo_m * a_gamat(int nv){
    Grafo_m *g = NULL;
    g = (Grafo_m *) malloc(sizeof(Grafo_m));
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

Grafo_m * f_gamat(Grafo_m *g){
    if(g == NULL) return NULL;
    int i;
    for(i = 0; i < g->n_vert; i++) free(g->p_mat[i]);
    free(g->p_mat);
    free(g);
    return NULL;
}

void n_grafo(Grafo_m **g, int nv){
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

int ler_grafo(Grafo_m **g){
    int nv, na, m;
    m = menu_n_grafo();
    if(m < 0 || m > 2){
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

void g_show(Grafo_m *g){
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

void ins_dir_amat(Grafo_m *g, int p, int v1, int v2){
    g->p_mat[--v1][--v2] = p;
    g->n_arst++;
}

void ins_ndir_amat(Grafo_m *g, int p, int v1, int v2){
    g->p_mat[--v1][--v2] = p;
    g->p_mat[v2][v1] = p;
    g->n_arst++;
}

void rmv_dir_amat(Grafo_m *g, int v1, int v2){
    g->p_mat[--v1][--v2] = 0;
    g->n_arst--;
}

void rmv_ndir_amat(Grafo_m *g, int v1, int v2){
    g->p_mat[--v1][--v2] = 0;
    g->p_mat[v2][v1] = 0;
    g->n_arst--;
}

int ex_amat(Grafo_m *g, int v1, int v2){
    return g->p_mat[--v1][--v2] != 0;
}

int grau(Grafo_m *g, int v){
    int i, s = 0;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v - 1][i] != 0) s++;
    return s;
}

int reg(Grafo_m *g){
    int i;
    if(g->n_vert == 1) return TRUE;
    int gr = grau(g, 1); // retorna o grau do vértice 1 (na matriz: 0)
    for(i = 1; i < g->n_vert; i++) // Linhas da matriz
        if(grau(g, i + 1) != gr) return FALSE;
    return gr;
}

int * conj_adj_amat(Grafo_m *g, int v){
    int k, *p = (int *)malloc(k = 0), i;
    --v;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v][i] != 0){
            p = (int *)realloc(p, ++k * sizeof(int));
            if(!p) { printf("Erro de memória"); exit(1); }
            p[k - 1] = i + 1;
        }
    return p;
}

void print_conj_adj(int grv, int *v){
    int i;
    printf("Lista de adjacentes: ");
    for(i = 0; i < grv; i++)
        if(i == grv - 1) printf("%d.", v[i]);
        else printf("%d - ", v[i]);
    printf("\n");
}

/* ------ Funções relacionadas a caminhamento em grafos ------ */

int ls_vazia_amat(Grafo_m *g, int v){
    int i;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v][i] != 0) return FALSE;
    return TRUE;
}

int primeiro_ls_amat(Grafo_m *g, int v){
    int i;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v][i] > 0) return i;
    return -1;
}

void prox_adj_amat(Grafo_m *g, int *v, int *adj, int *peso, int *prox, int *fim){
    *adj = *prox; //adjacente é o próximo
    *peso = g->p_mat[*v][*prox]; (*prox)++;
    //deixa selecionado o "próximo do próximo"
    while(*prox < g->n_vert && g->p_mat[*v][*prox] == 0) (*prox)++;
    if(*prox >= g->n_vert) *fim = TRUE;
}

void visita_dfs(Grafo_m *g, int u, int *tmp, int *d,
    int *t, int *cor, int *ant){
    int fim_ls;
    int peso, aux, v;
    cor[u] = CINZA; (*tmp)++; d[u] = *tmp;
    printf("Vértice %d descoberto em tempo %d.\n", u + 1, d[u]);
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

void gcic_amat(Grafo_m *g, int u, int *tmp, int *d,
    int *t, int *cor, int *ant, int *cic){
    if(*cic == 1) return;
    int fim_ls;
    int peso, aux, v;
    cor[u] = CINZA; (*tmp)++; d[u] = *tmp;
    if(!ls_vazia_amat(g, u)){
        aux = primeiro_ls_amat(g, u);
        fim_ls = FALSE;
        while(!fim_ls){
            /* O próximo da lista de adjacentes é retornado por v
             e aux já recebe o próximo com relação a v */
            prox_adj_amat(g, &u, &v, &peso, &aux, &fim_ls);
            if(cor[v] == BRANCO){
                ant[v] = u;
                gcic_amat(g, v, tmp, d, t, cor, ant, cic);
            } else *cic = 1;
        }
    }
    cor[u] = PRETO; (*tmp)++; t[u] = *tmp;
    return FALSE;
}

void busca_dfs(Grafo_m *g){
    int d[g->n_vert], t[g->n_vert],
    cor[g->n_vert], ant[g->n_vert];
    int i, tmp = 0;
    for(i = 0; i < g->n_vert; i++){
        cor[i] = BRANCO;
        ant[i] = -1;
    }
    for(i = 0; i < g->n_vert; i++)
        if(cor[i] == BRANCO) visita_dfs(g, i, &tmp, d, t, cor, ant);
}

int cic_dfs(Grafo_m *g){
    int d[g->n_vert], t[g->n_vert],
    cor[g->n_vert], ant[g->n_vert];
    int i, tmp = 0, cic = 0;
    for(i = 0; i < g->n_vert; i++){
        cor[i] = BRANCO;
        ant[i] = -1;
    }
    for(i = 0; i < g->n_vert; i++)
        if(cor[i] == BRANCO){
            gcic_amat(g, i, &tmp, d, t, cor, ant, &cic);
            if(cic == 1) return TRUE;
        }
    return FALSE;
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


/* ------ Funções de contagem de tempo de execução ------ */

double q1_timecount(Grafo_m *g, int v1, int v2,
                  int (*f)(Grafo_m *, int, int)){
    register const long _MIL = 1e6;
    #if linux
        struct timespec t1, t2;
        clock_gettime(CLOCK_REALTIME, &t1);
        f(g, v1, v2);
        clock_gettime(CLOCK_REALTIME, &t2);
        double elapsed = (t2.tv_sec - t1.tv_sec);
        elapsed += (double)(t2.tv_nsec - t1.tv_nsec) / _MIL;
        return elapsed;
    #elif WIN32
        struct LARGE_INTEGER l1, l2, freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&t1);
        f(g, v1, v2);
        QueryPerformanceCounter(&t2);
        double elapsed = (c2 - c1) * _MIL / CLOCKS_PER_SEC;
        return elapsed;
    #endif // linux
}

