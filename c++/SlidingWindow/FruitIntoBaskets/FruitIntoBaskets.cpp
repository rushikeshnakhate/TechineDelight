#include <vector>
#include <iostream>
#include <map>

int totalFruit(std::vector<int> &fruits) {
    int start = 0;
    int end = 0;
    int maxCount = 0;
    std::map<int, int> fruitsMap;
    while (end < fruits.size()) {
        auto fruit = fruits[end];

        fruitsMap[fruit]++;

        while (fruitsMap.size() > 2) {
            auto fruitToRemove = fruits[start];
            fruitsMap[fruitToRemove]--;
            if (fruitsMap[fruitToRemove] == 0) {
                fruitsMap.erase(fruitToRemove);
            }
            start++;
        }
        maxCount = std::max(maxCount, end - start + 1);
        end++;
    }
    return maxCount;
}

int main() {

    std::vector<int> f{1, 2, 1};
    //std::vector<int> f{0, 1, 2, 2};

    std::cout << totalFruit(f) << std::endl;
    return 0;
}