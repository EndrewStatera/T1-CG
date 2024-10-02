// C++ Program to Implement a Graph Using Adjacency Matrix
#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph();
    Graph(int n);
    vector<vector<int>> adj_matrix;
    void add_edge(int u, int v);
};
