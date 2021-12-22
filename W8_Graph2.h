#ifndef _GRAPH2_H_
#define _GRAPH2_H_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <queue>
#include <climits>
#include <list>

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

    void dfs(int vertex, vector<bool>& visited, vector<int> verticesList); //depth-first search

    pair<int, int> getConnectedComponentsNumberAndHowManyTrees(); //get the number of connected components in the graph

    void cutVerticesUlti(int vertex, vector<bool>& visited, vector<int>& discoveryTimes, vector<int>& lowTimes, int& time, int parent, vector<bool>& isCV);
    
    int getCutVerticesNumber(); //get the number of cut vertices in the graph (aka articulation points)

    void bridgeUtil(int vertex, vector<bool>& visited, vector<int>& discoveryTimes, vector<int>& lowTimes, vector<int>& parent, vector<Edge>& bridges);

    int getBridgesNumber(); //get the number of bridges in the graph

    Graph baseUndirectedGraph(); //use for directed graphs only, if the graph is already undirected, this will return itself

    vector<vector<int>> getComplementGraph(); //get the adjacency matrix of the complement graph of this graph (undirected graphs only)

    vector<vector<int>> getConverseGraph(); //get the adjacency matrix of the converse graph of this graph (directed graphs only)
};

#endif // _GRAPH2_H_