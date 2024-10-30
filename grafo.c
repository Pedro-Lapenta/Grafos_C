#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int **adj;
    int n;
}Grafo;

typedef Grafo * p_grafo; //ponteiro para Grafo == p_grafo

p_grafo cria_grafo(int n) {
    int i;
    int j;

    p_grafo g = (p_grafo) malloc(sizeof(Grafo));

    g -> n = n;
    g -> adj = (int **) malloc(n * sizeof(int *));

    for (i = 0; i < n; i++) {
        g -> adj[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            g -> adj[i][j] = 0;
        }
    }

    return g;
}


void destroi_grafo(p_grafo g) {
    int i;
    for (i = 0; i < g -> n; i++) {
        free(g -> adj[i]);
    }
    free(g -> adj);
    free(g);
}

void insere_aresta (p_grafo g, int u, int v) {
    g -> adj[u][v] = 1;
    g -> adj[u][v] = 1;
}

void remove_aresta (p_grafo g, int u, int v) {
    g -> adj[u][v] = 0;
    g -> adj[u][v] = 0;
}       

int tem_aresta (p_grafo g, int u, int v) {
    return g -> adj[u][v];
}

p_grafo le_grafo() {
    int n, m, i, u, v;
    p_grafo g;

    scanf("%d %d", &n, &m);
    g = cria_grafo(n);

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        insere_aresta(g, u, v);
    }

    return g;
}

void imprime_aresta(p_grafo g) {
    int u, v;
    for (u = 0; u < g -> n; u++) {
        for (v = 0; v < g -> n; v++) {
            if (tem_aresta(g, u, v)) {
                printf("%d %d\n", u, v);
            }
        }
    }

}

void imprime_matriz_adjacencia(p_grafo g) {
    int i, j;
    printf("Adjacency Matrix:\n");
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}



int main() {
    p_grafo g;
    int n = 5; // Example size of the graph

    // Create a graph
    g = cria_grafo(n);

    // Insert some edges
    insere_aresta(g, 0, 1);
    insere_aresta(g, 1, 2);
    insere_aresta(g, 2, 3);
    insere_aresta(g, 3, 4);
    insere_aresta(g, 4, 0);

    // Check if an edge exists
    if (tem_aresta(g, 0, 1)) {
        printf("Edge 0 -> 1 exists\n");
    }

    // Print all edges
    imprime_aresta(g);

    // Remove an edge
    remove_aresta(g, 0, 1);

    // Print all edges again to see the change
    imprime_aresta(g);

    // Print the adjacency matrix
    imprime_matriz_adjacencia(g);

    // Destroy the graph
    destroi_grafo(g);
}



