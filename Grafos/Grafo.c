#include <stdio.h>
#include "imp_grafo.h"
#include <locale.h>

int menu(){
    printf("\nMenu:\n");
    printf("1. Ler novo grafo;\n");
    printf("2. Mostrar o grafo;\n");
    printf("3. Inserir nova aresta;\n");
    printf("4. Remover aresta;\n");
    printf("5. Verificar se existe aresta;\n");
    printf("6. Aplicações de Buscas em Profundidade;\n");
    printf("7. Aplicações de Buscas em Largura;\n");
    printf("0. Sair do programa...\n"); int op;
    printf("Digite uma opção: "); scanf("%d", &op);
    printf("\n");
    return op;
}

int main(){
    Grafo *g = NULL;
    setlocale(LC_ALL, "portuguese");
    printf(" ** Leitura do grafo **\n");
    int m;
    m = ler_grafo(&g);
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
                break;
            case 7:
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
