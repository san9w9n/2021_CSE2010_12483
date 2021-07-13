#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Graph {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int n; // the number of vertex
} Graph;
 
void init(Graph *g) {
    int i, j;
    g->n = 0;
    for (i=0; i < MAX_VERTICES; i++) {
        for (j=0; j < MAX_VERTICES; j++)
            g->adjMatrix[i][j] = 0;
    }
}

void insertVertex(Graph *g, int v) {
    if (g->n == MAX_VERTICES) {
        // graph 정점 가득 찬 상황
        printf("Too many vertexes\n");
        return;
    }
    g->n++;
}

void insertEdge(Graph *g, int u, int v) {
    if (u >= g->n || v >= g->n) {
        printf("Wrong vertex number!\n");
        return;
    }
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1;
}

int dfs(Graph *g, int v) {
    int w, sum = 0;
    visited[v] = TRUE;
    printf("%d -> ", v);

    for (w=0; w < MAX_VERTICES; w++) {
        if (g->adjMatrix[v][w] > 0 && visited[w] == FALSE) {
            sum = dfs(g, w) + g->adjMatrix[v][w];
        }
    }
    return sum;
}

int main() {
    Graph g;
    init(&g);

    for (int i=0; i < MAX_VERTICES; i++) visited[i] = FALSE; //visited 초기화
    for (int i=0; i < 7; i++) insertVertex(&g, i);
    insertEdge(&g, 0, 4);
    insertEdge(&g, 0, 6);
    insertEdge(&g, 1, 3);
    insertEdge(&g, 3, 5);
    insertEdge(&g, 4, 1);
    insertEdge(&g, 4, 2);
    insertEdge(&g, 6, 2);

    printf("!!!!!!!!!!!!!!!!!%d\n",dfs(&g, 0));
}