#include <iostream>
#include <cmath>
#include "Functions.h"

#define INF 1e9

Graph::Graph(int vertices)
{
    numVertices = vertices;
    adj = new Node *[numVertices];
    coordinates = new Coordinate[numVertices];
    edges = new Edge[numVertices * numVertices];
    portal = new Portal[numVertices * numVertices];
    edgeCount = 0;
    portalCount = 0;

    for (int i = 0; i < numVertices; ++i)
    {
        adj[i] = nullptr;
    }
}

Graph::~Graph()
{
    for (int i = 0; i < numVertices; ++i)
    {
        Node *current = adj[i];
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adj;
    delete[] coordinates;
    delete[] edges;
    delete[] portal;
}

void Graph::addEdge(int u, int v)
{
    float weight = calculateDistance(u, v);
    Node *newNode = new Node;
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = adj[u];
    adj[u] = newNode;

    edges[edgeCount].u = u;
    edges[edgeCount].v = v;
    edges[edgeCount].weight = weight;
    edgeCount++;
}

void Graph::addPortal(int u, int v)
{
    float weight = 0;
    Node *newNode = new Node;
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = adj[u];
    adj[u] = newNode;

    portal[portalCount].u = u;
    portal[portalCount].v = v;
    portal[portalCount].weight = weight;
    portalCount++;
}

void Graph::setCoordinate(int vertex, float x, float y)
{
    if (vertex >= 0 && vertex < numVertices)
    {
        coordinates[vertex].x = x;
        coordinates[vertex].y = y;
    }
}

float Graph::calculateDistance(int u, int v)
{
    float dx = coordinates[u].x - coordinates[v].x;
    float dy = coordinates[u].y - coordinates[v].y;
    return std::sqrt(dx * dx + dy * dy);
}

void Graph::printGraph()
{
    for (int i = 0; i < numVertices; ++i)
    {
        Node *current = adj[i];
        std::cout << "Lista de adjacência do vértice " << i << ": ";
        while (current != nullptr)
        {
            std::cout << "(" << current->vertex << ", " << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

void Graph::printCoordinates()
{
    for (int i = 0; i < numVertices; ++i)
    {
        std::cout << "Coordenada do vértice " << i << ": (" << coordinates[i].x << ", " << coordinates[i].y << ")" << std::endl;
    }
}

void Graph::printEdges()
{
    for (int i = 0; i < edgeCount; ++i)
    {
        std::cout << "Aresta do vértice " << edges[i].u << " para o vértice " << edges[i].v << " com peso " << edges[i].weight << std::endl;
    }
}

void Graph::printPortal()
{
    for (int i = 0; i < portalCount; ++i)
    {
        std::cout << "Aresta do portal " << portal[i].u << " para o vértice " << portal[i].v << " com peso " << portal[i].weight << std::endl;
    }
}

int Graph::getNumVertices()
{
    return numVertices;
}

Node *Graph::getAdjList(int vertex)
{
    if (vertex >= 0 && vertex < numVertices)
    {
        return adj[vertex];
    }
    return nullptr;
}

// função heurística de calcular distancia
float heuristic(int u, int v, Coordinate *coordinates)
{
    float dx = coordinates[u].x - coordinates[v].x;
    float dy = coordinates[u].y - coordinates[v].y;
    return std::sqrt(dx * dx + dy * dy);
}

// função dijkstra para lista de adjacencia
bool Graph::algoritmo_dijkstra_lista(int start, int end, float energy, int maxPortals)
{
    float *dist = new float[numVertices];
    bool *visited = new bool[numVertices];
    int *portalUsed = new int[numVertices];

    for (int i = 0; i < numVertices; ++i)
    {
        dist[i] = INF;
        visited[i] = false;
        portalUsed[i] = 0;
    }

    dist[start] = 0;

    for (int i = 0; i < numVertices; ++i)
    {
        // encontrar o vértice com a menor distância que ainda não foi visitado
        int u = -1;
        for (int j = 0; j < numVertices; ++j)
        {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF)
            break;
        if (u == end)
            break; // break se alcançar o destino

        visited[u] = true;

        // atualizar as distâncias dos vizinhos de u
        for (Node *node = adj[u]; node != nullptr; node = node->next)
        {
            int v = node->vertex;
            float weight = node->weight;

            if (weight > 0)
            { // trilha com distancia
                if (dist[u] + weight < dist[v] && dist[u] + weight <= energy)
                {
                    dist[v] = dist[u] + weight;
                    portalUsed[v] = portalUsed[u];
                }
            }
            else
            { // portal
                if (portalUsed[u] < maxPortals && dist[u] < dist[v])
                {
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
// função A* para lista de adjacência
bool Graph::algoritmo_aestrela_lista(int start, int end, float energy, int maxPortals)
{
    struct A_estrela
    {
        int vertex;
        float fScore;
        float gScore;
        int portalsUsed;
    };

    A_estrela *nodes = new A_estrela[numVertices];
    bool *visited = new bool[numVertices];

    for (int i = 0; i < numVertices; ++i)
    {
        nodes[i].vertex = i;
        nodes[i].fScore = INF;
        nodes[i].gScore = INF;
        nodes[i].portalsUsed = 0;
        visited[i] = false;
    }

    // inicializa o nó de partida
    nodes[start].gScore = 0;
    nodes[start].fScore = calculateDistance(start, end);

    while (true)
    {
        int u = -1;

        // encontra o nó com o menor fScore que ainda não foi visitado
        for (int i = 0; i < numVertices; ++i)
        {
            if (!visited[i] && (u == -1 || nodes[i].fScore < nodes[u].fScore))
            {
                u = i;
            }
        }

        if (u == -1 || nodes[u].fScore == INF)
            break;
        if (u == end)
            break;

        visited[u] = true;

        // percorre todos os vizinhos do nó atual
        for (Node *node = adj[u]; node != nullptr; node = node->next)
        {
            int v = node->vertex;
            float weight = node->weight;
            float tentative_gScore = nodes[u].gScore + weight;

            if (weight > 0)
            {
                if (tentative_gScore < nodes[v].gScore && tentative_gScore <= energy)
                {
                    nodes[v].gScore = tentative_gScore;
                    nodes[v].fScore = nodes[v].gScore + calculateDistance(v, end);
                    nodes[v].portalsUsed = nodes[u].portalsUsed;
                }
            }
            else
            {
                float portalCost = calculateDistance(u, v);
                if (nodes[u].portalsUsed < maxPortals && nodes[u].gScore + portalCost < nodes[v].gScore)
                {
                    nodes[v].gScore = nodes[u].gScore + portalCost;
                    nodes[v].fScore = nodes[v].gScore + calculateDistance(v, end);
                    nodes[v].portalsUsed = nodes[u].portalsUsed + 1;
                }
            }
        }
    }

    bool result = (nodes[end].gScore <= energy && nodes[end].portalsUsed <= maxPortals);

    delete[] nodes;
    delete[] visited;

    return result;
}
