# Graph Library
Repositório dedicado aos trabalhos da disciplina Teoria dos Grafos (COS242) do período 2023.2 na UFRJ.
Os trabalhos consistem em desenvolver uma biblioteca para representação e manipulação de grafos.

## Funcionalidades
A biblioteca provê as seguintes funcionalidades:

Grafos sem peso:
* Ler grafo de arquivo
* Realizar buscas BFS e DFS
* Encontrar componentes conexos
* Calcular menor distância entre vértices
* Calcular diâmetro do grafo
* Gerar arquivo com informações do grafo

Grafos com peso (direcionados ou não-direcionados):
* Ler grafo de arquivo
* Calcular distância e menor caminho entre vértices (Dijkstra usando Heap)
* Calcular distância e menor caminho entre vértices (Dijkstra sem Heap)
* Encontrar fluxo máximo

## Instruções
Para executar a interface de testes, use o comando:
```bash
make run
```
