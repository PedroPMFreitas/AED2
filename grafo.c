#include <stdio.h>
#include <stdlib.h>

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

void imprimirGrafo(Vertice* vertices[], int numVertices) {
    printf("Dados armazenados:\n");
    for (int i = 0; i < numVertices; i++) {
        Vertice* vertice = vertices[i];
        printf("Vertice %d:\n", i + 1);
        Aresta* aresta = vertice->arestas;
        while (aresta != NULL) {
            printf("   -> Vertice %d (Peso: %d)\n", aresta->destino, aresta->peso);
            aresta = aresta->proxima;
        }
        printf("\n");
    }
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

    imprimirGrafo(vertices, numVertices);

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
