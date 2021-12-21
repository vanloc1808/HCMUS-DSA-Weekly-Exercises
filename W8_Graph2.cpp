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

 vector<int> Graph::inDegrees() {
    vector<int> ans;

    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        int degree = 0;

        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[j][i] == 1) {
                degree++;
            }
        }

        ans.push_back(degree);
    }

    return ans;
 }

 vector<int> Graph::outDegrees() {
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

 vector<int> Graph::isolatedVertices() {
     vector<int> ans;

    if (isDirectedOrUndirected()) {
        vector<int> degree = degrees();

        for (int i = 0; i < degree.size(); i++) {
            if (degree[i] == 0) {
                ans.push_back(i);
            }
        }
    } else {
        vector<int> inDegree = inDegrees();
        vector<int> outDegree = outDegrees();

        for (int i = 0; i < inDegree.size(); i++) {
            if (inDegree[i] + outDegree[i] == 0) {
                ans.push_back(i);
            }
        }
    }

     return ans;
}

vector<int> Graph::getLeafVertices() {
    vector<int> ans;

    if (isDirectedOrUndirected()) {
        vector<int> degree = degrees();

        for (int i = 0; i < degree.size(); i++) {
            if (degree[i] == 1) {
                ans.push_back(i);
            }
        }
    } else {
        vector<int> inDegree = inDegrees();
        vector<int> outDegree = outDegrees();

        for (int i = 0; i < inDegree.size(); i++) {
            if (inDegree[i] + outDegree[i] == 1) {
                ans.push_back(i);
            }
        }
    }

    return ans;
} 

bool Graph::isCompleteGraph() {
    if (isDirectedOrUndirected()) {
        vector<int> degree = degrees();

        for (int i = 0; i < degree.size(); i++) {
            if (degree[i] != degree.size() - 1) {
                return false;
            }
        }

        return true;
    } else {
        vector<int> inDegree = inDegrees();
        vector<int> outDegree = outDegrees();

        for (int i = 0; i < inDegree.size(); i++) {
            if (inDegree[i] + outDegree[i] != inDegree.size() - 1) {
                return false;
            }
        }

        return true;
    }
}

bool Graph::isCircularGraph() {
    if (isDirectedOrUndirected()) {
        //with an undirected graph, the graph is circular if it has no leaf or isolated vertice.
        vector<int> degree = degrees();

        for (int i = 0; i < degree.size(); i++) {
            if (degree[i] <= 1) {
                return false;
            }
        }
        
        return true;
    } else {
        //with an undirected graph, the graph is circular if every vertex has an in degree of 1 and an out degree of 1.
        vector<int> inDegree = inDegrees();
        vector<int> outDegree = outDegrees();

        for (int i = 0; i < inDegree.size(); i++) {
            if (inDegree[i] == 0 && outDegree[i] == 0) {
                return false;
            }
        }

        return true;
    }
}

//https://www.sanfoundry.com/cpp-program-check-bipartite-graph/
bool Graph::isBipartite() {
    vector<int> color(getVerticesNumber(), -1);

    queue<int> q;

    q.push(0);
    color[0] = 1;

    while (q.empty() == false) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjacencyMatrix[u].size(); i++) {
            if (adjacencyMatrix[u][i] == 1) {
                if (color[i] == -1) {
                    color[i] = 1 - color[u];
                    q.push(i);
                } else if (color[i] == color[u]) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Graph::isCompleteBiPartite() {
    vector<int> color(getVerticesNumber(), -1);

    queue<int> q;

    q.push(0);
    color[0] = 1;

    while (q.empty() == false) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < adjacencyMatrix[u].size(); i++) {
            if (adjacencyMatrix[u][i] == 1) {
                if (color[i] == -1) {
                    color[i] = 1 - color[u];
                    q.push(i);
                } else if (color[i] == color[u]) {
                    return false;
                }
            }
        }
    }

    int firstColor = 0, secondColor = 0;
    for (int i = 0; i < getVerticesNumber(); i++) {
        if (color[i] == 1) {
            firstColor++;
        } else {
            secondColor++;
        }
    }

    vector<int> degree = degrees();

    for (int i = 0; i < getVerticesNumber(); i++) {
        if (color[i] == -1) {
            return false;
        }

        if (color[i] == 1) {
            if (degree[i] != secondColor) {
                return false;
            }
        } else {
            if (degree[i] != firstColor) {
                return false;
            }
        }
    }

    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                if (color[i] == color[j]) {
                    return false;
                }
            }
        }
    }

    return true;
}

void Graph::dfs(int vertex, vector<bool>& visited, vector<int> verticesList) {
    visited[vertex] = true;
    verticesList.push_back(vertex);

    for (int i = 0; i < adjacencyMatrix[vertex].size(); i++) {
        if (adjacencyMatrix[vertex][i] == 1 && visited[i] == false) {
            dfs(i, visited, verticesList);
        }
    }
}

pair<int, int> Graph::getConnectedComponentsNumberAndHowManyTrees() {
    vector<bool> visited;
    for (int i = 0; i < getVerticesNumber(); i++) {
        visited.push_back(false);
    }

    int count = 0;
    int treeCount = 0;

    for (int i = 0; i < getVerticesNumber(); i++) {
        if (visited[i] == false) {
            vector<int> verticesList;
            dfs(i, visited, verticesList);
            count++;

            int totalDegree;
            if (isDirectedOrUndirected()) {
                vector<int> degree = degrees();
                
                totalDegree = 0;

                for (int j = 0; j < verticesList.size(); j++) {
                    totalDegree += degree[verticesList[j]];
                }

                if (verticesList.size() == totalDegree / 2 - 1) {
                    treeCount++;
                }
            } else {
                vector<int> inDegree = inDegrees();
                vector<int> outDegree = outDegrees();

                totalDegree = 0;

                for (int j = 0; j < verticesList.size(); j++) {
                    totalDegree += inDegree[verticesList[j]] + outDegree[verticesList[j]];
                }

                if (verticesList.size() == totalDegree / 2 - 1) {
                    treeCount++;
                }
            }
        }
    }

    return make_pair(count, treeCount);
}

