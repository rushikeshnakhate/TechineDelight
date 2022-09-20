#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

int countKAverageSubarrays(vector<int> &arr, int k) {
    int result = 0, curSum = 0;
    int n= arr.size();

    // Store the frequency of prefix
    // sum of the array arr[]
    unordered_map<int, int> mp;

    for (int i = 0; i < n; i++) {
        // Subtract k from each element,
        // then add it to curSum
        curSum += (arr[i] - k);

        // If curSum is 0 that means
        // sum[0...i] is 0 so increment
        // res
        if (curSum == 0)
            result++;

        // Check if curSum has occurred
        // before and if it has occurred
        // before, add it's frequency to
        // res
        if (mp.find(curSum) != mp.end())
            result += mp[curSum];

        // Increment the frequency
        // of curSum
        mp[curSum]++;
    }

    // Return result
    return result;
}


int solution(vector<int> &A, int S) {
    // write your code in C++14 (g++ 6.2.0)
    unsigned int end = 0;
    int sum = 0;
    int found = 0;
    double mean = 0;

    for (unsigned int start = 0; start < A.size(); ++start) {
        while (mean < S && end < A.size()) {
            sum += A[end];
            mean = sum / (end - start + 1);
            end++;
        }

        if (mean == S) {
            found += 1;
            mean = 0;
            sum = sum - A[start];
        }
        end++;
    }
    return found;
}

int main() {
    std::vector<int> A{2, 1, 3};
    std::cout << countKAverageSubarrays(A, 2) << std::endl;
    return 0;
}