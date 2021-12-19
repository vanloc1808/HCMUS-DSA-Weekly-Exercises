#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

enum class Type { Normal, Complete, Circular, Bigraph, ComBigraph };

class Graph {
 private:
  vector<vector<int>> data;
  bool mode;  // 1 for adjacency list, 0 for matrix

 public:
  void inputListFromFile(char const* filename) {}
  void inputMatrixFromFile(char const* filename) {}

  void changeMode() {
    if (mode) {  // List to Matrix
      mode = !mode;

      int n = getVertices();
      vector<vector<int>> temp(n, vector<int>(n, 0));
      for (int u = 0; u < n; u++) {
        for (auto& v : data[u]) {
          temp[u][v] = 1;
        }
      }
      data = move(temp);
    } else {  // Matrix to List
      mode = !mode;

      int n = getVertices();
      vector<vector<int>> temp(n);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (data[i][j] > 0) {
            temp[i].push_back(j);
          }
        }
      }
      data = move(temp);
    }
  }

  bool checkUndirected() {
    if (mode) {  // list
      // Time complexity: O(V + E)
      int n = data.size();
      for (int i = 0; i < n; i++) {
        for (auto& u : data[i]) {
          if (find(data[u].begin(), data[u].end(), i) ==
              data[u].end())  // u->v but no v->u
            return false;
        }
      }

    } else {  // Matrix
      // Time complexity: O(V^2)
      int n = data.size();
      for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
          if (data[u][v] > 0 && data[v][u] == 0) {  // Same as above
            return false;
          }
        }
      }
    }
    return true;
  }

  int getVertices() { return data.size(); }
  int getEdge() {
    bool isUndirected = checkUndirected();
    if (mode) {  // List
      // Time complexity: O(V)
      int total = 0;
      for (auto& v : data) {
        total += v.size();
      }
      return isUndirected ? (total / 2) : total;
    } else {  // Matrix
      // Time complexity: O(V^2)
      int total = 0;
      int n = data.size();
      for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
          if (data[u][v] > 0) total++;
      return isUndirected ? (total / 2) : total;
    }
  }

  pair<vector<int>, vector<int>> getDegree() {
    vector<int> inDeg(getVertices()), outDeg(getVertices());
    if (mode) {  // List
      // Time complexity: O(V + E)
      for (int i = 0; i < getVertices(); i++) {
        outDeg[i] = data[i].size();
        for (auto& v : data[i]) inDeg[v]++;
      }
    } else {  // Matrix
      // Time complexity: O(V^2)
      for (int i = 0; i < getVertices(); i++) {
        for (int j = 0; j < getVertices(); j++) {
          if (data[i][j] > 0) {  // i -> j
            outDeg[i]++;
            inDeg[j]++;
          }
        }
      }
    }
    return {inDeg, outDeg};
  }

  pair<vector<int>, vector<int>> getIsolatedAndLeaf() {
    auto [in, out] = getDegree();
    vector<int> isolated, leaf;
    // Time complexity: O(V)
    for (int i = 0; i < getVertices(); i++) {
      int totalDeg = in[i] + out[i];
      if (totalDeg == 0)
        isolated.push_back(i);
      else if (totalDeg == 1)
        leaf.push_back(i);
    }
    return {isolated, leaf};
  }

  bool isBipartite() {  // coloring 2
    vector<int> color(getVertices(), -1);
    queue<int> q;
    q.push(0);     // Supposed starting at 0
    color[0] = 1;  // Initialize 0
    if (mode) {    // List
      // Time complexity: O(V + E)
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        // set color of adjacent vertices differ from v
        for (auto& u : data[v]) {
          if (color[u] == -1) {  // Not set
            if (color[v] == 1)
              color[u] = 2;
            else
              color[u] = 1;
            q.push(u);
          } else {  // already set
            if (color[u] == color[v]) {
              return false;
            }
          }
        }
      }
    } else {  // Matrix
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < getVertices(); i++)
          if (data[v][i] > 0) {
            if (color[i] == -1) {
              if (color[v] == 1)
                color[i] = 2;
              else
                color[i] = 1;
              q.push(i);
            } else {
              if (color[v] != color[i]) {
                return false;
              }
            }
          }
      }
    }

    return true;
  }

  bool isCompleteBipartite() {
    // Same as testing partite
    // But save colors vertex
    vector<int> one, two;
    vector<int> color(getVertices(), -1);
    queue<int> q;
    q.push(0);     // Supposed starting at 0
    color[0] = 1;  // Initialize 0
    one.push_back(0);

    bool isUndirected = checkUndirected();
    auto [in, out] = getDegree();

    if (mode) {  // List
      // Time complexity: O(V + E)
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        // set color of adjacent vertices differ from v
        for (auto& u : data[v]) {
          if (color[u] == -1) {  // Not set
            if (color[v] == 1) {
              color[u] = 2;
              two.push_back(u);
            } else {
              color[u] = 1;
              one.push_back(u);
            }
            q.push(u);
          } else {  // already set
            if (color[u] == color[v]) {
              return false;
            }
          }
        }
      }
    } else {  // Matrix
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < getVertices(); i++)
          if (data[v][i] > 0) {
            if (color[i] == -1) {
              if (color[v] == 1) {
                color[i] = 2;
                two.push_back(i);
              } else {
                color[i] = 1;
                one.push_back(i);
              }
              q.push(i);
            } else {
              if (color[v] != color[i]) {
                return false;
              }
            }
          }
      }
    }
    // Phase 2: testing each in one have "path" to two and vice versa
    if (isUndirected) {
      for (auto& u : one) {
        if (in[u] != two.size()) return false;
      }
      for (auto& u : two) {
        if (in[u] != one.size()) return false;
      }
    } else {
      for (auto& u : one) {
        if (in[u] + out[u] != two.size()) return false;
      }
      for (auto& u : two) {
        if (in[u] + out[u] != one.size()) return false;
      }
    }

    return true;
  }

  bool isComplete() {
    auto [in, out] = getDegree();
    int n = getVertices();
    bool isUndirected = checkUndirected();
    // Time complexity: O(V)
    if (isUndirected) {
      for (int i = 0; i < n; i++) {
        if (in[i] != (n - 1)) {  // Each vertex must have n-1 degree
          return false;
        }
      }
    } else {
      for (int i = 0; i < n; i++) {
        if (in[i] + out[i] != (n - 1)) {
          return false;
        }
      }
    }

    return true;
  }

  bool isCircular() {
    int n = getVertices();
    bool isUndirected = checkUndirected();
    // Check if every vertex has total degree of 2
    auto [in, out] = getDegree();
    if (isUndirected) {  // only check in / out deg
      for (int i = 0; i < n; i++) {
        if (in[i] != 2) return false;
      }
    } else {  // Check total deg
      for (int i = 0; i < n; i++) {
        if (in[i] + out[i] != 2) return false;
      }
    }
    // DFS from random point and check if every vertex considered
    vector<bool> visited(n, false);
    stack<int> st;  // Non-recursive DFS
    st.push(0);
    if (mode) {  // List
      while (!st.empty()) {
        int u = st.top();
        st.pop();
        visited[u] = true;
        for (auto& v : data[u]) {
          if (!visited[v]) {
            st.push(v);
          }
        }
      }
    }
    for (int i = 0; i < n; i++)
      if (visited[i] == false) {  // ...
        return false;
      }
    return true;
  }

  Type getType() {
    if (isComplete()) return Type::Complete;
    if (isCircular()) return Type::Circular;
    if (isCompleteBipartite()) return Type::ComBigraph;
    if (isBipartite()) return Type::Bigraph;
    return Type::Normal;
  }


};

int main() { return 0; }
