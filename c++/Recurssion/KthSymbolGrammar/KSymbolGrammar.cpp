#include<cmath>

#include<iostream>

int kthGrammar(int n, int k) {

    for (int i = 0; i < n; ++i) {

    }
    if (n == 1 && k == 1)
        return 0;

    auto size = pow(2, n - 1);
    if (k <= size / 2)
        return kthGrammar(n - 1, k);
    return kthGrammar(n - 1, k - size / 2);


}

int main() {
    int n = 2;
    int k = 1;
    std::cout << kthGrammar(n, k) << std::endl;
    return 0;
}