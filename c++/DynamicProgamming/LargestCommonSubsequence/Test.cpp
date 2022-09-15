#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int marker[4][6];

int getLCS(std::string s1, std::string s2) {
    if (s1.empty() || s2.empty())
        return 0;

    int n = s1.length()-1;
    int m = s2.length()-1;

    if (marker[n][m] == -1) {
        for (int i = 1; i <= s1.length(); ++i) {
            for (int j = 1; j <= s2.length(); ++j) {
                if (s1[i-1] == s2[i-1])
                    marker[i][j] = 1 + marker[i - 1][j - 1];
                else
                    marker[i][j] = std::max(marker[i - 1][j], marker[i][j - 1]);
            }
        }
    }
    return marker[n][m];
}

int main() {
    std::string x = "abcf";
    std::string y = "abcdaf";
    int n = x.size();
    int m = y.size();

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 || j == 0)
                marker[i][j] = 0;
            else
                marker[i][j] = -1;
        }
    }

    std::cout << getLCS(x, y) << std::endl;
    return 0;
}