#include<vector>
#include <iostream>

using namespace std;

int getMinSteps(int maxCol, int maxRow, int k, vector<vector<int>> &grid, int row, int col, int totalSteps) {
    if (row >= maxRow || col >= maxCol || k < 0) {
        return 0;
    }

    if (row == maxRow - 1 && col == maxCol - 1) {
        std::cout << "totalSteps=" << totalSteps << std::endl;
        return 1;
    }

    if (grid[row][col] == 1) {
        k--;
    }

    auto horizontanSteps = getMinSteps(maxCol, maxRow, k, grid, row + 1, col, totalSteps + 1);
    auto verticalSteps = getMinSteps(maxCol, maxRow, k, grid, row, col + 1, totalSteps + 1);

    return horizontanSteps + verticalSteps;
}


int shortestPath(vector<vector<int>> &grid, int k) {
    auto maxCol = grid[0].size();
    auto maxRow = grid.size();
    if (grid[0][0] == 1) return -1;
    int totalSteps = 0;
    return getMinSteps(maxCol, maxRow, k, grid, 0, 0, totalSteps);
}

#include <algorithm>
using Matrix = std::vector<vector<char>>;

void BuildMatrix(vector<string> &B, vector<std::vector<char>> &m);

int main() {
    std::vector<string> B{"..#", "###"};
    Matrix m;

    BuildMatrix(B, m);

//    std::cout << shortestPath(grid, 1) << std::endl;
    return 0;
}

void BuildMatrix(vector<string> &B, Matrix &m) {
    for (auto x : B) {
        vector<char> row;
        for_each(x.begin(), x.end(), [&](char symbol) {
            row.push_back(symbol);
        });
        m.push_back(row);
    }
}
