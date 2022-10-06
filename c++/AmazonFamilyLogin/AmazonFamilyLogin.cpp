
#include <iostream>
#include<unordered_map>

using namespace std;

// function to return maximum number of distinct Toys
int MaxNumber(int arr[], int N, int K) {
    // Count Number of distinct Number
    unordered_map<int, int> mp;
    for (int i = 0; i < N; i++) {
        mp[arr[i]]++;
    }
    // push them into vector
    vector<int> v1;
    for (auto i : mp) {
        v1.push_back(i.second);
    }
    // add number of element except one element from every
    // distinct element
    int temp = 0;
    for (int i = 0; i < v1.size(); i++) {
        temp += v1[i] - 1;
    }
    // check if it is greater than simply return size of
    // vector otherwise decrement size of vector to fill k
    if (K <= temp) {
        return v1.size();
    } else {
        K = K - temp;
        int ans = v1.size();
        while (K) {
            ans--;
            K--;
        }
        return ans;
    }
}

// Driver Code
int main() {
    // array
    int arr[] = {2 , 3 , 1 , 1 ,2 };
    int K = 2;
    // size of array
    int N = sizeof(arr) / sizeof(arr[0]);
    cout << MaxNumber(arr, N, K) << endl;
    return 0;
}