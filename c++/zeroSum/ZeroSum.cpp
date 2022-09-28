#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

void hasZeroSumSubarray(vector<int> const &nums) {
    int sum = 0;
    std::map<int, int> sumwithEndIndex;
    sumwithEndIndex.insert(std::pair<int, int>(sum, -1));

    for (int i = 0; i < nums.size(); ++i) {
        sum += nums[i];
        if (sumwithEndIndex.find(sum) != sumwithEndIndex.end()) {

        }
        sumwithEndIndex.insert(std::pair<int, int>(sum, i));

    }
    for (auto x : sumwithEndIndex) {
        std::cout << x.first << " " << x.second << std::endl;
    }

}


void zeroSum(std::vector<int> &nums) {

    int sumSoFar = 0;
    int start = 0;
    int end = 0;
    set<vector<int>> subarrays;

    while (end < nums.size()) {
        sumSoFar += nums[end];
        if (sumSoFar == 0) {
            std::vector<int> r;
            for (int i = start; i < end - start + 1; ++i) {
                r.push_back(nums[i]);
            }
            subarrays.insert(r);
        }
        end++;
    };

    while (start <= end) {
        sumSoFar -= nums[start];
        if (sumSoFar == 0) {
            std::vector<int> r;
            for (int i = start; i < end - start + 1; ++i) {
                r.push_back(nums[i]);
            }
            subarrays.insert(r);
        }
        start++;
    }

    for (auto x : subarrays) {
        for (auto x1 : x) {
            std::cout << x1 << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> v{3, 4, -7, 9, -9};
    zeroSum(v);
    return 0;
}