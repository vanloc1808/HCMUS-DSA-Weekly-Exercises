#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

vector<int> LZW_Encode(string const& message) {
  vector<int> result;
  unordered_map<string, int> uMap;

  // Firstly initialize with ascii bytes (caution with \0)
  for (unsigned char i = 1;; i++) {
    uMap[string(1, i)] = static_cast<int>(i);
    if (i == 255) break;
  }

  // LZW kick in
  string w = "";
  int counter = 256;
  for (char k : message) {
    string wk = w + k;
    if (uMap[wk] != 0) {
      w = wk;
    } else {
      uMap[wk] = counter;
      result.push_back(uMap[w]);
      w = k;
      counter++;
    }
  }
  // Remember the last "char"
  result.push_back(uMap[w]);

  return result;
}

string LZW_Decode(vector<int> const& cipher) {
  string result;
  unordered_map<int, string> uMap;

  // Firstly initialize with ascii bytes (caution with \0)
  for (unsigned char i = 1;; i++) {
    uMap[i] = string(1, i);
    if (i == 255) break;
  }

  auto it = cipher.begin();
  int counter = 256;

  // Print first char and move on
  int w = *it;
  result += static_cast<char>(w);
  it++;

  while (it != cipher.end()) {
    int k = *it;
    string entry = uMap[k];
    result += entry;
    uMap[counter++] = uMap[w] + entry[0];
    w = k;
    it++;
  }

  return result;
}

string intToBin(int input, int bitCount) {
  string result;
  for (int i = 0; i < bitCount; i++) {
    result += (input % 2 == 0) ? '0' : '1';
    input /= 2;
  }
  reverse(begin(result), end(result));
  return result;
}

int getMaxBit(vector<int> const& data) {
  return log2(*max_element(begin(data), end(data))) + 1;
}

void printBin(vector<int> const& cipher, int maxBit) {
  for (int x : cipher) {
    cout << intToBin(x, maxBit) << " ";
  }
  cout << "\n";
}

void printCoef(int before, int after) {
  cout << fixed << setprecision(2)
       << (static_cast<double>(before) - after) * 100 / before;
}

int main(int argc, char** argv) {
  if (strncmp(argv[1], "-c", 2) == 0) { // Compress
      string message = argv[2];
      vector<int> cipher = LZW_Encode(message);
      int maxBit = getMaxBit(cipher);

      for (int x: cipher) cout << x << " ";
      cout << "\n";

      printBin(cipher, maxBit);
      printCoef(message.size() * 8, cipher.size() * maxBit);
      cout << "\n";
  } else if (strncmp(argv[1], "-e", 2) == 0) {
      vector<int> cipher;
      for (int i = 2; i < argc; i++) {
          cipher.push_back(atoi(argv[i]));
      }

      string message = LZW_Decode(cipher);
      int maxBit = getMaxBit(cipher);

      cout << message << "\n";
      printCoef(message.size() * 8, cipher.size() * maxBit);
      cout << "\n";
  }
  return 0;
}
