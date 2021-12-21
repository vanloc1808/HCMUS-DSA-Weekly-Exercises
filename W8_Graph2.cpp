#include "W8_Graph2.h"

Graph::Graph() {
    adjacencyList.resize(0);
    adjacencyMatrix.resize(0);
}

Graph::Graph(vector<Edge> const& edges, int n) {
    adjacencyList.resize(n);

    for (Edge const& edge : edges) {
        adjacencyList[edge.source].push_back(edge.destination);
        adjacencyMatrix[edge.source][edge.destination] = 1;
    }
}

 void Graph::addEdge(int source, int destination) {
    adjacencyList[source].push_back(destination);
    adjacencyMatrix[source][destination] = 1;
}

void Graph::readAdjacencyMatrix(string const& fileName) {
    ifstream file(fileName);

    if (file.is_open() == false) {
        cout << "File not found\n";

        return;
    }

    int n;
    file >> n;

    adjacencyMatrix.resize(n);
    adjacencyList.resize(n);

    for (int i = 0; i < n; i++) {
        adjacencyMatrix[i].resize(n);

        for (int j = 0; j < n; j++) {
            file >> adjacencyMatrix[i][j];
                
            if (adjacencyMatrix[i][j] == 1) {
                adjacencyList[i].push_back(j);
            }
        }
    }
}  

void Graph::readAdjacencyList(string const& fileName) {
    ifstream file(fileName);

    if (file.is_open() == false) {
        cout << "File not found\n";

        return;
    }

    int n;
    file >> n;

    string endline;
    getline(file, endline);

    adjacencyMatrix.resize(n);
    adjacencyList.resize(n);

    for (int i = 0; i < n; i++) {
        adjacencyMatrix[i].resize(n);

        for (int j = 0; j < n; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    vector<int> des;
    
    for (int i = 0; i < n; i++) {
        des.clear();

        string s;
        getline(file, s);

        stringstream ss(s);

        while (ss >> s) {
            des.push_back(stoi(s));
        }

       for (int j = 0; j < des.size(); j++) {
            adjacencyList[i].push_back(des[j]);
            adjacencyMatrix[i][des[j]] = 1;
        }
    }
}

void Graph::printAdjacencyMatrix() {
    cout << adjacencyMatrix.size() << "\n";
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }

        cout << "\n";
    }
}

void Graph::printAdjacencyList() {
    cout << adjacencyList.size() << "\n";

    for (int i = 0; i < adjacencyList.size(); i++) {
        for (int j = 0; j < adjacencyList[i].size(); j++) {
            cout << adjacencyList[i][j] << " ";
        }
            
        cout << "\n";
    }
} 

bool Graph::isDirectedOrUndirected() {
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i]) {
                return false;
            }
        }
    }

    return true;
}

int Graph::getEdgesNumber() {
    int n = adjacencyMatrix.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                ans++;
            }
        }
    }

    if (isDirectedOrUndirected()) {        
        return ans / 2;
    }

    return ans;
}

int Graph::getVerticesNumber() {
    return adjacencyMatrix.size();
}

 vector<int> Graph::degrees() {
    vector<int> ans;

    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        int degree = 0;

        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                degree++;
            }
        }

        ans.push_back(degree);
    }

    return ans;
 }