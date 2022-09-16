#include<vector>
#include<iostream>
#include <algorithm>

int findMax(std::vector<int> &v, int k = 2) {
    int start = 0;
    int end = 0;
    int sum = 0;
    while (end - start + 1 <= k) {
        sum += v[end];
        end++;
    }
    end--;
    while (end <= v.size()) {
        end++;
        int currentsum = sum - v[start] + v[end];
        start++;
        sum = std::max(sum, currentsum);
    }

    return sum;
}

int main() {
    std::vector<int> arr{100, 200, 300, 400};
    std::cout << findMax(arr) << std::endl;
}