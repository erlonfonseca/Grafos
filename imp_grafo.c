#include "libgrafo.h"

Grafo_m * a_gamat(int nv, int mode){
    Grafo_m *g = NULL;
    g = (Grafo_m *) malloc(sizeof(Grafo_m));
    g->p_mat = (int **) malloc(nv * sizeof(int *));
    if(!g || !g->p_mat){
        printf("Erro de memória!");
        exit(1);
    }
    int i;
    for(i = 0; i < nv; i++)
        g->p_mat[i] = (int *) calloc(nv, sizeof(int));
    g->n_arst = 0;
    g->mode = mode;
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

void n_grafo(Grafo_m **g, int nv, int m){
    if(*g != NULL)
        *g = f_gamat(*g);
    if(*g == NULL)
        *g = a_gamat(nv, m);
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
        printf("Opção inválida! Voltando...\n");
        return FALSE;
    }
    printf("\nDigite o número de vértices: ");
    scanf("%d", &nv);
    printf("Digite o número de arestas: ");
    scanf("%d", &na);

    /*Liberando o grafo existente na memória e/ou
    alocando um novo grafo*/
    n_grafo(g, nv, m);


    //Preenchendo o grafo com arestas e pesos
    printf("Digite V1, V2 e PESO separando por espaços\n");
    int i, v1, v2, p;
    for(i = 0; i < na; i++){
        printf("V1 V2 PESO: ");
        scanf("%d %d %d", &v1, &v2, &p);
        if(p == 0) {printf("\nPeso não pode ser 0!"); return FALSE;}
        ins_amat(*g, p, v1, v2);
    }
    return TRUE;
}

