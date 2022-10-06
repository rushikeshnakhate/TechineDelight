#include <utility>
#include <vector>
#include <iostream>
#include <tuple>
#include <assert.h>

const int factor = 2;

std::pair<int, int> get(int previous, int current) {
    if (previous > factor - 1) {
        current = current + previous / factor;
        previous = previous % factor;
    }
    return std::make_pair(previous, current);
}

int Solution(std::vector<int> v) {
    int countToken = 0;
    auto first = v[0];
    for (int i = 1; i < v.size(); ++i) {
        std::tie(v[i - 1], v[i]) = get(first, v[i]);
        first = v[i];
        if (v[i] > 0) countToken++;
    }

    //last item
    auto current = 0;
    std::tie(v[v.size() - 1], current) = get(v[v.size() - 1], 0);
    v.push_back(current);
    if (current > 0) countToken++;

    return countToken;
}

//Time Complexity O(n) and space Complexity O(1)
int main() {
    assert(Solution({2, 3}) == 2);
    assert(Solution({1, 0, 4, 1}) == 3);
    return 0;
}

