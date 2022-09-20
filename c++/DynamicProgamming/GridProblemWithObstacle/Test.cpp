#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> restoreMatrix(vector<int> &rowSum, vector<int> &colSum) {
    int r = rowSum.size();
    int c = colSum.size();
    vector<vector<int>> ans(r, vector<int>(c, 0));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int m = min(rowSum[i], colSum[j]);
            ans[i][j] += m;
            rowSum[i] -= m;
            colSum[j] -= m;
        }
    }
    return ans;
}

string solution1(int U, int L, vector<int> &C) {
    // write your code in C++14 (g++ 6.2.0)
    vector<int> rowSum{U, L};
}


vector<vector<int>> solution(int U, int L, vector<int> &C) {
    vector<vector<int>> ans(2, vector<int>(C.size(), 0));
    for (int i = 0; i < C.size(); i++) {
        if (C[i] == 1) {
            if (U > L) {
                ans[0][i] = 1;
                U--;
            } else {
                ans[1][i] = 1;
                L--;
            }

        }

        if (C[i] == 2) {
            ans[0][i] = 1;
            ans[1][i] = 1;
            U--;
            L--;
        }

        if (U < 0 or L < 0)
            return {};
    }

    //0th row sum and 1st row sum should be completely made by forming the matrix
    if (U != 0 or L != 0)
        return {};

    return ans;
}

int main() {
    std::vector<int> C{2, 0, 2, 0};

    std::string s;
    auto x = solution(2, 2, C);
    for (auto a : x) {
        for (auto b :a) {
            std::cout << b << " ";
            s += std::to_string(b);
        }
        s += ",";
        std::cout << std::endl;
    }
    std::cout << s << std::endl;
}