#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 20

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* proxima;
    struct Aresta* anterior;
} Aresta;

typedef struct Vertice {
    int dado;
    Aresta* arestas;
} Vertice;

Vertice* criarVertice(int dado) {
    Vertice* vertice = (Vertice*)malloc(sizeof(Vertice));
    vertice->dado = dado;
    vertice->arestas = NULL;
    return vertice;
}

 
void adicionarAresta(Vertice* vertice, int destino, int peso) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = vertice->arestas;
    novaAresta->anterior = NULL;
    if (vertice->arestas != NULL) {
        vertice->arestas->anterior = novaAresta;
    }
    vertice->arestas = novaAresta;
}

int encontrarMenorDistancia(int distancia[], int visitado[], int numVertices) {
    int menorDistancia = INT_MAX, menorIndice;

    for (int v = 0; v < numVertices; v++) {
        if (visitado[v] == 0 && distancia[v] <= menorDistancia) {
            menorDistancia = distancia[v];
            menorIndice = v;
        }
    }
    return menorIndice;
}

void imprimirCaminho(int caminho[], int j) {
    if (caminho[j] == -1) {
        return;
    }
    imprimirCaminho(caminho, caminho[j]);
    printf("%d ", j);
}

void imprimirResultado(int distancia[], int caminho[], int numVertices, int origem) {
    printf("Vertice\tDistancia de Origem\tCaminho\n");
    for (int i = 0; i < numVertices; i++) {
        if (i != origem) {
            printf("%d -> %d\t\t%d\t\t\t%d ", origem, i, distancia[i], origem);
            imprimirCaminho(caminho, i);
            printf("\n");
        }
    }
}

void dijkstra(Vertice* vertices[], int numVertices, int origem) {
    int distancia[numVertices]; 
    int visitado[numVertices];
    int caminho[numVertices];

    for (int i = 0; i < numVertices; i++) {
        distancia[i] = INT_MAX;
        visitado[i] = 0;
        caminho[i] = -1;
    }

    distancia[origem] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = encontrarMenorDistancia(distancia, visitado, numVertices);
        visitado[u] = 1;

        Aresta* aresta = vertices[u]->arestas;
        while (aresta != NULL) {
            int v = aresta->destino;
            if (!visitado[v] && distancia[u] != INT_MAX && distancia[u] + aresta->peso < distancia[v]) {
                distancia[v] = distancia[u] + aresta->peso;
                caminho[v] = u;
            }
            aresta = aresta->proxima;
        }
    }

    imprimirResultado(distancia, caminho, numVertices, origem);
}

int main() {
    Vertice* vertices[MAX_VERTICES];
    int numVertices = 0;

    printf("Digite o numero de vertices (ate %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    if (numVertices > MAX_VERTICES || numVertices <= 0) {
        printf("Numero de vertices invalido.\n");
        return 1;
    }

    for (int i = 0; i < numVertices; i++) {
        int dadoVertice;
        printf("Digite o valor do vertice %d: ", i + 1);
        scanf("%d", &dadoVertice);
        vertices[i] = criarVertice(dadoVertice);
    }

    for (int i = 0; i < numVertices; i++) {
        int numArestas;
        printf("Quantas arestas o vertice %d possui? ", vertices[i]->dado);
        scanf("%d", &numArestas);
        for (int j = 0; j < numArestas; j++) {
            int destinoVertice, peso;
            printf("Digite o destino e o peso da aresta %d: ", j + 1);
            scanf("%d %d", &destinoVertice, &peso);
            if (destinoVertice > 0 && destinoVertice <= numVertices) {
                adicionarAresta(vertices[i], destinoVertice, peso);
            } else {
                printf("Destino invalido.\n");
            }
        }
    }

    int origem;
    printf("Digite o vertice de origem: ");
    scanf("%d", &origem);
    if (origem <= 0 || origem > numVertices) {
        printf("Vertice de origem invalido.\n");
        return 1;
    }

    dijkstra(vertices, numVertices, origem - 1);

    for (int i = 0; i < numVertices; i++) {
        Aresta* aresta = vertices[i]->arestas;
        while (aresta != NULL) {
            Aresta* proximaAresta = aresta->proxima;
            free(aresta);
            aresta = proximaAresta;
        }
        free(vertices[i]);
    }

    return 0;
}
