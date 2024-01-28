#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"

int genRandNum(int min, int max) {
  int num = (rand() % (max - min + 1)) + min;
  return (num);
}

int main() {
  srand(time(NULL));

  Vertex *s1 = createVertex(0, 13);
  Vertex *s2 = createVertex(1, 44);
  Vertex *s3 = createVertex(3, 69);
  
  Graph *g = createGraph(10);
  addVertex(&g, s2);
  addVertex(&g, s3);
  addEdge(&g, s1, s3, 0);
  addEdge(&g, s2, s3, 0);
  addEdge(&g, s2, s3, 0);
  addEdge(&g, s1, s2, 0);
  addEdge(&g, s1, s2, 0);
  addEdge(&g, s1, s3, 0);
  printGraph(g);
  delEdges(&g, 0, 3, 0);
  printGraph(g);
  return 0;
}