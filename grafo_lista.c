#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

typedef struct no {
    int v;
    int peso;
    struct no *next;
}NO;

typedef NO *p_no;

typedef struct grafo {
    int n;
    p_no *adj;
}GRAFO;  

typedef GRAFO *p_grafo;

typedef struct item {
    int prioridade;
    int vertice;
}ITEM;

typedef struct fila_prioridade {
    int n;
    int tamanho;
    int max;
    ITEM *itens;
}FILA_PRIORIDADE;

typedef FILA_PRIORIDADE *p_fila_prioridade;

p_grafo cria_grafo(int n) {
    int i;
    p_grafo g = (p_grafo) malloc(sizeof(GRAFO));
    g -> n = n;
    g -> adj = (p_no *) malloc(n * sizeof(p_no));
    for (i = 0; i < n; i++) {
        g -> adj[i] = NULL;
    }
    return g;
}

void liberar_lista(p_no no) {
    if (no != NULL) {
        liberar_lista(no -> next);
        free(no);
    }
}

void destroi_grafo(p_grafo g) {
    int i;
    for (i = 0; i < g -> n; i++) {
        liberar_lista(g -> adj[i]);
    }
    free(g -> adj);
    free(g);
}

void insere_aresta(p_grafo g, int u, int v, int peso) {
    p_no novo = (p_no) malloc(sizeof(NO));
    novo->v = v;
    novo->peso = peso;
    novo->next = g->adj[u];
    g->adj[u] = novo;
}

void inserir_aresta_recursivo(p_grafo g, int u, int v, int peso) {
    insere_aresta(g, u, v, peso);
    insere_aresta(g, v, u, peso);
}


p_no remove_elemento(p_no no, int v) {
    if (no == NULL) {
        return NULL;
    }
    if (no -> v == v) {
        p_no aux = no -> next;
        free(no);
        return aux;
    }
    no -> next = remove_elemento(no -> next, v);
    return no;
}

void remove_aresta(p_grafo g, int u, int v) {
    g -> adj[u] = remove_elemento(g -> adj[u], v);
    g -> adj[v] = remove_elemento(g -> adj[v], u);
}

int possui_aresta(p_grafo g, int u, int v) {
    p_no no = g -> adj[u];
    while (no != NULL) {
        if (no -> v == v) {
            return 1;
        }
        no = no -> next;
    }
    return 0;
}

void imprime_aresta(p_grafo g) {
    int u;
    p_no no;
    for (u = 0; u < g -> n; u++) {
        no = g -> adj[u];
        while (no != NULL) {
            printf("%d %d %d\n", u, no -> v, no -> peso);
            no = no -> next;
        }
    }
}

void visita_recursiva(p_grafo g, int u, int *visitado) {
    p_no no = g -> adj[u];
    visitado[u] = 1;
    while (no != NULL) {
        if (!visitado[no -> v]) {
            visita_recursiva(g, no -> v, visitado);
        }
        no = no -> next;
    }
}

int * encontrar_componentes_conexas(p_grafo g) {
    int i, *visitado = (int *) malloc(g -> n * sizeof(int));
    for (i = 0; i < g -> n; i++) {
        visitado[i] = 0;
    }
    for (i = 0; i < g -> n; i++) {
        if (!visitado[i]) {
            visita_recursiva(g, i, visitado);
        }
    }
    return visitado;
}

/*
BUSCA EM PROFUNDADE 
*/

void busca_profundidade(p_grafo g, int u, int *visitado) {
    p_no no = g -> adj[u];

    visitado[u] = 1;

    while (no != NULL) {
        if (!visitado[no -> v]) {
            busca_profundidade(g, no -> v, visitado);
        }
        no = no -> next;
    }
}

int * encontra_caminho(p_grafo g, int u) {
    int i, *visitado = (int *) malloc(g -> n * sizeof(int));
    for (i = 0; i < g -> n; i++) {
        visitado[i] = 0;
    }
    busca_profundidade(g, u, visitado);
    return visitado;
}

