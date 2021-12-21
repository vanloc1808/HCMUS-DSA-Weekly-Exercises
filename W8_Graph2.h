#ifndef _GRAPH2_H_
#define _GRAPH2_H_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

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
};

#endif // _GRAPH2_H_