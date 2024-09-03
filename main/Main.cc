/******************************************************************************

5 4 2
0 1
0 0
0 2
1 1
10 2
0 1
0 3
1 4
2 4
0 2
3 4
1 1


*******************************************************************************/
#include "Functions.h"
#include <iostream>

int main()
{
    int n;
    int m;
    int k;
    int energia;
    int quantidade_de_portais;
    std::cin >> n >> m >> k;
    Graph grafo(n);

    for (int i = 0; i < n; i++)
    {
        float x, y;
        std::cin >> x >> y;
        grafo.setCoordinate(i, x, y);
    }

    for (int i = 0; i < m; i++)
    {
        int g1, g2;
        std::cin >> g1 >> g2;
        grafo.addEdge(g1, g2);
    }

    for (int i = 0; i < k; i++)
    {
        int g1, g2;
        std::cin >> g1 >> g2;
        grafo.addPortal(g1, g2);
    }

    std::cin >> energia >> quantidade_de_portais;

    int start = 0;
    int end = n - 1;

    if (grafo.algoritmo_dijkstra_lista(start, end, energia, quantidade_de_portais))
    {
        std::cout << "1 ";
    }
    else
    {
        std::cout << "0 ";
    }

    if (grafo.algoritmo_aestrela_lista(start, end, energia, quantidade_de_portais))
    {
        std::cout << "1" << std::endl;
    }
    else
    {
        std::cout << "0" << std::endl;
    }

    return 0;
}
