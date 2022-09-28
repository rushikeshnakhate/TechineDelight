#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//brute Force
int maxProfit(vector<int> &prices) {
    int profit = 0;
    for (int i = 0; i < prices.size(); ++i) {
        for (int j = i + 1; j < prices.size(); ++j) {
            if (prices[j] > prices[i]) {
                profit = max(profit, prices[j] - prices[i]);
            }
        }
    }
    return profit;
}





int main() {
    std::vector<int> v{2, 7, 9, 5, 1, 3, 5};
    std::cout << maxProfit1(v) << std::endl;
    return 0;

}