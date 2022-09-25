#include<iostream>
#include <vector>

int main() {
    std::vector<int> s{1, 2, 3, 4};
    std::vector<int> s1{11, 22, 33, 44};
    std::copy(s.begin(), s.end(), std::back_insert_iterator<std::vector<int>>(s1));
    for (auto x: s1) {
        std::cout << x << " ";
    }
    return 0;
}