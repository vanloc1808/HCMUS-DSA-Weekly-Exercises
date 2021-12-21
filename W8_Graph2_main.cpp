#include <iostream>
#include "W8_Graph2.h"

int main() {
    Graph g;
    g.readAdjacencyList("graph2.txt");
    g.printAdjacencyMatrix();
    cout << "The number of edges is: " << g.getEdgesNumber() << "\n";
    cout << "The number of vertices is: " << g.getVerticesNumber() << "\n";
    if (g.isDirectedOrUndirected()) {
        cout << "Undirected\n";

        vector<int> degrees = g.degrees();
        cout << "The degrees of each vertex is: \n";
        for (int i = 0; i < degrees.size(); i++) {
            cout << "Degree of vertex " << i << " is " << degrees[i] << "\n";
        }
    } else {
        cout << "Directed\n";
        vector<int> indeg = g.inDegrees();
        cout << "The in-degrees of each vertex is: \n";
        for (int i = 0; i < indeg.size(); i++) {
            cout << "In-degree of vertex " << i << " is " << indeg[i] << "\n";
        }

        vector<int> outdeg = g.outDegrees();
        cout << "The out-degrees of each vertex is: \n";
        for (int i = 0; i < outdeg.size(); i++) {
            cout << "Out-degree of vertex " << i << " is " << outdeg[i] << "\n";
        }
    }

    if (g.isBipartite()) {
        cout << "Bipartite\n";
    } else {
        cout << "Not bipartite\n";
    }

    if (g.isCompleteBiPartite()) {
        cout << "Complete bipartite\n";
    } else {
        cout << "Not complete bipartite\n";
    }
}

//g++-10 W8_Graph2.cpp W8_Graph2_main.cpp -o w8