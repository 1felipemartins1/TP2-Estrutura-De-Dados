#include "Functions.h"
#include <iostream>

int main()
{
    int n; // grafos ou vertices
    int m; // arestas ou trilhas
    int k; // portais
    int energia; // energia do personagem 
    int quantidade_de_portais; //quantidade de portais que o personagem pode usar 
    std::cin >> n >> m >> k;
    Graph grafo(n);

    // leitura das coordenadas
    for (int i = 0; i < n; i++)
    {
        float x, y;
        std::cin >> x >> y;
        grafo.setCoordinate(i, x, y);
    }

    // leitura de adjacencias
    for (int i = 0; i < m; i++)
    {
        int g1, g2;
        std::cin >> g1 >> g2;
        grafo.addEdge(g1, g2);
    }

    // leitura de portais
    for (int i = 0; i < k; i++){
        int g1, g2; 
        std::cin >> g1 >> g2; 
        grafo.addPortal(g1, g2);
    }
    
    std::cin >> energia >> quantidade_de_portais;
    
    int start = 0; // vértice inicial
    int end = n - 1; // vértice final

    if (grafo.canReachWithEnergyAndPortals(start, end, energia, quantidade_de_portais)) {
        std::cout << "1 1" << std::endl;
    } else {
        std::cout << "0 0" << std::endl;
        }

    return 0;
}
