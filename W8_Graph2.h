#ifndef _GRAPH2_H_
#define _GRAPH2_H_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

//Algorithms on graph
struct Edge {
    int source;

    int destination;
};

class Graph {
public:
    vector<vector<int>> adjacencyMatrix;

    vector<vector<int>> adjacencyList;

    Graph();

    //n is the number of vertices
    Graph(vector<Edge> const& edges, int n);

    void addEdge(int source, int destination);

    void readAdjacencyMatrix(string const& fileName);

    void readAdjacencyList(string const& fileName);

    void printAdjacencyMatrix();

    void printAdjacencyList(); 

    bool isDirectedOrUndirected();

    int getEdgesNumber();

    int getVerticesNumber();

    vector<int> degrees(); //degrees of each vertex in the graph, used for undirected graphs only

    vector<int> inDegrees(); //in-degrees of each vertex in the graph, used for directed graphs only

    vector<int> outDegrees(); //out-degrees of each vertex in the graph, used for directed graphs only

    vector<int> isolatedVertices(); //get the isolated vertices (vertices with degree = 0 in undirected graphs or in-degree + out-degree = 0 in directed graphs)

    vector<int> getLeafVertices();

    bool isCompleteGraph(); //check if the graph is complete 

    bool isCircularGraph(); //check if the graph is circular (cyclic)

    bool isBipartite(); //check if the graph is bipartite (two-colorable)

    bool isCompleteBiPartite(); //check if the graph is complete bipartite (two-colorable)
};

#endif // _GRAPH2_H_