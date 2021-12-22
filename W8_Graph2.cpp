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

//this is a recursive function,
//used to find cut vertices (aka articulation points) using DFS traversal.
//vertex: the next vertex to be visited
//visited: keeps track of visited vertices
//discorveryTimes: stores discovery times of visited vertices
//lowTimes: stores earliest visited vertex (the vertex with minimum discovery time)
//that can be reached from sub-tree rooted with current vertex
//parent: stores the parent vertex in DFS tree
//isCV: stores the cut vertices
//https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
void Graph::cutVerticesUlti(int vertex, vector<bool>& visited, vector<int>& discoveryTimes, vector<int>& lowTimes, int& time, int parent, vector<bool>& isCV) {
    //count the number of children in DFS tree
    int children = 0;

    visited[vertex] = true;

    discoveryTimes[vertex] = lowTimes[vertex] = ++time;

    for (auto v: adjacencyList[vertex]) {
        if (visited[v] == false) {
            children++;

            cutVerticesUlti(v, visited, discoveryTimes, lowTimes, time, vertex, isCV);

            //check if the subtree rooted with v has a connection to one of the ancestors of vertex
            lowTimes[vertex] = min(lowTimes[vertex], lowTimes[v]);

            //check if vertex is not root and low value of one of its child 
            //is more than discovery value of vertex
            if (parent != -1 && lowTimes[v] >= discoveryTimes[vertex]) {
                isCV[vertex] = true;
            }
        } else if (v != parent) {
            //update the low value of vertex by taking the minimum of the current low value and the discovery value of the visited vertex
            lowTimes[vertex] = min(lowTimes[vertex], discoveryTimes[v]);
        }
    }

    //if vertex is root of DFS tree and it has more than one child
    //then it is a cut vertex
    if (parent == -1 && children > 1) {
        isCV[vertex] = true;
    }
}

int Graph::getCutVerticesNumber() {
    int verticeNumber = getVerticesNumber();

    vector<int> discoverTimes(verticeNumber, 0);
    vector<int> lowTimes(verticeNumber, INT_MAX);
    vector<bool> isCutVertex(verticeNumber, false);
    vector<bool> visited(verticeNumber, false);
    int time = 0, parent = -1;

    //add this loop so that the code works even if the graph is not connected
    for (int i = 0; i < verticeNumber; i++) {
        if (visited[i] == false) {
            cutVerticesUlti(i, visited, discoverTimes, lowTimes, time, parent, isCutVertex);
        }
    }

    int cutVerticeNumber = 0;
    for (int i = 0; i < verticeNumber; i++) {
        if (isCutVertex[i] == true) {
            cutVerticeNumber++;
        }
    }

    return cutVerticeNumber;
}

//a recursive function that find bridges using DFS traversal
//vertex: the next vertex to be visited
//visited: keeps track of visited vertices
//discorveryTimes: stores discovery times of visited vertices
//lowTimes: stores earliest visited vertex (the vertex with minimum discovery time)
//that can be reached from sub-tree rooted with current vertex
//parent: stores parent vertices in DFS tree
//https://www.geeksforgeeks.org/bridge-in-a-graph/
void Graph::bridgeUtil(int vertex, vector<bool>& visited, vector<int>& discoveryTimes, vector<int>& lowTimes, vector<int>& parent, vector<Edge>& bridges) {
    //a static variable is used for simplicity, 
    //we can avoid use of static variable by passing a pointer
    static int time = 0;

    visited[vertex] = true;

    discoveryTimes[vertex] = lowTimes[vertex] = ++time;

    //go through all the vertices adjacent to this vertex
    vector<int>::iterator i;

    for (i = adjacencyList[vertex].begin(); i != adjacencyList[vertex].end(); i++) {
        int v = *i; //v is the current neighbor of vertex

        //if v is not visited yet, then use the recursion for it
        if (visited[v] == false) {
            parent[v] = vertex;

            bridgeUtil(v, visited, discoveryTimes, lowTimes, parent, bridges);

            //check if the sub-tree rooted with v has a connection to one of the ancestors of vertex
            lowTimes[vertex] = min(lowTimes[vertex], lowTimes[v]);

            //if the lowest vertex reachable from subtree rooted with v is below v, then vertex-v is a bridge
            if (lowTimes[v] > discoveryTimes[vertex]) {
                //this is a bridge
                //add the edge (vertex, v) to the list of bridges
                bridges.push_back(Edge(vertex, v));
            }
        } else if (v != parent[vertex]) {
            //update the low value of vertex by taking the minimum of the current low value and the discovery value of the visited vertex
            lowTimes[vertex] = min(lowTimes[vertex], discoveryTimes[v]);
        }
    }
}

//dfs based to find bridges, used the bridgeUtil function
int Graph::getBridgesNumber() {
    int verticeNumber = getVerticesNumber();

    vector<bool> visited;
    vector<int> discoveryTimes;
    vector<int> lowTimes;
    vector<int> parent;
    
    for (int i = 0; i < verticeNumber; i++) {
        visited.push_back(false);
        discoveryTimes.push_back(0);
        lowTimes.push_back(0);
        parent.push_back(0);
    }

    vector<Edge> bridges;

    for (int i = 0; i < verticeNumber; i++) {
        if (visited[i] == false) {
            bridgeUtil(i, visited, discoveryTimes, lowTimes, parent, bridges);
        }
    }

    return bridges.size();
}

Graph Graph::baseUndirectedGraph() {
    if (isDirectedOrUndirected()) {
        return *this;
    }

    int n = getVerticesNumber();

    vector<vector<int>> AM;
    AM.resize(n);
    for (int i = 0; i < n; i++) {
        AM[i].resize(n);
    }

    vector<vector<int>> AL;
    AL.resize(n);

    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                AL[i].push_back(j);
                AL[j].push_back(i);

                AM[i][j] = 1;
                AM[j][i] = 1;
            }
        }
    }

    Graph ans;
    ans.adjacencyList = AL;
    ans.adjacencyMatrix = AM;

    return ans;
}

vector<vector<int>> Graph::getComplementGraph() {
    vector<vector<int>> ans;

    if (isDirectedOrUndirected() == false) {
        return ans;
    }

    int n = getVerticesNumber();
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        ans[i].resize(n);
    }

    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                ans[i][j] = 0;
                ans[j][i] = 0;
            } else {
                ans[i][j] = 1;
                ans[j][i] = 1;
            }
        }
    }

    return ans;
}

vector<vector<int>> Graph::getConverseGraph() {
    vector<vector<int>> ans;

    if (isDirectedOrUndirected() == true) {
        return ans;
    }

    int n = getVerticesNumber();

    ans.resize(n);
    for (int i = 0; i < n; i++) {
        ans[i].resize(n);
    }

    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                ans[i][j] = 0;
            } else {
                ans[i][j] = 1;
            }
        }
    }

    return ans;
}