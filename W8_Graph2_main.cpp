#include <iostream>
#include "W8_Graph2.h"

int main() {
    Graph g;
    g.readAdjacencyList("graph2.txt");
    g.printAdjacencyMatrix();
    if (g.isDirectedOrUndirected()) {
        cout << "Undirected\n";
    } else {
        cout << "Directed\n";
    }
    
    cout << "The number of edges is: " << g.getEdgesNumber() << "\n";
    cout << "The number of vertices is: " << g.getVerticesNumber() << "\n";

    vector<int> degrees = g.degrees();
    cout << "The degrees of each vertex is: \n";
    for (int i = 0; i < degrees.size(); i++) {
        cout << "Degree of vertex " << i << " is " << degrees[i] << "\n";
    }
}

//g++ W8_Graph2.cpp W8_Graph2_main.cpp -o w8