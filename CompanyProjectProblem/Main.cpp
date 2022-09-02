#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>


std::map<int, int> &BuildDependencyToMap(std::vector<int> &A, std::vector<int> &B, std::map<int, int> &dependency);

std::vector<int> &BuildDependecyToVector(std::vector<int> &A, std::vector<int> &B, std::vector<int> &dd);

template<typename T1, typename T2>
T1 &operator<<(T1 &t1, T2 &t2) {
    for (auto x: t2) {
        t1 << x << " ";
    }
    t1 << std::endl;
    return t1;
}


int main() {
    int v ;
    std::string ss;

    use strci
    my v;
    $v=1 ;
    $v="adasdsad"



    std::vector<int> V{-3, 5, 7, 2, 3};
    std::vector<int> A{3, 1}, B{2, 4};

    std::map<int, int> dependency;
    std::vector<int> dd(V.size(), 0);

//    std::copy(A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::copy(B.begin(), B.end(), std::ostream_iterator<int>(std::cout, " "));


    dependency = BuildDependencyToMap(A, B, dependency);
    dd = BuildDependecyToVector(A, B, dd);

    std::vector<int> xx;
    std::transform(V.begin(), V.end(), dd.begin(), std::back_inserter(xx), [&](int source, int destination) {
        if (destination > -1)
            xx.push_back(source);
        return false;
    });
    std::cout << xx << std::endl;

    //Convert Array to use iterator
//    int arr[] = {1, 2, 3};
//    auto start = arr;
//    auto end = arr + sizeof(arr) / sizeof(arr[0]);
//    std::for_each(start, end, [](int x) {
//        std::cout << x << std::endl;
//    });


}

std::vector<int> &BuildDependecyToVector(std::vector<int> &A, std::vector<int> &B, std::vector<int> &dd) {
    std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(dd), [&](int leader, int voter) {
        dd[leader] = dd[leader] + 1;
        dd[voter] = dd[voter] - 1;
        return false;
    });
    return dd;
}

std::map<int, int> &BuildDependencyToMap(std::vector<int> &A, std::vector<int> &B, std::map<int, int> &dependency) {
    std::transform(A.begin(), A.end(), B.begin(), std::inserter(dependency, dependency.end()),
                   [&](int increment, int reduce) {
                       dependency[reduce] -= 1;
                       dependency[increment] += 1;
                       return std::pair<int, int>(reduce, increment);
                   });
    return dependency;
}
