# Escapando da Floresta da Neblina 🌲✨

Este é o repositório do Trabalho Prático 2 da disciplina **DCC205 - Estruturas de Dados** do Departamento de Ciência da Computação (DCC) da UFMG, orientado pelos professores Wagner Meira Jr. e Eder Ferreira de Figueiredo. O objetivo deste projeto é implementar algoritmos clássicos de busca em grafos, adaptados para resolver o problema do herói Linque, que precisa escapar de uma floresta envolta por uma neblina mágica.

## Descrição do Problema

Linque, um herói lendário, está perdido na **Floresta da Neblina**. A floresta é composta por `n` clareiras conectadas por `m` trilhas unidirecionais. Algumas clareiras possuem portais mágicos que não consomem energia para serem atravessados, mas podem ser usados no máximo `k` vezes. Linque inicia na clareira `0` e precisa chegar na clareira `n-1`, utilizando no máximo `s` de energia. 

O objetivo é determinar se Linque consegue escapar da floresta antes que sua energia se esgote e sem utilizar mais portais do que o permitido.

## Algoritmos Implementados

- **Dijkstra**: Um algoritmo clássico para encontrar o caminho de menor custo em grafos, adaptado para levar em conta o consumo de energia e o uso de portais.
- **A***: Algoritmo de busca heurística que utiliza a distância euclidiana como função heurística para encontrar o caminho mais curto até a saída da floresta.

### Modificações Específicas

Ambos os algoritmos foram adaptados para parar a busca assim que o vértice de destino é removido da fila de prioridades. Além disso, implementamos um TAD de fila de prioridades modificado para satisfazer as condições do problema.

## Estruturas de Dados

- **TAD de Grafo**: Implementado tanto com Matriz de Adjacência quanto com Lista de Adjacência. A lista de adjacência é usada na VPL devido a restrições de memória.
- **TAD de Fila de Prioridades**: Modificado para gerenciar a energia consumida e o número de portais usados.

## Como Executar

1. Compile o código utilizando um compilador C++.
2. Execute o programa passando o arquivo de entrada padrão conforme o formato descrito abaixo.

### Formato de Entrada

A entrada consiste em:
- `n`, `m`, `k`: Número de clareiras, trilhas e portais.
- Coordenadas de cada clareira em um plano (n linhas).
- Conexões entre clareiras por trilhas (m linhas).
- Conexões entre clareiras por portais (k linhas).
- `s`, `q`: Energia disponível e número máximo de portais que podem ser usados.

### Formato de Saída

O programa deve imprimir dois inteiros:
- 1 se é possível escapar da floresta utilizando o algoritmo de Dijkstra e 0 caso contrário.
- 1 se é possível escapar utilizando o algoritmo A* e 0 caso contrário.

## Análise Experimental

Este projeto também inclui uma análise experimental comparando a eficiência das implementações de Matriz de Adjacência e Lista de Adjacência.

## Conclusão

Este trabalho explora algoritmos clássicos de busca em grafos, adaptando-os para resolver problemas com restrições de recursos, como energia e uso de portais. A implementação bem-sucedida desses algoritmos destaca a importância da escolha de estruturas de dados adequadas e da modificação de algoritmos para atender às exigências específicas de um problema.

## Referências

- [Algoritmo de Dijkstra](https://www.youtube.com/watch?v=Kue4UUxstoU&ab_channel=MaratonaUFMG)
- [Algoritmo A*](https://pt.wikipedia.org/wiki/Algoritmo_A*)

## Contato

Para mais informações, sinta-se à vontade para entrar em contato:
- **Email**: [14felipemartins08@gmail.com]

