#include "Test.h"
#include "Functions.h"
#include <iostream>
int main()
{

    int n; // grafos ou vertices
    int m; // arestas ou trilhas
    int k; // portais

    std::cin >> n >> m >> k;
    Graph grafo(n);

    // leitura das coordenadas 
    for (int i = 0; i < n; i++)
    {
        float x,y;
        std::cin >> x >> y; 
        grafo.setCoordinate(i,x,y);
    }

    // leitura de adjacencias 
    for (int i = 0; i < m; i++){
        int g1, g2;
        std::cin >> g1 >> g2; 
        grafo.addEdge(g1,g2); 
    }
    grafo.printGraph();
    grafo.printCoordinates();
}