#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct TrieNode {
  int ID = -1;
  std::array<TrieNode*, 26> next = {};
};

void Insert(TrieNode*& t, std::string const& s, int id) {
  TrieNode* p = t;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i] - 'a';
    if (p->next[c] == nullptr) {
      p->next[c] = new TrieNode;
    }
    p = p->next[c];
  }
  p->ID = id;
}

void createTrie(TrieNode*& t, std::string const& path) {
  std::ifstream ifs(path);

  t = new TrieNode;
  std::string line;
  while (std::getline(ifs, line)) {
    if (line == "") break;  // Blank line
    line.pop_back(); // Remove \r
    int pos = line.find(".");
    Insert(t, line.substr(pos + 2, std::string::npos),
           std::stoi(line.substr(0, pos)));
  }

  ifs.close();
}

int lookUp(TrieNode* t, std::string const& s) {
  if (t == nullptr) return -1;
  TrieNode* p = t;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i] - '0';
    if (p->next[c] == nullptr) {
      return -1;  // Cannot find
    }
    p = p->next[c];
  }
  return p->ID;
}

void DFT(TrieNode* t, std::vector<std::string>& result, std::string& current) {
  if (t == nullptr) return;
  if (t->ID != -1) {
    result.push_back(current);
  }

  for (int i = 0; i < 26; i++) {
    if (t->next[i] == nullptr) continue;
    current += 'a' + i;
    DFT(t->next[i], result, current);
    current.pop_back();
  }
}

std::vector<std::string> lookUpPrefix(TrieNode* t, std::string const& s) {
  TrieNode* p = t;
  std::string prefix;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i] - 'a';
    prefix += s[i];
    if (p == nullptr) return std::vector<std::string>();
    p = p->next[c];
  }
  if (p == nullptr) return std::vector<std::string>();

  std::vector<std::string> result;
  DFT(t, result, prefix);
  return result;
}

void Remove(TrieNode*& t, std::string const& s) {
  TrieNode* p = t;
  for (int i = 0; i < s.length(); i++) {
    char c = s[i] - 'a';
    if (p->next[c] == nullptr) {
      return;  // Not found
    }
    p = p->next[c];
  }
  p->ID = -1;  // Pseudo delete
}

int main() {
  TrieNode* t = nullptr;

  createTrie(t, "HW6-dic.txt");
  std::vector<std::string> result = lookUpPrefix(t, "over");
  for (auto const& s : result) {
    std::cout << s << "\n";
  }

  return 0;
}
