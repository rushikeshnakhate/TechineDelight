#include <vector>
#include <iostream>

template<typename T1, typename T2>
T1 &operator<<(T1 &t1, T2 &t2) {
    for (auto x : t2) {
        t1 << x << " ";
    }
    t1 << std::endl;
}

void shrinkVector(std::vector<int> &v, int k) {
    int start = 0;
    int end = 0;
    int triplet = 3;


    while (end - start + 1 != triplet && end < v.size()) {
        end++;
    }

    std::vector<int> res;
    while (end < v.size()) {
        auto secondElelementOftriplet = v[start + 1];
        if (secondElelementOftriplet == k + v[start] && v[end] == k + secondElelementOftriplet) {
            std::cout << start << " " << end << std::endl;
            v.erase(v.begin() + start, v.begin() + end);
            break;
        }
        start++;
        end++;
    }
    std::cout << v << std::endl;
}


int main() {

    std::vector<int> A = {1, 2, 3, 5, 7, 8};
    int k = 2;
    shrinkVector(A, k);
    return 0;
}