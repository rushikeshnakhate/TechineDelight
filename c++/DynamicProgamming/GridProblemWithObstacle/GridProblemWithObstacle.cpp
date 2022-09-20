#include<vector>
#include <iostream>

using namespace std;

int getMinSteps(int maxCol, int maxRow, int k, vector<vector<int>> &grid, int row, int col, int totalSteps) {
    if (row >= maxRow || col >= maxCol || k < 0 ) {
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


int main() {
    std::vector<std::vector<int>> grid1{
            {0, 0, 0},
            {1, 1, 0},
            {0, 0, 0},
            {0, 1, 1},
            {0, 0, 0}
    };
//    std::vector<std::vector<int>> grid{
//            {0, 0, 0},
//            {0, 0, 0},
//            {0, 0, 0},
//    };

    std::vector<std::vector<int>> grid{
            {0, 1, 1},
            {1, 1, 1},
            {1, 0, 0},
    };
    std::cout << shortestPath(grid, 1) << std::endl;
    return 0;
}