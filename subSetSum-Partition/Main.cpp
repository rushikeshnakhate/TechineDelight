#include <vector>
#include <iostream>
#include <numeric>
#include <map>

bool canDivide(std::vector<int> &v, int n, int sum, std::map<std::string, bool> &LookUp) {
    if (sum == 0)
        return true;
    if (n < 0)
        return false;
    std::string key = std::to_string(sum) + "|" + std::to_string(n);
    if (LookUp.find(key) == LookUp.end()) {
        LookUp[key] = canDivide(v, n - 1, sum - v[n], LookUp) || canDivide(v, n - 1, sum, LookUp);
    }
    return LookUp[key];
}


int main() {
    std::vector<int> v{3, 1, 1, 2, 2, 1};
    std::map<std::string, bool> LookUp;
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << canDivide(v, v.size() - 1, sum / 2, LookUp) << std::endl;
}