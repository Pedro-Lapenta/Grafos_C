#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definindo o número máximo de vértices
#define MAX_VERTICES 100

// Estrutura do grafo com matriz de adjacência
typedef struct {
    int matriz_adjacencia[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Grafo;

// Função para inicializar o grafo
void inicializar_grafo(Grafo* g, int num_vertices) {
    g->num_vertices = num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            g->matriz_adjacencia[i][j] = 0;  // Inicializa com 0 (sem arestas)
        }
    }
}

// Função para adicionar aresta
void adicionar_aresta(Grafo* g, int origem, int destino, int peso) {
    g->matriz_adjacencia[origem][destino] = peso;
    g->matriz_adjacencia[destino][origem] = peso;  // Grafo não direcionado
}

// Função para busca em largura
void busca_em_largura(Grafo* g, int inicio) {
    int visitado[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES], frente = 0, tras = 0;

    printf("Busca em Largura a partir do vertice %d: ", inicio);
    visitado[inicio] = 1;
    fila[tras++] = inicio;

    while (frente < tras) {
        int v = fila[frente++];
        printf("%d ", v);

        for (int i = 0; i < g->num_vertices; i++) {
            if (g->matriz_adjacencia[v][i] != 0 && !visitado[i]) {
                visitado[i] = 1;
                fila[tras++] = i;
            }
        }
    }
    printf("\n");
}

// Função para busca em profundidade (DFS)
void busca_em_profundidade(Grafo* g, int inicio, int visitado[MAX_VERTICES]) {
    visitado[inicio] = 1;
    printf("%d ", inicio);

    for (int i = 0; i < g->num_vertices; i++) {
        if (g->matriz_adjacencia[inicio][i] != 0 && !visitado[i]) {
            busca_em_profundidade(g, i, visitado);
        }
    }
}

void dfs(Grafo* g, int inicio) {
    int visitado[MAX_VERTICES] = {0};
    printf("Busca em Profundidade a partir do vertice %d: ", inicio);
    busca_em_profundidade(g, inicio, visitado);
    printf("\n");
}

// Função para Dijkstra
void dijkstra(Grafo* g, int inicio) {
    int distancias[MAX_VERTICES], visitado[MAX_VERTICES], caminho[MAX_VERTICES];
    for (int i = 0; i < g->num_vertices; i++) {
        distancias[i] = INT_MAX;
        visitado[i] = 0;
        caminho[i] = -1;
    }
    distancias[inicio] = 0;

    for (int i = 0; i < g->num_vertices - 1; i++) {
        int u = -1, menor_distancia = INT_MAX;
        for (int j = 0; j < g->num_vertices; j++) {
            if (!visitado[j] && distancias[j] < menor_distancia) {
                u = j;
                menor_distancia = distancias[j];
            }
        }
        visitado[u] = 1;

        for (int v = 0; v < g->num_vertices; v++) {
            if (g->matriz_adjacencia[u][v] != 0 && !visitado[v]) {
                int nova_distancia = distancias[u] + g->matriz_adjacencia[u][v];
                if (nova_distancia < distancias[v]) {
                    distancias[v] = nova_distancia;
                    caminho[v] = u;
                }
            }
        }
    }

    printf("Dijkstra a partir do vertice %d:\n", inicio);
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Distancia de %d a %d: %d\n", inicio, i, distancias[i]);
    }
}

// Função para encontrar a árvore geradora mínima (Prim)
void arvore_geradora_minima(Grafo* g, int vertice_inicial) {
    int chave[MAX_VERTICES], pai[MAX_VERTICES], visitado[MAX_VERTICES];
    for (int i = 0; i < g->num_vertices; i++) {
        chave[i] = INT_MAX;
        pai[i] = -1;
        visitado[i] = 0;
    }
    chave[0] = 0;

    for (int i = 0; i < g->num_vertices - 1; i++) {
        int u = -1, menor_chave = INT_MAX;
        for (int v = 0; v < g->num_vertices; v++) {
            if (!visitado[v] && chave[v] < menor_chave) {
                u = v;
                menor_chave = chave[v];
            }
        }
        visitado[u] = 1;

        for (int v = 0; v < g->num_vertices; v++) {
            if (g->matriz_adjacencia[u][v] != 0 && !visitado[v] && g->matriz_adjacencia[u][v] < chave[v]) {
                chave[v] = g->matriz_adjacencia[u][v];
                pai[v] = u;
            }
        }
    }

    printf("Arvore Geradora Minima (Arestas):\n");
    for (int i = 1; i < g->num_vertices; i++) {
        if (pai[i] != -1) {
            printf("%d - %d (Peso: %d)\n", pai[i], i, g->matriz_adjacencia[i][pai[i]]);
        }
    }
}

// Função principal
#include <stdio.h>
#include <limits.h>

int main() {
    Grafo g;
    int num_vertices = 5;
    
    // Inicializa o grafo com o número de vértices
    inicializar_grafo(&g, num_vertices);

    // Adiciona as arestas ao grafo (ajuste conforme necessário)
    adicionar_aresta(&g, 0, 1, 1);
    adicionar_aresta(&g, 0, 2, 1);
    adicionar_aresta(&g, 1, 3, 1);
    adicionar_aresta(&g, 1, 4, 1);
    adicionar_aresta(&g, 2, 4, 1);
    adicionar_aresta(&g, 3, 4, 1);

    // TESTE 1: Busca em Largura
    busca_em_largura(&g, 0); // Chama a função de Busca em Largura

    // TESTE 2: Busca em Profundidade
    dfs(&g, 0); // Chama a função de Busca em Profundidade

    // TESTE 3: Algoritmo de Dijkstra
    dijkstra(&g, 0); // Chama a função de Dijkstra para encontrar o caminho mínimo

    // TESTE 4: Algoritmo da Árvore Geradora Mínima (Usando Prim)
    arvore_geradora_minima(&g, 0); // Chama a função para calcular a árvore geradora mínima

    return 0;
}

