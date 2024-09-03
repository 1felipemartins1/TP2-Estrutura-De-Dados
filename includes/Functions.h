#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Coordinate
{
    float x, y;
};

struct Node //nó usado para a lista 
{
    int vertex;
    float weight; 
    Node *next;
};
struct Portal
{
    int u;
    int v;
    float weight;
};

struct Edge // aresta usada na lista para o grafo 
{
    int u;
    int v;
    float weight;
};

class Graph
{
private:
    Node **adj;              // ponteiro para array de ponteiros para nós
    Coordinate *coordinates; // array de coordenadas
    int numVertices;         // número de vértices no grafo
    Edge *edges;             // array de pares de arestas
    Portal *portal;          // array de portais
    int edgeCount;           // contador de arestas
    int portalCount;         // contador de portais

public:
    // Construtor da classe
    Graph(int vertices);

    // destrutor da classe
    ~Graph();

    // função para adicionar uma aresta direcionada do vértice u para o vértice v
    void addEdge(int u, int v);

    // função paara adicionar uma aresta portal direcionada do vertice u para o vértice v (portais tem weight = 0)
    void addPortal(int u, int v);

    //função para definir a coordenada de um vértice
    void setCoordinate(int vertex, float x, float y);

    // função para calcular a distância euclidiana entre dois vértices
    float calculateDistance(int u, int v);

    // função para imprimir a representação da lista de adjacência do grafo
    void printGraph();

    // função para imprimir as coordenadas dos vértices
    void printCoordinates();

    // função para imprimir os pares portais
    void printPortal();

    // função para imprimir os pares de vértices
    void printEdges();

    // funções de acesso
    int getNumVertices();
    Node *getAdjList(int vertex);

    // Função para verificar se o destino é alcançável com a energia e portais disponíveis usando Dijkstra
    bool algoritmo_dijkstra_lista(int start, int end, float energy, int maxPortals);

    // Função para verificar se o destino é alcançável com a energia e portais disponíveis usando A*
    bool algoritmo_aestrela_lista(int start, int end, float energy, int maxPortals);
};

#endif
