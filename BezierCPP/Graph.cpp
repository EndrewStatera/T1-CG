#include "Graph.h"

// Constructor to initialize the graph with 'n' vertices
Graph::Graph()
{
    adj_matrix = vector<vector<int> >(100, vector<int>(100, 0));
}
Graph::Graph(int n)
{
    adj_matrix = vector<vector<int> >(n, vector<int>(n, 0));
}

// Function to add an edge between vertices 'u' and 'v'
// of the graph
void Graph::add_edge(int u, int v)
{
    // Set edge from u to v
    adj_matrix[u][v] = 1;
    // Set edge from v to u (for undirected graph)
    adj_matrix[v][u] = 1;
}