void imprime_caminho(int *caminho, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", caminho[i]);
    }
    printf("\n");
}

void imprime_caminho_reverso(int *caminho, int n) {
    int i;
    for (i = n - 1; i >= 0; i--) {
        printf("%d ", caminho[i]);
    }
    printf("\n");
}

/*
BUSCA EM LARGURA
*/

void visita_topologica(p_grafo g, int u, int *visitado, int *ordem, int *pos) {
    p_no no = g -> adj[u];
    visitado[u] = 1;
    while (no != NULL) {
        if (!visitado[no -> v]) {
            visita_topologica(g, no -> v, visitado, ordem, pos);
        }
        no = no -> next;
    }
    ordem[*pos] = u;
    (*pos)--;
}

int * ordenacao_topologica(p_grafo g) {
    int i, *visitado = (int *) malloc(g -> n * sizeof(int));
    int *ordem = (int *) malloc(g -> n * sizeof(int));
    int pos = g -> n - 1;
    for (i = 0; i < g -> n; i++) {
        visitado[i] = 0;
    }
    for (i = 0; i < g -> n; i++) {
        if (!visitado[i]) {
            visita_topologica(g, i, visitado, ordem, &pos);
        }
    }
    return ordem;
}

p_fila_prioridade cria_fila_prioridade(int max) {
    p_fila_prioridade fp = (p_fila_prioridade) malloc(sizeof(FILA_PRIORIDADE));
    fp -> n = 0;
    fp -> tamanho = 0;
    fp -> max = max;
    fp -> itens = (ITEM *) malloc(max * sizeof(ITEM));
    return fp;
}

void insere_fila_prioridade(p_fila_prioridade fp, int prioridade, int vertice) {
    int i, j;
    if (fp -> n == fp -> max) {
        return;
    }
    i = fp -> n;
    j = (i - 1) / 2;
    while (i > 0 && fp -> itens[j].prioridade > prioridade) {
        fp -> itens[i] = fp -> itens[j];
        i = j;
        j = (i - 1) / 2;
    }
    fp -> itens[i].prioridade = prioridade;
    fp -> itens[i].vertice = vertice;
    fp -> n++;
}

void diminui_prioridade(p_fila_prioridade fp, int vertice, int prioridade) {
    int i, j;
    for (i = 0; i < fp -> n; i++) {
        if (fp -> itens[i].vertice == vertice) {
            break;
        }
    }
    if (i == fp -> n) {
        return;
    }
    fp -> itens[i].prioridade = prioridade;
    j = (i - 1) / 2;
    while (i > 0 && fp -> itens[j].prioridade > prioridade) {
        ITEM aux = fp -> itens[i];
        fp -> itens[i] = fp -> itens[j];
        fp -> itens[j] = aux;
        i = j;
        j = (i - 1) / 2;
    }
}

int fila_vazia(p_fila_prioridade fp) {
    return fp -> n == 0;
}

int prioridade (p_fila_prioridade fp, int vertice) {
    int i;
    for (i = 0; i < fp -> n; i++) {
        if (fp -> itens[i].vertice == vertice) {
            return fp -> itens[i].prioridade;
        }
    }
    return INT_MAX;
}

int extrai_minimum(p_fila_prioridade fp) {
    int i, j, min = fp -> itens[0].vertice;
    fp -> n--;
    fp -> itens[0] = fp -> itens[fp -> n];
    i = 0;
    while (1) {
        int e = 2 * i + 1;
        int d = e + 1;
        int menor;
        if (e >= fp -> n) {
            break;
        }
        if (d >= fp -> n || fp -> itens[e].prioridade < fp -> itens[d].prioridade) {
            menor = e;
        } else {
            menor = d;
        }
        if (fp -> itens[i].prioridade <= fp -> itens[menor].prioridade) {
            break;
        }
        ITEM aux = fp -> itens[i];
        fp -> itens[i] = fp -> itens[menor];
        fp -> itens[menor] = aux;
        i = menor;
    }
    return min;
}

