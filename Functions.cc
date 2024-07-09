#include <iostream>
#include <cmath>
#include "Functions.h"

// Construtor da classe
Graph::Graph(int vertices) {
    numVertices = vertices;
    adj = new Node*[numVertices];
    coordinates = new Coordinate[numVertices];

    for (int i = 0; i < numVertices; ++i) {
        adj[i] = nullptr;
    }
}

// Destrutor da classe
Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i) {
        Node* current = adj[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adj;
    delete[] coordinates;
}

// Função para adicionar uma aresta direcionada do vértice u para o vértice v
void Graph::addEdge(int u, int v) {
    double weight = calculateDistance(u, v);
    Node* newNode = new Node;
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// Função para definir a coordenada de um vértice
void Graph::setCoordinate(int vertex, int x, int y) {
    if (vertex >= 0 && vertex < numVertices) {
        coordinates[vertex].x = x;
        coordinates[vertex].y = y;
    }
}

// Função para calcular a distância euclidiana entre dois vértices
double Graph::calculateDistance(int u, int v) {
    int dx = coordinates[u].x - coordinates[v].x;
    int dy = coordinates[u].y - coordinates[v].y;
    return std::sqrt(dx * dx + dy * dy);
}

// Função para imprimir a representação da lista de adjacência do grafo
void Graph::printGraph() {
    for (int i = 0; i < numVertices; ++i) {
        Node* current = adj[i];
        std::cout << "Lista de adjacência do vértice " << i << ": ";
        while (current != nullptr) {
            std::cout << "(" << current->vertex << ", " << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

// Função para imprimir as coordenadas dos vértices
void Graph::printCoordinates() {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Coordenada do vértice " << i << ": (" << coordinates[i].x << ", " << coordinates[i].y << ")" << std::endl;
    }
}

// Funções de acesso
int Graph::getNumVertices() {
    return numVertices;
}

Node* Graph::getAdjList(int vertex) {
    if (vertex >= 0 && vertex < numVertices) {
        return adj[vertex];
    }
    return nullptr;
}
