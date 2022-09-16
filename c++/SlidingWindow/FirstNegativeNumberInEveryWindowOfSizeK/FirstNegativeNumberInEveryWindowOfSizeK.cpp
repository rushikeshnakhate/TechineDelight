#include<vector>
#include<iostream>
#include <queue>


void findFirstNegative(std::vector<int> &arr) {
    int start = 0, end = 0;
    int k = 3;

    std::queue<int> q;
    int negativeNumber = 0;
    while (end - start + 1 <= k) {
        if (arr[end] < 0) {
            q.push(end);
        }
        end++;
    }
    end--;


    while (end < arr.size()) {
        end++;
        if (arr[end] < 0) {
            q.push(end);
        }
        if (!q.empty()) {
            std::cout << arr[q.front()] << " ";
        } else {
            std::cout << 0 << " ";
        }
        if (arr[start] < 0)
            q.pop();
        start++;
    }

}

int main() {
    std::vector<int> arr{112, -1, -7, 8, -15, 30, 16, 28};
    findFirstNegative(arr);
    return 0;
}