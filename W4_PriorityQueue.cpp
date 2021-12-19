#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using std::string;

struct Object {
  string id;
  unsigned order;
  unsigned priority;
  bool operator>(Object const& other) { return priority > other.priority; }
  bool operator==(Object const& other) { return priority == other.priority; }
  bool operator<(Object const& other) { return priority < other.priority; }
};

using vobj = std::vector<Object>;

// Swap but keep order
void swap(Object& a, Object& b) {
  std::swap(a.id, b.id);
  std::swap(a.priority, b.priority);
}

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
      ::swap(m_arr[swap], m_arr[root]);
      root = swap;
    }
  }

  // Sift from position n to correct place
  void siftUp(int n) {
    int child = n;
    while (child > 0) {
      int parent = (child - 1) / 2;
      if (m_arr[parent] > m_arr[child]) {
        ::swap(m_arr[parent], m_arr[child]);
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

  // int binary_search(unsigned priority) {
  //   int l = 0;
  //   int r = m_arr.size();
  //   while (l <= r) {
  //     int m = l + (r - l) / 2;
  //     if (m_arr[m].priority == priority) return m;
  //     if (m_arr[m].priority > priority) {
  //       r = m - 1;
  //     } else {
  //       l = m + 1;
  //     }
  //   }
  //   return -1;
  // }

 public:
  PQMinHeap() {}
  bool isEmpty() { return m_arr.empty(); }
  void Insert(Object const& o) {
    m_arr.push_back(o);
    int n = m_arr.size();
    m_arr.back().order = n - 1;
    siftUp(n - 1);
  }
  Object Extract() {
    if (isEmpty()) {
      throw std::runtime_error("Can't extract empty heap!");
      return Object{};
    }

    Object data = m_arr[0];
    ::swap(m_arr[0], m_arr.back());
    m_arr.pop_back();
    siftDown(0, m_arr.size() - 1);
    return data;
  }
  void Remove(string const& id) {
    auto it = std::find_if(m_arr.begin(), m_arr.end(),
                           [&id](Object const& elem) { return elem.id == id; });
    if (it == m_arr.end()) return;  // Not found
    if (it == m_arr.begin()) {      // Delete first element
      Extract();
      return;
    }
    ::swap(*it, m_arr.back());
    m_arr.pop_back();

    int current = std::distance(m_arr.begin(), it);
    int parent = (current - 1) / 2;
    if (m_arr[current] > m_arr[parent]) {
      siftUp(current);
    } else {
      siftDown(current, m_arr.size() - 1);
    }
  }
  void changePriority(string const& id, unsigned newPrio) {
    auto it = std::find_if(m_arr.begin(), m_arr.end(),
                           [&id](Object const& elem) { return elem.id == id; });
    if (it == m_arr.end()) return;  // Not found
    if (it == m_arr.begin()) {
      siftDown(0, m_arr.size() - 1);
      return;
    }

    int current = std::distance(m_arr.begin(), it);
    int parent = (current - 1) / 2;
    it->priority = newPrio;
    if (m_arr[current] < m_arr[parent]) {
      siftUp(current);
    } else {
      siftDown(current, m_arr.size() - 1);
    }
  }
  void print() {
    for (auto i : m_arr) {
      std::cout << i.id << " " << i.priority << " " << i.order << "\n";
    }
  }
};

int main() {
  PQMinHeap pq;
  std::cout << "--------------------\n";
  pq.Insert(Object{"abc", 1, 2});
  pq.print();
  std::cout << "\n";
  pq.Insert(Object{"bbc", 1, 3});
  pq.print();
  std::cout << "\n";
  pq.Insert(Object{"cbc", 1, 5});
  pq.print();
  std::cout << "\n";
  pq.Insert(Object{"dbc", 1, 1});
  pq.print();
  std::cout << "\n";
  pq.Insert(Object{"ebc", 1, 9});
  pq.print();
  std::cout << "\n";
  pq.Insert(Object{"fbc", 1, 0});
  pq.print();
  std::cout << "\n";
  std::cout << "--------------------\n";

  std::cout << "Extract: " << pq.Extract().id << "\n";
  pq.print(); std::cout << "\n";

  std::cout << "Remove cbc: \n";
  pq.Remove("cbc");
  pq.print(); std::cout << "\n";

  std::cout << "Change priority ebc to 0\n";
  pq.changePriority("ebc", 0);
  pq.print(); std::cout << "\n";

  return 0;
}
