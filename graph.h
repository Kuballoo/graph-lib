#include <stdlib.h>

// vertex struct
typedef struct Vertex {
    int key;
    int value;
    struct Vertex *next;
} Vertex;

// graph struct
typedef struct Graph {
    int numVertices;
    Vertex **adjList;
} Graph;

// function creating new vertex
Vertex* createVertex(int key, int value) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->key = key;
    newVertex->value = value;
    newVertex->next = NULL;
    return newVertex;
}

// create new graph
Graph* createGraph(int numVertices) {
    Graph *newGraph = (Graph*)malloc(sizeof(Graph));
    newGraph->numVertices = numVertices;
    newGraph->adjList = (Vertex**)malloc(sizeof(Vertex*)*numVertices);

    for(int i=0; i<numVertices; i++) newGraph->adjList[i] = NULL;

    return newGraph;
}

// add new vertex to adj list on first position
void addVertex(Graph** graph, Vertex* vertex) {
    if((*graph)->numVertices <= vertex->key) return;
    Vertex* c = (Vertex*)malloc(sizeof(Vertex));
    c->key = vertex->key;
    c->value = vertex->value;
    c->next = vertex->next;
    c->next = (*graph)->adjList[c->key];
    (*graph)->adjList[c->key] = c;
}

// generate edge from vertex src to vertex des, if u set directed to 0, function add additional edge to oppostie side (for example 0: 1, 1: 0)
void addEdge(Graph** graph, Vertex* src, Vertex* des, int directed) {
    if((*graph)->numVertices <= src->key || (*graph)->numVertices <= des->key) return;
    if((*graph)->adjList[src->key] == NULL) addVertex(graph, src);
    if((*graph)->adjList[des->key] == NULL) addVertex(graph, des);

    Vertex* d = (Vertex*)malloc(sizeof(Vertex));
    d->key = des->key;
    d->value = des->value;
    d->next = (*graph)->adjList[src->key]->next;
    (*graph)->adjList[src->key]->next = d;

    if(!directed && src!=des) {
        Vertex* s = (Vertex*)malloc(sizeof(Vertex));
        s->key = src->key;
        s->value = src->value;
        s->next = (*graph)->adjList[des->key]->next;
        (*graph)->adjList[des->key]->next = s;
    }
}

// print neighborhood list of graph
void printGraph(Graph* graph) {
    for(int i=0; i<graph->numVertices; i++) {
        if(graph->adjList[i] == NULL) continue;
        printf("%d: ", graph->adjList[i]->key);
        Vertex* ver = graph->adjList[i]->next;
        while(ver != NULL) {
            printf("%d ", ver->key);
            ver = ver->next;
        }
        printf("\n");
    }
}

// increase or decrease number of vertices in graph
void increaseVerNum(Graph** graph, int newSize) {
    int numVertices = (*graph)->numVertices;
    (*graph)->numVertices = newSize;
    (*graph)->adjList = (Vertex**)realloc((*graph)->adjList, sizeof(Vertex*)*newSize);
    
    for(int i=numVertices-1; i<newSize; i++) (*graph)->adjList[i] = NULL;
}

// delete all edges from srcKey to desKey, if twoWay is true delete edges from desKey to srcKey
void delEdges(Graph** graph, int srcKey, int desKey, int twoWay) {
    Vertex* vertex = (*graph)->adjList[srcKey];
    Vertex* prev = vertex;
    while(vertex) {
        if(vertex->key == desKey) {
            prev->next = vertex->next;
            free(vertex);
            vertex = prev;
            
        }
        prev = vertex;
        vertex = vertex->next;
    }
    if(twoWay) {
        vertex = (*graph)->adjList[desKey];
        prev = vertex;
        while (vertex) {
            if(vertex->key == srcKey) {
                prev->next = vertex->next;
                free(vertex);
                vertex = prev;
                
            }
            prev = vertex;
            vertex = vertex->next;
        }
    }
}

// delete vertex with key == key and delete all edges connected with this vertex
void delVertex(Graph** graph, int key) {
    int numVertices = (*graph)->numVertices;
    if(numVertices <= key) return;
    for(int i=0; i<numVertices; i++) {
        Vertex* vertex = (*graph)->adjList[i];
        Vertex* prev = NULL;
        
        if(i == key) {
            vertex = vertex->next;
            while (vertex != NULL) {
                prev = vertex->next;
                free(vertex);
                vertex = prev;
            }
            (*graph)->adjList[i] = NULL;
        }
        while(vertex != NULL) {
            
            if(vertex->key == key) {
                prev->next = vertex->next;
                free(vertex);
                vertex = prev;
                vertex = vertex->next;
            } else {
                prev = vertex;
                vertex = vertex->next;
            }
        }
    }
}

