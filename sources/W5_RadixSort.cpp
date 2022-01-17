#include <fstream>
#include <iostream>

struct Node {
  int data;
  Node* pNext;
};

struct Bucket {
  int key;
  Node* pHead;
  Node* pTail;
  Bucket* pNext;
};

Bucket* lowerBoundBucketFind(Bucket* buckHead, int key) {
  Bucket* p = buckHead;
  Bucket* q = p->pNext;  // Next pointer;
  while (q != nullptr && q->key < key) {
    p = p->pNext;
    q = q->pNext;
  }
  return p;  // this node will be < key
}

Bucket* insertBucket(Bucket* buckHead, int key) {  // insert after
  Bucket* p = lowerBoundBucketFind(buckHead, key);
  if (p->pNext != nullptr && p->pNext->key == key) {  // Already
    return p->pNext;
  }

  Bucket* newBucket = new Bucket{key, nullptr, nullptr, p->pNext};
  p->pNext = newBucket;
  return newBucket;
}

void addTail(Node*& pHead, Node*& pTail, Node* p) {
  if (pHead == nullptr) {
    pHead = pTail = p;
  } else {
    pTail->pNext = p;
    pTail = p;
  }
  pTail->pNext = nullptr;  // normalize ptail
}

void radixSort(Bucket* buckHead, Node** array, int n, int base) {
  int shiftRight = 1;  // value to shift right with division

  // find max element;
  int maxElem = array[0]->data;
  for (int i = 1; i < n; i++) {
    if (maxElem < array[i]->data) {
      maxElem = array[i]->data;
    }
  }

  while (shiftRight <= maxElem) {
    // Build bucket
    for (int i = 0; i < n; i++) {
      int key = (array[i]->data / shiftRight) % base;
      Bucket* p = insertBucket(buckHead, key);
      addTail(p->pHead, p->pTail, array[i]);
    }

    // Traverse and clean
    Bucket* buck = buckHead->pNext;
    Bucket* temp;
    int i = 0;
    while (buck != nullptr) {
      for (Node* p = buck->pHead; p != nullptr; p = p->pNext) {
        array[i] = p;
        i++;
      }
      temp = buck;
      buck = buck->pNext;
      delete temp;
    }
    // Normalized buckHead
    buckHead->pNext = nullptr;

    // Process to next "digit"
    shiftRight *= base;
  }
}

int main() {
  std::ifstream ifs("input.txt");
  int n, k;
  ifs >> k >> n;

  Node** array = new Node*[n];
  for (int i = 0; i < n; i++) {
    int x;
    ifs >> x;
    array[i] = new Node{x, nullptr};
  }
  ifs.close();
  Bucket* buckHead = new Bucket{-1, nullptr, nullptr, nullptr};  // Dummy node

  int base = 1;
  while (k-- > 0) base *= 10;
  radixSort(buckHead, array, n, base);

  for (int i = 0; i < n; i++) {
    std::cout << array[i]->data << " ";
    std::cout.flush();
    delete array[i];
  }

  delete[] array;
  delete buckHead;

  return 0;
}

