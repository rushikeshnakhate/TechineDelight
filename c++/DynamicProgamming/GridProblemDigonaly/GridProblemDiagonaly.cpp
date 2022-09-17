#include <vector>
#include <iostream>


template<typename T1, typename T2>
T1 &operator<<(T1 &t1, T2 &t2) {
    for (auto &x: t2)
        t1 << x << " ";
    t1 << std::endl;
    return t1;
}

void AllWays(std::vector<std::vector<int>> &mat, int row, int col, std::vector<int> route) {
    if (row >= mat.size() | col >= mat[0].size()) {
        return;
    }

    if (mat[row][col] == 9) {
        route.push_back(mat[row][col]);
        std::cout << route;
    }

    route.push_back(mat[row][col]);

    AllWays(mat, row + 1, col, route);
    AllWays(mat, row, col + 1, route);
    AllWays(mat, row + 1, col + 1, route);

    return;
}

int main() {
    std::vector<std::vector<int>> mat =
            {
                    {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}
            };

    std::vector<int> route;
    AllWays(mat, 0, 0, route);
    return 0;
}