#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using std::string;

struct Object {
  string id;
  unsigned order;
  unsigned priority;
  bool operator>(Object const& other) { return priority > other.priority; }
};

using vobj = std::vector<Object>;

class PQMinHeap {
 private:
  vobj m_arr;

  void siftDown(int start, int n) {
    int root = start;
    int child = 0;

    while ((child = root * 2 + 1) < n) {
      int swap = root;
      if (m_arr[swap] > m_arr[child]) {
        swap = child;
      }
      if (child + 1 <= n && m_arr[swap] > m_arr[child + 1]) {
        swap = child + 1;
      }

      if (swap == root) return;
      std::swap(m_arr[swap], m_arr[root]);
      root = swap;
    }
  }

  // Sift from position n to correct place
  void siftUp(int n) {
    int child = n;
    while (child > 0) {
      int parent = (child - 1) / 2;
      if (m_arr[parent] > m_arr[child]) {
        std::swap(m_arr[parent], m_arr[child]);
        child = parent;
      } else {
        return;
      }
    }
  }

  void heapdify() {
    int n = m_arr.size();
    int start = (n - 1 - 1) / 2;

    while (start >= 0) {
      siftDown(start, n - 1);
      start--;
    }
  }

 public:
  PQMinHeap() {}
  bool isEmpty() { return m_arr.empty(); }
  void Insert(Object const& o) {
    m_arr.push_back(o);
    int n = m_arr.size();
    m_arr.back().order = n - 1;
    siftUp(n - 1);
  }
  Object Extract(unsigned prio) {}
  void Remove(string const& id) {}
  void changePriority(string const& id, unsigned newOrd) {}
  void print() {
    for (auto i : m_arr) {
      std::cout << i.id << " " << i.priority << " " << i.order << "\n";
    }
  }
};

int main() {
  PQMinHeap pq;
  pq.Insert(Object{"abc", 1, 2});
  pq.Insert(Object{"bbc", 1, 3});
  pq.Insert(Object{"cbc", 1, 5});
  pq.Insert(Object{"dbc", 1, 1});
  pq.print();
  return 0;
}