void g_show(Grafo_m *g){
    printf("\n   "); int i;
    for(i = 0; i < g->n_vert; i++)
        if(i < 9) printf(" %s%d", "V0", i + 1);
        else printf(" %s%d", "V", i + 1);
    printf("\n"); int j;
    for(i = 0; i < g->n_vert; i++){
        if(i < 9) printf("%s%d", "V0", i + 1);
        else printf("%s%d", "V", i + 1);
        for(j = 0; j < g->n_vert; j++)
            printf("%3d ", g->p_mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

Grafo_m * gcpy(Grafo_m *g){
    Grafo_m *cp = a_gamat(g->n_vert, g->mode);
    int i, j;
    for(i = 0; i < g->n_vert; i++)
        for(j = 0; j < g->n_vert; j++)
            cp->p_mat[i][j] = g->p_mat[i][j];
    cp->mode = g->mode;
    cp->n_arst = g->n_arst;
    return cp;
}

void ins_amat(Grafo_m *g, int p, int v1, int v2){
    if(g->mode == 1) g->p_mat[--v1][--v2] = p;
    else{
        g->p_mat[--v1][--v2] = p;
        if(v1 != v2) g->p_mat[v2][v1] = p;
    }
    g->n_arst++;
}

void rmv_amat(Grafo_m *g, int v1, int v2){
    if(g->mode == 1) g->p_mat[--v1][--v2] = 0;
    else{
        g->p_mat[--v1][--v2] = 0;
        if(v1 != v2) g->p_mat[v2][v1] = 0;
    }
    g->n_arst--;
}

int ex_amat(Grafo_m *g, int v1, int v2){
    return g->p_mat[--v1][--v2] != 0;
}

int grau(Grafo_m *g, int v){
    int i, s = 0;
    if(g->mode == 2){
        for(i = 0; i < g->n_vert; i++)
            if(g->p_mat[v - 1][i] != 0) s++;
    } else
        for(i = 0; i < g->n_vert; i++){
            if(g->p_mat[v - 1][i] != 0) s++;
            if(g->p_mat[i][v - 1] != 0) s++;
        }
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

Lista * conj_adj_amat(Grafo_m *g, int v){
    int i; Lista *p = NULL;
    --v;
    for(i = 0; i < g->n_vert; i++)
        if(g->p_mat[v][i] != 0) add(&p, i, len(p));
    return p;
}

/* ------ Funções relacionadas a caminhamento em grafos ------ */

Grafo_m * Grafo_transp(Grafo_m *g){
	int i, j;
	// funcao que inicia o grafo vazio com um dado número de vertices
	Grafo_m *gt = a_gamat(g->n_vert, g->mode);
	gt->n_arst = g->n_arst;

	for(i = 0; i < g->n_vert; i++){
        for(j = 0; j < g->n_vert; j++){
        	gt->p_mat[i][j] = g->p_mat[j][i];
		}
    }
    //g_show(gt); // TESTE: MATRIZ TRANSPOSTA
    return gt;
}

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

int cic_dfs(Grafo_m *g){
    int d[g->n_vert], t[g->n_vert],
    cor[g->n_vert], ant[g->n_vert];
    int i, tmp = 0, cic = FALSE;
    for(i = 0; i < g->n_vert; i++){
        cor[i] = BRANCO;
        ant[i] = -1;
    }
    for(i = 0; i < g->n_vert; i++)
        if(cor[i] == BRANCO){
            gcic_amat(g, i, &tmp, d, t, cor, ant, &cic);
            if(cic) return TRUE;
        }
    return FALSE;
}

void gcic_amat(Grafo_m *g, int u, int *tmp, int *d,
    int *t, int *cor, int *ant, int *cic){
    int fim_ls;
    int peso, aux, v;
    cor[u] = CINZA; (*tmp)++; d[u] = *tmp;
    if(!ls_vazia_amat(g, u)){
        aux = primeiro_ls_amat(g, u);
        fim_ls = FALSE;
        while(!fim_ls){
            if(*cic) return;
            prox_adj_amat(g, &u, &v, &peso, &aux, &fim_ls);
            if(cor[v] == BRANCO){
                ant[v] = u;
                gcic_amat(g, v, tmp, d, t, cor, ant, cic);
            } else if(cor[v] == CINZA && ant[u] != v) *cic = TRUE;
        }
    }
    cor[u] = PRETO; (*tmp)++; t[u] = *tmp;
}

int euler(Grafo_m *g){
    int i;
    for(i = 0; i < g->n_vert; i++)
        if(grau(g, i + 1) % 2 != 0) return FALSE;
    return TRUE;
}

void rb_cic(Grafo_m *g, int *s, int v, int *ant, Lista **c, int *end){
    Lista *l = conj_adj_amat(g, v + 1);
    int i;
    if(len(l) != 0)
        for(i = 0; i < len(l); i++){
            int nxt = get(l, i)->data;
            if(*end) return;
            if(nxt != *s && ant[v] != nxt) {
                add(c, v, len(*c));
                ant[nxt] = v;
                rb_cic(g, s, nxt, ant, c, end);
            }
            else if(nxt == *s && ant[v] != nxt){
                add(c, v, len(*c));
                *end = TRUE;
            }
        }
}

Lista * h_busca_cic(Grafo_m *g, int v){
    int end = FALSE;
    int i, ant[g->n_vert];
    for(i = 0; i < g->n_vert; i++) ant[i] = -1;
    Lista *c = NULL; int s = v; //cópia do vértice fonte para guardar referência
    rb_cic(g, &s, v, ant, &c, &end);
    //adicionar o fonte no fim para formar o ciclo
    add(&c, s, len(c));
    return c;
}

Lista * hierholzer(Grafo_m *g){
    Grafo_m *h = a_gamat(g->n_vert, g->mode); //alocação
    h = gcpy(g); //cópia segura
    int v0 = 0; //vértice inicial;
    Lista *p = NULL; add(&p, v0, 0);
    int i;
    while(h->n_arst > 0){
        int n, vi;
        for(i = 0; i < len(p); i++){ //Obter vértice em p com grau > 0
            n = get(p, i)->data;
            if(grau(h, n + 1) > 0){
                vi = n; break;
            }
        }
        Lista *l = h_busca_cic(h, vi); //Buscar ciclo com vértice vi
        /* Dada uma lista com os vértices, percorre a lista
           dois a dois itens, retirando as arestas de h */
        for(i = 0; i < len(l) - 1; i++){
            int u = get(l, i)->data; int v = get(l, i + 1)->data;
            rmv_amat(h, u + 1, v + 1);
        }
        //Substituir o vértice vi em p pela lista obtida em l
        int idx = l_indexof(p, vi); //Obter o índice da última ocorrência de um vértice na lista
        rmv(&p, idx); //Remover o vértice em idx
        //Adicionar a partir de idx
        for(i = 0; i < len(l); i++) add(&p, get(l, i)->data, idx++);
    }
    for(i = 0; i < len(p); i++) get(p, i)->data++;
    return p;
}

void bfs(Grafo_m *g){
    int ant[g->n_vert];
    int d[g->n_vert];  // Distância
    int cor[g->n_vert], i;
    // Decrementar para alcançar o vértice correto
    for(i = 0; i < g->n_vert; i++){
            cor[i] = BRANCO;
            d[i] = 1e6;
            ant[i] = -1;
    }
    for(i = 0; i < g->n_vert; i++)
        if(cor[i] == BRANCO) visita_bfs(g, i, cor, ant, d);
}

void visita_bfs(Grafo_m *g, int s, int *cor, int *ant, int *d){
    Fila *f = NULL;
    ant[s] = -1; cor[s] = CINZA; d[s] = 0;
    printf("Vértice fonte: %d\n", s + 1);
    enq(&f, s); p_fila(1, f);
    int u;
    while(!empty_q(f)){
        deq(&f, &u);
        printf("Vértice expandido: %d.\n", u + 1);
        /* As funções conj_adj_amat e grau recebem (u + 1)
        pois decrementam esse valor internamente */
        Lista *l = conj_adj_amat(g, u + 1);
        int i;
        if(len(l) != 0)
            for(i = 0; i < len(l); i++){
                int adj = get(l, i)->data;
                if(cor[adj] == BRANCO){
                    cor[adj] = CINZA;
                    ant[adj] = u;
                    d[adj] = d[u] + 1;
                    printf("Adjacente %d descoberto na distância %d.\n", adj + 1, d[adj]);
                    enq(&f, adj);
                }
            }
        cor[u] = PRETO;
        p_fila(1, f);
    }
}

void env_path_bfs(Grafo_m *g, int s, int f){
    int ant[g->n_vert];
    int d[g->n_vert];  // Distância
    int cor[g->n_vert], i;
    for(i = 0; i < g->n_vert; i++){
            cor[i] = BRANCO;
            d[i] = 1e6;
            ant[i] = -1;
    }
    //Obter a lista de anteriores
    for(i = 0; i < g->n_vert; i++)
        if(cor[i] == BRANCO) visita_bfs(g, i, cor, ant, d);
    --s; --f;
    print_paths(g, s, f, ant);
    printf("\n");
}

void print_paths(Grafo_m *g, int s, int v, int *ant){
    if(s == v) printf("%d", s + 1);
	else if(s != v && ant[v] == -1)
		printf("Não há caminho do vértice %d a %d", s + 1, v + 1);
    else{
        print_paths(g, s, ant[v], ant);
        printf(" - %d", v + 1);
    }
}

typedef struct t_wi_node{
    int idx, vertex;
}d_node;

int min_idx(int *v, int n){
    int idx, min = v[idx = 0], i;
    for(i = 0; i < n; i++)
        if(v[i] < min && v[i] > -1){
            min = v[i];
            idx = i;
        }
    return idx;
}

void dijkstra(Grafo_m *g, int s){
    int i, j;
    --s;
    for(i = 0; i < g->n_vert; i++)
        for(j = 0; j < g->n_vert; j++)
            if(g->p_mat[i][j] < 0){
                printf("Grafo com pelo menos uma aresta com peso negativo!\n");
                printf("Saindo!\n"); return;
            }

    int ant[g->n_vert], d[g->n_vert];
    for(i = 0; i < g->n_vert; i++){
        ant[i] = -1; d[i] = 1e6;
    }
    printf("Vértice fonte: %d\n", s + 1);
    d[s] = 0; Lista *l = NULL;
    //coloca os vértices em uma lista
    for(i = 0; i < g->n_vert; i++) add(&l, i, len(l));
    //Cria um vetor imutável com as distâncias
    int *a = (int *) malloc(len(l) * sizeof(int));
    while(len(l) > 0){
        int idx = min_idx(a, len(l)); //o índice da menor das distâncias
        a[idx] = -1; //previne que a posição seja escolhida novamente
        int u = get(l, idx)->data; rmv(&l, idx);
        Lista *p = conj_adj_amat(g, u + 1);
        if(len(p) != 0)
            for(i = 0; i < len(p); i++){
                int v = get(p, i)->data;
                if(d[u] + g->p_mat[u][v] < d[v]){
                    d[v] = d[u] + g->p_mat[u][v];
                    ant[v] = u;
                }
            }
    }
    printf("Caminhos Mínimos:\n");
    for(i = 0; i < g->n_vert; i++)
        if(i != s){
            printf("%d -> %d: ", s + 1, i + 1);
            print_paths(g, s, i, ant);
            printf("\n");
        }
}

//==============================================================================================
//Componentes Fortementes Conexos
//==============================================================================================

void inicializaCP(CaminhoProfundo *cp, int t){
	cp->tempo=0;
	cp->cor = (int*)malloc(sizeof(int)*t);
	cp->termino =(int*)malloc(sizeof(int)*t);
	cp->descoberta = (int*)malloc(sizeof(int)*t);
	cp->antecessor = (int*)malloc(sizeof(int)*t);
	int i;
	for(i=0;i<t;i++){
		cp->cor[i] = 0;
		cp->antecessor[i]=-1;
		cp->termino[i] = 999999;
		cp->descoberta[i] = 999999;
	}
}

void visita_dfs2(Grafo_m *g,int u ,CaminhoProfundo *cp){
    int fim_ls;
    int peso, aux, v;
    cp->cor[u] = 1;
    cp->tempo++;
	cp->descoberta[u] = cp->tempo;
    printf("Vertice %d descoberto em tempo %d.\n", u + 1,cp->descoberta[u]);
    if(!ls_vazia_amat(g, u)){

        aux = primeiro_ls_amat(g, u);
        fim_ls = FALSE;
        while(!fim_ls){
            /* O próximo da lista de adjacentes é retornado por v
             e aux já recebe o próximo com relação a v */
            prox_adj_amat(g, &u, &v, &peso, &aux, &fim_ls);
            if(cp->cor[v] == 0){
            	cp->antecessor[v] = u;
                //ant[v] = u;
                visita_dfs2(g, v,cp);
            }
        }
    }
    cp->cor[u] = 2;
    cp->tempo++;
    cp->termino[u] = cp->tempo;
    //cor[u] = 2; (tmp)++; t[u] = tmp;
    printf("Vértice %d terminado em tempo %d.\n", u + 1, cp->termino[u]);
}


void busca_profundidade(Grafo_m *g, CaminhoProfundo *cp){
    inicializaCP(cp,g->n_vert);
    int i;
    for(i = 0; i < g->n_vert; i++){
        if(cp->cor[i] == 0){
        	 //visita_dfs(g, i, cp->tempo, cp->descoberta, cp->termino, cp->cor, cp->antecessor);
        	visita_dfs2(g, i,cp);
		}
	}
}



Grafo_m* gTransposto(Grafo_m *g){
	Grafo_m *trans;
	trans = (Grafo_m*)malloc(sizeof(Grafo_m));
	trans->n_arst = g->n_arst;
	trans->n_vert = g->n_vert;
	trans->p_mat = (int**)malloc(sizeof(int*)*g->n_vert);
	int i,j;
	for(i=0;i<g->n_vert;i++){
		trans->p_mat[i] = (int*)malloc(sizeof(int)*g->n_vert);
	}
	for(i=0;i<g->n_vert;i++){
		for(j=0;j<g->n_vert;j++){
			trans->p_mat[j][i] = g->p_mat[i][j];
		}
	}
	g_show(trans);
	return trans;
}

int ncpenpef2(int *ccor, int tam){
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

void CompFortCon(Grafo_m *g, CaminhoProfundo *caminho){
	CaminhoProfundo *c =(CaminhoProfundo*)malloc(sizeof(CaminhoProfundo));
	busca_profundidade(g,c);
	Grafo_m *gTrans = gTransposto(g);// Grafo_transp(g,gTrans);
	inicializaCP(caminho,g->n_vert);
	int cont = 0;
	int i ;
	//Vertice Com o Maior Termino
	int vcmt = ondeEstaMaior(c->termino, g->n_vert),aux=0;

	//Faz a busca em profundidade a apartir do vertice com maior tempo de termino
	while(ncpenpef2(caminho->cor, g->n_vert) == 0){
		int aux2 = c->termino[vcmt];
		if(caminho->cor[vcmt] == 0){

			visita_dfs2(gTrans, vcmt, caminho);
		}
		vcmt = ondeEstaMaiorTeto(c->termino, g->n_vert, aux2);
		aux++;
	}
	free(c);
}

void imprimeCFC(CaminhoProfundo *c, int tam){
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
	printf("\n");
}
int quantCFC(CaminhoProfundo *c, int tam){
	int i,cont = 0;
	for(i=0;i<tam;i++){
		if(c->antecessor[i] == -1){
			cont++;
		}
	}
	return cont;
}
//======================================================================================================

void impVetCusto(int *vet, int t){
	int i;
	for(i=0;i<t;i++){
		if(vet[i] == INF){
			printf("INF ");
		}else{
			printf("%d ",vet[i]);
		}
	}
	printf("\n");
}
void impVetAnt(int *vet, int t){
	int i;
	for(i=0;i<t;i++){
		if(vet[i] == -1){
			printf("%d ",vet[i]);
		}else{
			printf("%d ",vet[i]+1);
		}
	}
	printf("\n");
}

void SingleSource(Grafo_m *g, int vFonte, CaminhoMinimo *cm){

	int i;
	for(i=0;i<g->n_vert;i++){
		cm->antecessor[i] = -1;
		cm->custo[i] = INF;
	}
	cm->custo[vFonte] = 0;

}

void relaxar(Grafo_m *g, CaminhoMinimo *cm, int v1, int v2){
	int aux;
	if(g->p_mat[v1][v2] == 0){
		aux = INF;
	}else{
		aux=g->p_mat[v1][v2];
	}
	if(cm->custo[v2] > cm->custo[v1]+aux){
		cm->custo[v2]=cm->custo[v1]+aux;
		cm->antecessor[v2] = v1;
	}
}
int BellmanFord(Grafo_m *g, int vFonte, CaminhoMinimo *cm){
	int i,j;
	SingleSource(g, vFonte, cm);
	printf("\nAntecessores: ");
	impVetAnt(cm->antecessor,g->n_vert);
	printf("Custo: ");
	impVetCusto(cm->custo,g->n_vert);
	
	for(i=0;i<g->n_vert;i++){
		for(j=0;j<g->n_vert;j++){
			if(i==0){
				relaxar(g,cm,vFonte,j);
			}else{
				if(i== vFonte){
					relaxar(g,cm,0,j);
				}else{
					relaxar(g,cm,i,j);
				}
			}
			printf("\nAntecessores:");
			impVetAnt(cm->antecessor,g->n_vert);
			printf("Custo:");
			impVetCusto(cm->custo,g->n_vert);
		}
	}
	printf("Verificacao de ciclo negativo . . .\n");
	for(i=0;i<g->n_vert;i++){
		for(j=0;j<g->n_vert;j++){
			int aux;
			if(g->p_mat[i][j] == 0){
				aux = INF;
			}else{
				aux=g->p_mat[i][j];
			}
			if(cm->custo[j] > cm->custo[i]+aux){
				cm->custo[j]=cm->custo[i]+aux;
				cm->antecessor[j] = i;
				printf("Foi possivel fazer mais um relaxamento\n");
				printf("\nAntecessores:");
				impVetAnt(cm->antecessor,g->n_vert);
				printf("Custo:");
				impVetCusto(cm->custo,g->n_vert);
				printf("O grafo possui Ciclo Negativo\n");
				return 0;
			}
		}
	}
	return 1;
}
void impCaminho(CaminhoMinimo *cm, int fonte, int destino){
	printf("%d ",destino+1);
	int aux = destino;
	if(cm->antecessor[aux] != -1){
		while(aux != fonte){
			aux = cm->antecessor[aux];
			printf("<- %d ",aux+1);
		}
	}
}
//=======================================================================================================
void impMat(int **mat,int t){
	int i,j;

	for(i=0;i<t;i++){
		for(j=0;j<t;j++){
			if(mat[i][j] == INF){
				printf("INF ");
			}else{
				printf(" %d ",mat[i][j]);
			}

		}
		printf("\n");
	}
}
//Algoritmo Floyd Warshall.
int FloydWarshall(Grafo_m *g,CMFloydWarshall *cm){
	int k,v,w;
	for(v=0;v<g->n_vert;v++){
		for(w=0;w<g->n_vert;w++){
			if(v==w){
				cm->matCusto[v][w] = 0;
			}else{
				if(g->p_mat[v][w] != 0){
					cm->matCusto[v][w] = g->p_mat[v][w];
				}else{
					cm->matCusto[v][w] = INF;
				}
			}
		}
	}
	impMat(cm->matCusto,g->n_vert);
	for(k=0;k<g->n_vert;k++){
		for(v=0;v<g->n_vert;v++){
			for(w=0;w<g->n_vert;w++){
				if(cm->matCusto[v][k] + cm->matCusto[k][w] < cm->matCusto[v][w]){
					cm->matCusto[v][w] = cm->matCusto[v][k] + cm->matCusto[k][w];
					cm->antecessor[w] = k;

				}
				printf("\n");
				printf("\nAntecessores: ");
				impVetAnt(cm->antecessor,g->n_vert);
				printf("Matriz de Custo:\n");
				impMat(cm->matCusto,g->n_vert);
			}
		}
	}
	int i;
	for(i=0;i<g->n_vert;i++){
		if(cm->matCusto[i][i] < 0 ){
			return 0;
		}
	}

	return 1;
}

void mostraCaminho(CMFloydWarshall *cm, int fonte, int destino){
	if(cm->matCusto[fonte][destino] != INF){
		printf("%d ",destino+1);
		int aux = destino;
		while(aux != fonte){
			aux = cm->antecessor[aux];
			printf("<- %d ",aux+1);
		}
	}else{
		printf("Não exite um caminho caminho que ligue esses vertices\n");
	}
}


//==============================================================================================
//Algoritmo de Kruskal

//Cria vetor de Aresta
Aresta** VetAresta(Grafo_m *g){
	Aresta **a = (Aresta**)malloc(sizeof(Aresta*)*5);
	if(a==NULL){
			printf("\nERRO DE MEMORIA\n");
			exit(0);
		}
	int i,j;
	for(i = 0;i<g->n_arst;i++){
		a[i] = (Aresta*)malloc(sizeof(Aresta));
		if(a[i]==NULL){
			printf("\nERRO DE MEMORIA\n");
			exit(0);
		}
	}
	int k=0;
	for(i=0;i<g->n_vert;i++){
		for(j=0;j<=i;j++){
			if(g->p_mat[i][j] != 0){
				a[k]->peso = g->p_mat[i][j];
				a[k]->v1 = i;
				a[k]->v2 =j;
				k++;

			}
		}
	}
	return a;
}

int separa(Aresta **v, int p, int r){
   int c = v[p]->peso, i = p+1, j = r;
   Aresta *t,*c1 = v[p];
   while(TRUE){
    	while(i <= r && v[i]->peso <= c){
    		i++;
		}
    	while (c < v[j]->peso){
    		j--;
		}
	    if (i >= j){
	    	break;
		}
	    t = v[i];
		v[i] = v[j];
		v[j] = t;
	    ++i; --j;
   }
   v[p] = v[j], v[j] = c1;
   return j;
}
//Algoritmos QuickSort
void quicksort (Aresta **v, int p, int r){
   int j;
   if (p < r){
      j = separa (v, p, r);
      quicksort (v, p, j-1);
      quicksort (v, j+1, r);
   }
}

//Algoritmo de buscas(for\E7a bruta)
int buscaNoVet(int *vet, int valor, int t){
	int i;
	for(i=0;i<t;i++){
		if(vet[i] == valor){
			return i;
		}
	}
	return -1;
}

//Ordena o vetor em fun\E7\E3o do peso das arestas
void ordenaArestas(Grafo_m *g, Aresta **a){
	quicksort(a, 0, g->n_arst-1);
}

//Algoritmo de Kruskal
void Kruskal(Grafo_m *g, Aresta **a){
	//Ordena as arestas do grafo
	ordenaArestas(g, a);
											//Aloca um vetor para armazenar o conj de vertices
	int  i,j,k,nAres=0,nEle = 0,custoMin = 0,*conj = (int *)malloc(sizeof(int)*g->n_vert);
	if(conj==NULL){
			printf("\nERRO DE MEMORIA\n");
			exit(0);
		}
	for(i=0;i<g->n_vert;i++){
		conj[i] = -2;
	}
	//Aloca memoria para armazenar a AGM
	Aresta **arv = (Aresta**)malloc(sizeof(Aresta*));
	if(arv==NULL){
			printf("\nERRO DE MEMORIA\n");
			exit(0);
		}
	for(k=0;k<g->n_vert-1;k++){
		arv[k] = (Aresta*)malloc(sizeof(Aresta));
		if(arv[k]==NULL){
			printf("\nERRO DE MEMORIA\n");
			exit(0);
		}
	}
	printf("\n...\n");
	for(k=0;k<g->n_arst;k++){
		//Verifica se os vertives que compoem a aresta ja est\E3o
		//presentes no conj de vertices, se um dele n\E3o estiver,
		//ent\E3o a aresta \E9 adicionada a AGM, se n\E3o verifica a proxima aresta
		if(buscaNoVet(conj,a[k]->v1,g->n_vert) == -1 ||
		buscaNoVet(conj,a[k]->v2,g->n_vert) == -1){
			printf("A aresta V%d - V%d foi adicionada na arvore\n",a[k]->v1+1, a[k]->v2+1);
			arv[nAres] = a[k];
			custoMin += arv[nAres]->peso;
			nAres++;
		}else{
			printf("A aresta V%d - V%d nao foi adicionada na arvore. Ela formou um ciclo\n",a[k]->v1, a[k]->v2);
		}

		if(buscaNoVet(conj,a[k]->v1,g->n_vert) == -1){
			conj[nEle] = a[k]->v1;
			nEle++;
		}
		if(buscaNoVet(conj,a[k]->v2,g->n_vert) == -1){
			conj[nEle] = a[k]->v2;
			nEle++;
		}
		if(nAres == g->n_vert-1){
			break;
		}
	}

	printf("\nArvore Geradora Minima\n");
	for(j=0;j<nAres;j++){
		printf("Aresta: V%d - V%d, Peso: %d \n",arv[j]->v1+1,arv[j]->v2+1,arv[j]->peso);
	}
	printf("Custo Minimo: %d",custoMin);
}

/* --- Implementação da estrutura Fila --- */

int empty_q(Fila *f){
    return (f == NULL);
}

void enq(Fila **f, int v){
    Fila *p = NULL;
    p = (Fila *)malloc(sizeof(Fila));
    if(!p){
        printf("Erro de memória!"); exit(1);
    }
    p->prox = *f; p->v = v; *f = p;
}

void s_fila(Fila *f){
    if(empty_q(f)) {
        printf("Fila vazia!\n"); return;
    }
    printf("Fila: ");
    while(f != NULL){
        if(f->prox == NULL) printf("%d", f->v + 1);
        else printf("%d, ", f->v + 1);
        f = f->prox;
    }
    printf("\n");
}

void s_filar(Fila *f){
	if(empty_q(f)) {
        printf("Fila vazia!\n"); return;
    }
	if(f->prox != NULL){
		s_filar(f->prox);
		printf(", %d", f->v + 1);
	} else printf("Fila: %d", f->v + 1);
}

void p_fila(int op, Fila *f){
    switch(op){
        case 1:
            s_filar(f);
            printf("\n");
            break;
        case 2:
            s_fila(f);
            break;
    }
}

void deq(Fila **f, int *v){
    if(empty_q(*f)){
        printf("Fila vazia!"); return;
    }
    else{
        Fila *p1, *p2; p1 = p2 = *f;
        while(p2->prox != NULL){
            p1 = p2; p2 = p2->prox;
        }
        *v = p2->v;
        p1->prox = NULL; free(p2);
        if(p1 == p2) *f = NULL;
    }
}

void l_show(Lista *l){
    if(len(l) == 0){
        printf("Lista vazia!"); return;
    }
    printf("Lista: ");
    while(l != NULL){
        if(l->prox == NULL) printf("%d", l->data);
        else printf("%d, ", l->data);
        l = l->prox;
    }
    printf("\n");
}

int len(Lista *l){
    if(l == NULL) return 0;
    int i = 0;
    while(l != NULL){
        i++; l = l->prox;
    }
    return i;
}

Lista * get(Lista *l, int i){
    if(i < 0 || i >= len(l)){
        printf("Índice incorreto!"); return NULL;
    }
    while(l->idx < i) l = l->prox;
    return l;
}

void add(Lista **l, int data, int i){
    if(len(*l) == 0){
        Lista *p = (Lista *)malloc(sizeof(Lista));
        if(!p){ printf("Erro de memória!"); return; }
        p->idx = 0; p->data = data; p->prox = NULL; *l = p;
    } else{ //Para listas não-vazias:
        if(i == 0){ //Adicionar no início
            Lista *tmp = *l; //Atualizar índices
            while(tmp != NULL){
                tmp->idx++; tmp = tmp->prox;
            }
            Lista *p = (Lista *)malloc(sizeof(Lista)); // Alocar
            if(!p){ printf("Erro de memória!"); return; } //Tratar
            p->idx = 0; p->data = data; p->prox = *l; *l = p;
        } else if(i == len(*l)){ // Adicionar no fim
            Lista *p = (Lista *)malloc(sizeof(Lista)); // Alocar
            if(!p){ printf("Erro de memória!"); return; } //Tratar
            Lista *tmp = get(*l, len(*l) - 1); // Obter o último nó
            tmp->prox = p;
            p->idx = tmp->idx + 1; p->data = data; p->prox = NULL;
        } else{ // Adicionar em índice i
            Lista *tmp1 = get(*l, i - 1), *tmp2 = get(*l, i);
            Lista *p = (Lista *)malloc(sizeof(Lista)); // Alocar
            if(!p){ printf("Erro de memória!"); return; } //Tratar
            p->data = data; p->idx = i;
            tmp1->prox = p; p->prox = tmp2;
            while(tmp2 != NULL){ //Atualizar índices a partir de tmp2
                tmp2->idx++; tmp2 = tmp2->prox;
            }
        }
    }
}

void rmv(Lista **l, int i){
    if(len(*l) == 0){
        printf("Lista vazia!"); return;
    } else if(i >= len(*l)){
        printf("Índice incorreto"); return;
    } else{
        if(i == 0){
            Lista *tmp = *l;
            *l = tmp->prox;
            free(tmp);
            Lista *p = *l;
            while(p != NULL){
                p->idx--; p = p->prox;
            }
        } else if(i == len(*l) - 1){
            Lista *p1, *p2; p1 = p2 = *l;
            while(p2->prox != NULL){
                p1 = p2; p2 = p2->prox;
            }
            p1->prox = NULL; free(p2);
            if(p1 == p2) *l = NULL;
        } else{
            Lista *tmp1 = get(*l, i - 1);
            Lista *tmp2 = get(*l, i);
            tmp1->prox = tmp2->prox;
            free(tmp2);
            while(tmp1->prox != NULL){ // Atualizar índices à direita
                tmp1 = tmp1->prox; tmp1->idx--;
            }
        }
    }
}

int indexof(Lista *l, int data){
    if(len(l) == 0){
        printf("Lista vazia!"); return -1;
    }
    while(l != NULL){
        if(data == l->data) return l->idx;
        l = l->prox;
    }
    return -1; //Terá chegado ao fim sem ter encontrado elemento
}

int l_indexof(Lista *l, int data){
    if(len(l) == 0){
        printf("Lista vazia!"); return -1;
    }
    int i = -1;
    while(l != NULL){
        if(data == l->data) i = l->idx;
        l = l->prox;
    }
    return i;
}

int l_min(Lista *l){
    if(len(l) == 0){
        printf("Lista vazia!"); return -1e6;
    }
    int _min = l->data;
    while(l->prox != NULL){
        l = l->prox;
        if(_min > l->data) _min = l->data;
    }
    return _min;
}

int * int_array(Lista *l){
    int i = 0;
    int *a = (int *) malloc(len(l) * sizeof(int));
    while(l != NULL){
        a[i] = l->data;
        l = l->prox; i++;
    }
    return a;
}

/* ------ Funções de contagem de tempo de execução ------ */

double q1_timecount(Grafo_m *g, int v1, int v2,
                  int (*f)(Grafo_m *, int, int)){
    #if linux
        register const long _MIL = 1e6;
        struct timespec t1, t2;
        clock_gettime(CLOCK_REALTIME, &t1);
        f(g, v1, v2);
        clock_gettime(CLOCK_REALTIME, &t2);
        double elapsed = (t2.tv_sec - t1.tv_sec);
        elapsed += (double)(t2.tv_nsec - t1.tv_nsec) / _MIL;
        return elapsed;
    #elif WIN32
        __int64 l1, l2, freq;
        QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
        QueryPerformanceCounter((LARGE_INTEGER *)&l1);
        f(g, v1, v2);
        QueryPerformanceCounter((LARGE_INTEGER *)&l2);
        double elapsed = (l2 - l1) * 1000.0 / freq;
        return elapsed;
    #endif // linux
}

double q2_timecount(Grafo_m *g, int v,
                  Lista *(*f)(Grafo_m *, int)){
    #if linux
        register const long _MIL = 1e6;
        struct timespec t1, t2;
        clock_gettime(CLOCK_REALTIME, &t1);
        f(g, v);
        clock_gettime(CLOCK_REALTIME, &t2);
        double elapsed = (t2.tv_sec - t1.tv_sec);
        elapsed += (double)(t2.tv_nsec - t1.tv_nsec) / _MIL;
        return elapsed;
    #elif WIN32
        __int64 l1, l2, freq;
        QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
        QueryPerformanceCounter((LARGE_INTEGER *)&l1);
        f(g, v);
        QueryPerformanceCounter((LARGE_INTEGER *)&l2);
        double elapsed = (l2 - l1) * 1000.0 / freq;
        return elapsed;
    #endif // linux
}