void destroi_fila_prioridade(p_fila_prioridade fp) {
    free(fp -> itens);
    free(fp);
}

/*
DIJKSTRA
*/

int * dijkstra(p_grafo g, int s) {
    int i, *dist = (int *) malloc(g -> n * sizeof(int));
    p_fila_prioridade fp = cria_fila_prioridade(g -> n);
    for (i = 0; i < g -> n; i++) {
        dist[i] = INT_MAX;
        insere_fila_prioridade(fp, INT_MAX, i);
    }
    dist[s] = 0;
    diminui_prioridade(fp, s, 0);
    while (!fila_vazia(fp)) {
        int u = extrai_minimum(fp);
        p_no no = g -> adj[u];
        while (no != NULL) {
            if (dist[no -> v] > dist[u] + no -> peso) {
                dist[no -> v] = dist[u] + no -> peso;
                diminui_prioridade(fp, no -> v, dist[no -> v]);
            }
            no = no -> next;
        }
    }
    destroi_fila_prioridade(fp);
    return dist;
}

/*
ARVORE GERADORA MINIMA 
*/

int* arvore_geradora_minima(p_grafo g, int s) {
    int i, *pai = (int *) malloc(g -> n * sizeof(int));
    int *dist = (int *) malloc(g -> n * sizeof(int));
    p_fila_prioridade fp = cria_fila_prioridade(g -> n);
    for (i = 0; i < g -> n; i++) {
        dist[i] = INT_MAX;
        insere_fila_prioridade(fp, INT_MAX, i);
    }
    dist[s] = 0;
    diminui_prioridade(fp, s, 0);
    while (!fila_vazia(fp)) {
        int u = extrai_minimum(fp);
        p_no no = g -> adj[u];
        while (no != NULL) {
            if (prioridade(fp, no -> v) > no -> peso) {
                pai[no -> v] = u;
                dist[no -> v] = no -> peso;
                diminui_prioridade(fp, no -> v, no -> peso);
            }
            no = no -> next;
        }
    }
    destroi_fila_prioridade(fp);
    free(dist);
    return pai;
}

int main() {
    p_grafo g = cria_grafo(6);

    // Inserindo arestas no grafo
    insere_aresta(g, 0, 1, 4);
    insere_aresta(g, 0, 2, 3);
    insere_aresta(g, 1, 2, 1);
    insere_aresta(g, 1, 3, 2);
    insere_aresta(g, 2, 3, 4);
    insere_aresta(g, 3, 4, 2);
    insere_aresta(g, 4, 5, 6);

    // Imprimindo arestas para verificar o grafo
    printf("Arestas do Grafo:\n");
    imprime_aresta(g);

    // Busca em Largura
    printf("\nBusca em Largura a partir do vertice 0:\n");
    int *caminho_bfs = encontra_caminho(g, 0);
    imprime_caminho(caminho_bfs, g->n);
    free(caminho_bfs);

    // Busca em Profundidade
    printf("\nBusca em Profundidade a partir do vertice 0:\n");
    int *caminho_dfs = encontra_caminho(g, 0);
    imprime_caminho(caminho_dfs, g->n);
    free(caminho_dfs);

    // Dijkstra
    printf("\nMenor caminho a partir do vertice 0 (Dijkstra):\n");
    int *dist = dijkstra(g, 0);
    for (int i = 0; i < g->n; i++) {
        printf("Distancia para %d: %d\n", i, dist[i]);
    }
    free(dist);

    // Árvore Geradora Mínima
    printf("\nArvore Geradora Minima (Prim) com vertice 0 como raiz:\n");
    int *pai = arvore_geradora_minima(g, 0);
    for (int i = 1; i < g->n; i++) { // Começa do 1, pois 0 é a raiz
        printf("Pai de %d: %d\n", i, pai[i]);
    }
    free(pai);

    // Destruir grafo
    destroi_grafo(g);

    return 0;
}
