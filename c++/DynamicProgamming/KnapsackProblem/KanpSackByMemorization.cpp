using namespace std;

#include <iostream>
#include<vector>

int knapSack(int val[], int wt[], int w, int n, std::vector<std::vector<int>> &Lookup) {
    if (w == 0 || n == 0)
        return 0;

    if (Lookup[n][w] != -1)
        return Lookup[n][w];

    if (wt[n - 1] <= w) {
        auto include = val[n - 1] + knapSack(val, wt, w - wt[n - 1], n - 1, Lookup);
        auto exclude = knapSack(val, wt, w, n - 1, Lookup);

        Lookup[n][w] = std::max(include, exclude);
    } else {
        Lookup[n][w] = knapSack(val, wt, w, n - 1, Lookup);
    }
    return Lookup[n][w];
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int w = 50;

    int n = sizeof(val) / sizeof(val[0]);
    std::vector<std::vector<int>> lookUp(n + 1, std::vector<int>(w + 1, -1));

    cout << knapSack(val, wt, w, n, lookUp);

    return 0;
}