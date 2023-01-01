#include <vector>
#include <iostream>

std::vector<std::vector<int>> all_subarray(std::vector<int> &v) {
    std::vector<std::vector<int>> res;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = i; j < v.size(); ++j) {
            std::vector<int> row;
            for (int k = i; k < j; ++k) {
                res.emplace_back(row);
            }
        }
    }
    return res;
}

void all_subset() {

}

void all_subsequence() {

}

#include <cassert>

auto main() -> int {
    std::vector<int> v{2, 1, 3, 4};
    std::vector<int> v1{1,
                        2,
                        3,
                        4};
    assert(v == v1);
    std::vector<std::vector<int>> expected = {
            {1},
            {1, 2},
            {1, 2, 3},
            {1, 2, 3, 4},
            {2},
            {2, 3},
            {2, 3, 4},
            {3},
            {3, 4},
            {4}
    };

    return 0;
}