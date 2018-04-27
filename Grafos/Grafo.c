#include <stdio.h>
#include "imp_grafo.h"
#include <locale.h>
/* ----- Programa Teste para a Implementação de Algoritmos de Grafos ----- */

int menu(){
    printf("\nMenu:\n");
    printf("1. Ler novo grafo;\n");
    printf("2. Mostrar o grafo;\n");
    printf("3. Inserir nova aresta;\n");
    printf("4. Remover aresta;\n");
    printf("5. Verificar se existe aresta;\n");
    printf("6. Questões gerais sobre o grafo;\n");
    printf("7. Aplicações de Buscas em Profundidade;\n");
    printf("8. Aplicações de Buscas em Largura;\n");
    printf("0. Sair do programa...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

int menu_6(){
    printf("\nMenu:\n");
    printf("1. Verificar se o grafo é regular;\n");
    printf("2. Verificar o grau de um vértice;\n");
    printf("0. Voltar para menu principal...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_6(Grafo *g, int op){
    int m;
    switch(op){
        case 1:
            m = reg(g);
            if(m) printf("\nGrafo regular em %d\n", m);
            else printf("\nGrafo não-regular\n");
            break;
        case 2:
            printf("Digite o número do vértice: ");
            int v; scanf("%d", &v);
            printf("Grau do vértice %d: %d", v, grau(g, v));
            break;
        case 0:
            printf("Voltando...\n");
            break;
        default:
            printf("Comando inválido!\n");
            break;
    }
}

int menu_7(){
    printf("\nMenu:\n");
    printf("1. Busca em Profundidade;\n");
    printf("2. Ver ciclicidade de grafo;\n");
    printf("3. Verificar ordenação topológica;\n");
    printf("4. Verificar componentes fortemente conexos;\n");
    printf("0. Voltar para menu principal...\n"); int op;
    printf("> Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

void exec_7(Grafo *g, int op){
    switch(op){
        case 1:
            busca_dfs(g);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            printf("Voltando...\n");
            break;
    }
}

int main(){
    Grafo *g = NULL;
    setlocale(LC_ALL, "portuguese");
    printf(" ** Leitura do grafo **\n");
    int m = ler_grafo(&g);
    int op;
    do{
        op = menu();
        switch(op){
            case 1:
                 m = ler_grafo(&g);
                 if(m == -1) return -1;
                break;
            case 2:
                g_show(g);
                break;
            case 3:
                printf("Digite os vértices e peso \"V1 V2 PESO\": ");
                int v1, v2, p; scanf("%d %d %d", &v1, &v2, &p);
                if(p == 0) {printf("\nPeso não pode ser 0!"); return -1;}
                if(m == 1)
                    ins_dir_amat(g, p, v1, v2);
                else ins_ndir_amat(g, p, v1, v2);
                break;
            case 4:
                printf("Digite os vértices \"V1 V2\": ");
                scanf("%d %d", &v1, &v2);
                if(m == 1)
                    rmv_dir_amat(g, v1, v2);
                else rmv_ndir_amat(g, v1, v2);
                break;
            case 5:
                printf("Digite os vértices \"V1 V2\": ");
                scanf("%d %d", &v1, &v2);
                if(ex_amat(g, v1, v2))
                    printf("\nExiste\n");
                else printf("\nNão existe\n");
                break;
            case 6:
                exec_6(g, menu_6());
                break;
            case 7:
                exec_7(g, menu_7());
                break;
            case 8:
                break;
            default:
                printf("Comando inválido\n");
                break;
        }
    } while(op != 0);
    g = f_gamat(g); //Libera o grafo da memória ao sair do programa
    printf("Saindo...");
    return 0;
}
