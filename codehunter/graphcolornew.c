//Graph Coloring Code

#include <stdio.h>
#include <stdbool.h>
#define MAX 100

int V;
int m;
int color[MAX];
int adj[MAX][MAX];
int adjSize[MAX]; // Keeps track of how many neighbors each vertex has
int solutionCount = 0; // To count the number of solutions found

void printSolution() {
    printf("Solution %d:\n", ++solutionCount);
    printf("Vertex Color Assignment:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d -> Color %d\n", i, color[i]);
    }
    printf("\n");
}

bool isSafe(int v, int c) {
    for (int i = 0; i < adjSize[v]; i++) {
        int neighbor = adj[v][i];
        if (color[neighbor] == c) {
            return false;
        }
    }
    return true;
}

void graphColoringUtil(int v, int m) {
    if (v == V) {
        printSolution();
        return;
    }
    
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            graphColoringUtil(v + 1, m); // Continue exploring
            color[v] = 0; // Backtrack
        }
    }
}

void graphColoring(int m) {
    // Initialize colors
    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }
    
    solutionCount = 0;
    graphColoringUtil(0, m);
    
    if (solutionCount == 0) {
        printf("No valid coloring found with %d colors.\n", m);
    } else {
        printf("Found %d different valid colorings.\n", solutionCount);
    }
}

int main() {
    int E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    
    // Initialize adjacency list sizes
    for (int i = 0; i < V; i++) {
        adjSize[i] = 0;
    }
    
    printf("Enter %d edges (u v) pairs (0-based indexing):\n", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Add edge u-v and v-u
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
    }
    
    printf("Enter the number of colors: ");
    scanf("%d", &m);
    
    graphColoring(m);
    
    return 0;
}

// Enter number of vertices: 5
// Enter number of edges: 5
// Enter 5 edges (u v) pairs (0-based indexing):
// 0 1
// 0 2
// 2 4
// 3 1
// 4 3
// Enter the number of colors: 3
