#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

//brute Force
int maxProfit(vector<int> &prices) {
    int i = 4;
    while (i--) {
        std::cout << "xx" << " ";
    }
    std::cout << "\n=====" << i << std::endl;
    i = 4;
    while (--i) {
        std::cout << "yy" << " ";
    }
    std::cout << "\n=====" << i << std::endl;

    return 0;
}

template<int N>
struct S {
    enum {
        value = S<N / 2>::value + (N % 2)
    };
};
template<>
struct S<0> {
    enum {
        value = 0
    };
};


int main() {
//    std::set<int> s{1, 3, 5, 7, 8, 9};
//    for (auto x: s) {
//        std::cout << x << " ";
//    }
//
//    std::cout << std::endl;
//    s.erase(5);
//    s.insert(9);
//    s.insert(10);
//    for (auto x: s) {
//        std::cout << x << " ";
//    }
//    std::cout << S<6>::value << std::endl;
//    int s = 10;
//    std::string s1 = "sadasd";
//    if (s == s1)
//
//
//        return;


    int x = 9;
    if (x >> 1 == 0)
        std::cout << "idd" << std::endl;
    std::vector<int>A {1,10,3};
    int n = A.size();
    for ( int i=0 ; i < n-1 ; i++ ) {
        if ( A[i] > A[i+1]) {
            int tmp = A[i];
            A[i] = A[i+1];
            A[i+1] = tmp ;
        }
    }
    for ( auto x : A) {
        std::cout << x <<" " ;
    }
}
