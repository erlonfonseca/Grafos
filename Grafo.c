#if defined(WIN32) || defined(windows)
    #include "imp_grafo.c"
#else
    #include "libgrafo.h"
#endif
#include <locale.h>
#include "Lista_de_Adjacencia.h"

/* ----- Programa Teste para a Implementação de Algoritmos de Grafos ----- */

int menu_p(){
    printf("\nInserir novo grafo representado como:\n");
    printf("1. Matriz de Adjacências;\n");
    printf("2. Lista de Adjacências;\n");
    printf("0. Sair do programa...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

int menu_16(){
    printf("\nMenu:\n");
    printf("1. Verificar se o grafo é regular;\n");
    printf("2. Verificar o grau de um vértice;\n");
    printf("3. Obter conjunto de vértices adjacentes a um vértice;\n");
    printf("4. Verificar o tempo de execução de busca de aresta;\n");
    printf("5. Verificar o tempo de execução de 3;\n");
    printf("0. Voltar para menu anterior...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_16(Grafo_m *g, int op){
    switch(op){
        case 1:{
            int m = reg(g);
            if(m) printf("\nGrafo regular em %d\n", m);
            else printf("\nGrafo não-regular\n");
            break;
        }
        case 2:
            printf("Digite o número do vértice: ");
            int v; scanf("%d", &v);
            printf("Grau do vértice %d: %d\n", v, grau(g, v));
        break;
        case 3:
            printf("Digite o número do vértice: ");
            scanf("%d", &v);
            Lista *p = conj_adj_amat(g, v);
            l_show(p); printf("\n");
        break;
        case 4:
            printf("Digite os vértices \"V1 V2\": ");
            int v1, v2; scanf("%d %d", &v1, &v2);
            double elapsed = q1_timecount(g, v1, v2, ex_amat);
            printf("Tempo total de execução: %.5lfms.\n", elapsed);
        break;
        case 5:
            printf("Digite o número do vértice: ");
            scanf("%d", &v);
            elapsed = q2_timecount(g, v, conj_adj_amat);
            printf("Tempo total de execução: %.5lfms.\n", elapsed);
        break;
        case 0:
            printf("Voltando...\n");
        break;
        default:
            printf("Comando inválido! Voltando...\n");
        break;
    }
}

int menu_17(){
    printf("\nMenu:\n");
    printf("1. Busca em Profundidade;\n");
    printf("2. Ver ciclicidade de grafo;\n");
    printf("3. Verificar componentes fortemente conexos;\n");
    printf("4. Verificar ciclo euleriano;\n");
    printf("0. Voltar para menu anterior...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_17(Grafo_m *g, int op){
    switch(op){
        case 1:
            busca_dfs(g);
        break;
        case 2:
            if(cic_dfs(g)) printf("\nGrafo cíclico!\n");
            else printf("\nGrafo acíclico!\n");
        break;
        case 3:{
				CaminhoProfundo *auxCaminho = (CaminhoProfundo*)malloc(sizeof(CaminhoProfundo));
				CompFortCon(g,auxCaminho);
				printf("\nComponentes Fortementes Conexo:\n");
				imprimeCFC(auxCaminho, g->n_vert);
				printf("\nQuantidades de Componentes Fortementes Conexo: %d\n",quantCFC(auxCaminho,g->n_vert));
				break;
			}
        break;
        case 4:
            if(!euler(g)){ printf("\nGrafo não-euleriano!\n"); break; }
            printf("\nCiclo euleriano:\n");
            l_show(hierholzer(g));
        break;
        case 0:
            printf("Voltando...\n");
        break;
    }
}

int menu_18(){
    printf("\nMenu:\n");
    printf("1. Busca em Largura;\n");
    printf("2. Imprimir caminho;\n");
    printf("0. Voltar para menu anterior...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_18(Grafo_m *g, int op){
    switch(op){
        case 1:
            bfs(g);
        break;
        case 2:
            printf("Digite um vértice de origem e destino: ");
            int s; int f; scanf("%d %d", &s, &f);
            env_path_bfs(g, s, f);
        break;
        case 0:
            printf("Voltando...\n");
        break;
    }
}

int menu_19(){
    printf("\nMenu:\n");
    printf("1. Algoritmo de Dijkstra;\n");
    printf("2. Algoritmo de Bellman-Ford;\n");
    printf("3. Algoritmo de Floyd-Warshall;\n");
    printf("0. Voltar para menu anterior...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_19(Grafo_m *g, int op){
    switch(op){
        case 1:
            printf("Digite um vértice fonte: ");
            int s; scanf("%d", &s);
            dijkstra(g, s);
        break;
        case 2:{
                CaminhoMinimo *BF = (CaminhoMinimo*)malloc(sizeof(CaminhoMinimo));
                BF->antecessor = (int*)malloc(sizeof(int)*g->n_vert);
                BF->custo = (int*)malloc(sizeof(int)*g->n_vert);
                printf("Qual o vertice fonte?\n");
                int fonte;
                scanf("%d",&fonte);
                int auxliar = BellmanFord(g, fonte-1,BF);
                if(auxliar){
                    printf("Não possui ciclo negativo\n");
                    printf("Buscar um caminnho minho ate um vertice:\n");
                    printf("Qual o vertice?\nv1:\n");
                    int verti;
                    scanf("%d", &verti);
                    impCaminho(BF,fonte-1,verti-1);
                    printf("\nCusto: %d\n",BF->custo[verti-1]);
                }
        }break;
        case 3:{
                CMFloydWarshall *cm = (CMFloydWarshall*)malloc(sizeof(CMFloydWarshall));
                cm->antecessor = (int*)malloc(sizeof(int)*g->n_vert);
                cm->matCusto = (int**)malloc(sizeof(int*)*g->n_vert);
                int i;
                for(i=0;i<g->n_vert;i++){
                    cm->matCusto[i] = (int*)malloc(sizeof(int)*g->n_vert);
                }
                printf("int %d\n",FloydWarshall(g,cm));
                if(FloydWarshall(g,cm)){
                    printf("Caminho com custo minimo entre dois vertices\n");
                    printf("Digite o vertice v1: ");
                    int v,w;
                    scanf("%d",&v);
                    printf("Digite o vertice v2: ");
                    scanf("%d",&w);
                    mostraCaminho(cm,v-1,w-1);
                }
        }break;
        case 0:
            printf("Voltando...\n");
        break;
        default:
            printf("Comando inválido\n");
        break;
    }
}

int menu_110(){
    printf("\nMenu:\n");
    printf("1. Algoritmo de Prim;\n");
    printf("2. Algoritmo de Kruskal;\n");
    printf("0. Voltar para menu anterior...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_110(Grafo_m *g, int op){
    switch(op){
        case 1:
        break;
        case 2:{
                Aresta **a = VetAresta(g);
                Kruskal(g, a);
        }break;
        case 0: printf("Voltando...\n");
        break;
        default: printf("Comando inválido\n");
        break;
    }
}

int menu_1(){
    printf("\nMenu:\n");
    printf("1. Ler novo grafo;\n");
    printf("2. Mostrar o grafo;\n");
    printf("3. Inserir nova aresta;\n");
    printf("4. Remover aresta;\n");
    printf("5. Verificar se existe aresta;\n");
    printf("6. Questões gerais sobre o grafo;\n");
    printf("7. Aplicações de Buscas em Profundidade;\n");
    printf("8. Aplicações de Buscas em Largura;\n");
    printf("9. Algoritmos de Caminhos Mínimos;\n");
    printf("10. Algoritmos de Árvores Geradoras Mínimas;\n");
    printf("0. Voltar para menu principal...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_1(Grafo_m *g, int op_prin){
    switch(op_prin){
        case 1:
            ler_grafo(&g);
            break;
        case 2:
            g_show(g);
            break;
        case 3:
            printf("Digite os vértices e peso \"V1 V2 PESO\": ");
            int v1, v2, p; scanf("%d %d %d", &v1, &v2, &p);
            if(p == 0) {printf("\nPeso não pode ser 0!"); break;}
            ins_amat(g, p, v1, v2);
            break;
        case 4:
            printf("Digite os vértices \"V1 V2\": ");
            scanf("%d %d", &v1, &v2);
            rmv_amat(g, v1, v2);
            break;
        case 5:
            printf("Digite os vértices \"V1 V2\": ");
            scanf("%d %d", &v1, &v2);
            if(ex_amat(g, v1, v2))
                printf("\nExiste\n");
            else printf("\nNão existe\n");
            break;
        case 6:
            exec_16(g, menu_16());
            break;
        case 7:
            exec_17(g, menu_17());
            break;
        case 8:
            exec_18(g, menu_18());
            break;
        case 9:
            exec_19(g, menu_19());
            break;
        case 10:
            exec_110(g, menu_110());
            break;
        case 0:
            printf("Voltando...\n");
            break;
        default:
            printf("Comando inválido\n");
            break;
    }
}

int main(){
    Grafo_m *g = NULL;
    setlocale(LC_ALL, "portuguese");
    printf(" ** Leitura do grafo **\n");
    int op;
    do{
        op = menu_p();
        switch(op){
            case 1:
                if(!ler_grafo(&g)) break;
                int op1;
                while(TRUE){
                    op1 = menu_1();
                    if(op1 <= 0) break;
                    exec_1(g, op1);
                }
                break;
            case 2:
                menuListAdj();
                break;
            case 0: break;
            default:
                printf("Comando inválido!\n");
                break;
        }
    } while(op > 0);
    /* Será implementado um switch para
        liberar o grafo representado tanto
        em forma de matrizes ou de lista. */
    if(op == 1) g = f_gamat(g); //Libera o grafo da memória ao sair do programa
    printf("Saindo...");
    return 0;
}
