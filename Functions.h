#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Coordinate {
    float x, y;
};

struct Node {
    int vertex;
    float weight; // Peso da aresta
    Node* next;
};

struct Portal {
    int u; 
    int v; 
    float weight; 
};

struct Edge {
    int u;
    int v;
    float weight;
};

class Graph {
private:
    Node** adj; // Ponteiro para array de ponteiros para nós
    Coordinate* coordinates; // Array de coordenadas
    int numVertices; // Número de vértices no grafo
    Edge* edges; // Array de pares de arestas
    Portal* portal; // Array de portais 
    int edgeCount; // Contador de arestas
    int portalCount; // Contador de portais 
public:
    // Construtor da classe
    Graph(int vertices);

    // Destrutor da classe
    ~Graph();

    // Função para adicionar uma aresta direcionada do vértice u para o vértice v
    void addEdge(int u, int v);

    // Função para adicionar uma aresta portal direcionada do vertice u para o vértice v (portais tem weight = 0)
    void addPortal(int u, int v);

    // Função para definir a coordenada de um vértice
    void setCoordinate(int vertex, float x, float y);

    // Função para calcular a distância euclidiana entre dois vértices
    float calculateDistance(int u, int v);

    // Função para imprimir a representação da lista de adjacência do grafo
    void printGraph();

    // Função para imprimir as coordenadas dos vértices
    void printCoordinates();

    // Função para imprimir os pares portais
    void printPortal();

    // Função para imprimir os pares de vértices
    void printEdges();

    // Função que implementa o algoritmo de Dijkstra e verifica se o destino é alcançável
    bool canReachWithEnergyAndPortals(int start, int end, float energy, int maxPortals);

    // Funções de acesso
    int getNumVertices();
    Node* getAdjList(int vertex);
};

#endif
