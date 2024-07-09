#ifndef GRAPH_H
#define GRAPH_H

struct Coordinate {
    int x, y;
};

struct Node {
    int vertex; 
    double weight; // Peso da aresta
    Node* next; 
};

class Graph {
private:
    Node** adj; // Ponteiro para array de ponteiros para nós
    Coordinate* coordinates; // Array de coordenadas
    int numVertices; // Número de vértices no grafo

public:
    // Construtor da classe
    Graph(int vertices);

    // Destrutor da classe
    ~Graph();

    // Função para adicionar uma aresta direcionada do vértice u para o vértice v
    void addEdge(int u, int v);

    // Função para definir a coordenada de um vértice
    void setCoordinate(int vertex, int x, int y);

    // Função para imprimir a representação da lista de adjacência do grafo
    void printGraph();

    // Função para imprimir as coordenadas dos vértices
    void printCoordinates();

    // Função para calcular a distância euclidiana entre dois vértices
    double calculateDistance(int u, int v);

    // Funções de acesso
    int getNumVertices();
    Node* getAdjList(int vertex);
};

#endif
