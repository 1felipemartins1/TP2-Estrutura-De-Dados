#include <iostream>
#include <cmath>
#include "Functions.h"

#define INF 1e9

// Construtor da classe
Graph::Graph(int vertices) {
    numVertices = vertices;
    adj = new Node*[numVertices];
    coordinates = new Coordinate[numVertices];
    edges = new Edge[numVertices * numVertices]; // Máximo possível de arestas
    portal = new Portal[numVertices * numVertices]; // Máximo possível de portais
    edgeCount = 0;
    portalCount = 0;

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
    delete[] edges;
    delete[] portal;
}

// Função para adicionar uma aresta direcionada do vértice u para o vértice v
void Graph::addEdge(int u, int v) {
    float weight = calculateDistance(u, v);
    Node* newNode = new Node;
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = adj[u];
    adj[u] = newNode;

    // Armazenar o par (u, v) na estrutura Edge
    edges[edgeCount].u = u;
    edges[edgeCount].v = v;
    edges[edgeCount].weight = weight;
    edgeCount++;
}

void Graph::addPortal(int u, int v){
    float weight = 0;
    Node* newNode = new Node;
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = adj[u];
    adj[u] = newNode;

    portal[portalCount].u = u;
    portal[portalCount].v = v;
    portal[portalCount].weight = weight;
    portalCount++;
}

// Função para definir a coordenada de um vértice
void Graph::setCoordinate(int vertex, float x, float y) {
    if (vertex >= 0 && vertex < numVertices) {
        coordinates[vertex].x = x;
        coordinates[vertex].y = y;
    }
}

// Função para calcular a distância euclidiana entre dois vértices
float Graph::calculateDistance(int u, int v) {
    float dx = coordinates[u].x - coordinates[v].x;
    float dy = coordinates[u].y - coordinates[v].y;
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

// Função para imprimir os pares de vértices
void Graph::printEdges() {
    for (int i = 0; i < edgeCount; ++i) {
        std::cout << "Aresta do vértice " << edges[i].u << " para o vértice " << edges[i].v << " com peso " << edges[i].weight << std::endl;
    }
}

void Graph::printPortal(){
    for(int i = 0; i < portalCount; i++){
        std:: cout << "Aresta do portal " << portal[i].u << " para o vértice " << portal[i].v << " com o peso " << portal[i].weight << std::endl;
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

// Função para verificar se o destino é alcançável com a energia e portais disponíveis
bool Graph::canReachWithEnergyAndPortals(int start, int end, float energy, int maxPortals) {
    float* dist = new float[numVertices];
    bool* visited = new bool[numVertices];
    int* portalUsed = new int[numVertices];

    for (int i = 0; i < numVertices; ++i) {
        dist[i] = INF;
        visited[i] = false;
        portalUsed[i] = 0;
    }

    dist[start] = 0;

    for (int i = 0; i < numVertices; ++i) {
        // Encontrar o vértice com a menor distância que ainda não foi visitado
        int u = -1;
        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF) break;
        if (u == end) break; // Parar ao alcançar o destino

        visited[u] = true;

        // Atualizar as distâncias dos vizinhos de u
        for (Node* node = adj[u]; node != nullptr; node = node->next) {
            int v = node->vertex;
            float weight = node->weight;

            if (weight > 0) { // Aresta comum
                if (dist[u] + weight < dist[v] && dist[u] + weight <= energy) {
                    dist[v] = dist[u] + weight;
                    portalUsed[v] = portalUsed[u];
                }
            } else { // Portal
                if (portalUsed[u] < maxPortals && dist[u] < dist[v]) {
                    dist[v] = dist[u];
                    portalUsed[v] = portalUsed[u] + 1;
                }
            }
        }
    }

    bool result = (dist[end] <= energy);

    delete[] dist;
    delete[] visited;
    delete[] portalUsed;

    return result;
}
