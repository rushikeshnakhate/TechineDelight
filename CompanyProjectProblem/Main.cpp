#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>


template<typename T1, typename T2>
T1 &operator<<(T1 &t1, T2 &t2) {
    for (auto x: t2) {
        t1 << x << " ";
    }
    t1 << std::endl;
    return t1;
}

int main() {
    std::vector<int> V{-3, 5, 7, 2, 3};
    std::vector<int> A{3, 1}, B{2, 4};
    std::cout << V << std::endl;
    std::map<int, int> dependency;

    std::copy(A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " "));
    std::copy(B.begin(), B.end(), std::ostream_iterator<int>(std::cout, " "));

    std::transform(A.begin(), A.end(), B.begin(), std::inserter(dependency, dependency.end()),
                   [&](int increment, int reduce) {
                       dependency[reduce] -= 1;
                       dependency[increment] += 1;
                       return std::pair<int, int>(reduce, increment);
                   });

    std::for_each(dependency.begin(), dependency.end(), [](auto x) {
        std::cout << x.first << " " << x.second << std::endl;
    });

    std::vector<int> dd(V.size(), 0);

    std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(dd), [&](int leader, int voter) {
        dd[leader] = dd[leader] + 1;
        dd[voter] = dd[voter] - 1;
        return false;
    });
    std::cout << dd << " " << dd.size() << std::endl;
    std::transform(dependency.begin(), dependency.end(), std::inserter(dependency, dependency.end()),
                   [](auto x) {
                       return std::pair<int, int>(1, 1);
                   });

    std::vector<int> xx;
    std::transform(V.begin(), V.end(), dd.begin(), std::back_inserter(xx), [&](int source, int destination) {
        if (destination > -1)
            xx.push_back(source);
        std::cout << source << "--->" << destination << std::endl;
        return false;
    });


    std::vector<int> to_vector;
    std::remove_if(xx.begin(), xx.begin(), [](int source) {
        std::cout << source << std::endl;
        return source == 5;
    });
    std::cout << to_vector << std::endl;


    int arr[] = {1, 2, 3};
    auto start = arr;
    auto end = arr + sizeof(arr) / sizeof(arr[0]);
    std::for_each(start, end, [](int x) {
        std::cout << x << std::endl;
    });


}