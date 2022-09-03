#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

int minIncrementForUnique(std::vector<int> &v) {
    std::map<int, int> counter;
    std::set<int> visited;

    std::for_each(v.begin(), v.end(), [&](const int &x) {
        counter[x] += 1;
        visited.insert(x);
    });

    int ret = 0;
    for (auto x: counter) {
        int value = x.first;
        int frequency = x.second;
        if (frequency <= 1)
            continue;

        int newValue = value + 1;
        while (frequency > 1) {
            if (visited.find(newValue) == visited.end()) {
                ret += newValue - value;
                visited.insert(newValue);
                frequency--;
            }
            newValue++;
        }
    }
    return ret;
}

int main() {
    std::vector<int> v1 = {3, 2, 1, 2, 1, 2, 6, 7 };
    std::cout << minIncrementForUnique(v1) << std::endl;
    return 0;

}

