#include <iostream>
#include <vector>

using namespace std;

int steps = 0;

int interpolationSearch(vector<int> a, int n, int x) {
    int l = 0, r = n - 1;

    while(l <= r) {
        steps++;

        int pivot = (1.0 * (x - a[l]) * (r - l)) / (a[r] - a[l]) + l;

        if (a[pivot] == x) {
            return pivot;
        }

        if (a[pivot] > x) {
            r = pivot - 1;
        } else {
            l = pivot + 1;
        }
    }
    return -1;
}

int main(int argc, char** argv) {
    int x = atoi(argv[1]);

    vector<int> a;
    for (int i = 2; i < argc; i++) {
        a.push_back(atoi(argv[i]));
    }

    cout << steps << " " << interpolationSearch(a, a.size(), x) << "\n";

    return 0;
}