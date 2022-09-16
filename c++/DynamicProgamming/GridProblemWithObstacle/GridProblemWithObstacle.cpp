#include <vector>
#include <iostream>
#include <algorithm>

int GridProblemWithObstacle(std::vector<std::vector<int>> &grid,
                            std::vector<int> route,
                            int gRow, int gCol, int k, int row, int col) {


    if (row >= gRow || col >= gCol) {
        return 0;
    }
    std::cout << grid[row][col] << " row=" << row << " col=" << col << " " << gRow << " " << gCol << std::endl;

    if (grid[row][col] == 100) {
        k--;
    }
    if (k < 0) {
        return 0;
    }
    route.emplace_back(grid[row][col]);
    if (row == gRow - 1 && col == gCol - 1) {

        for (auto x : route) {
            std::cout << x << "  ";
        }
        std::cout << std::endl;
        return 1;
    }
    auto r = GridProblemWithObstacle(grid, route, gRow, gCol, k, row + 1, col);
    auto c = (GridProblemWithObstacle(grid, route, gRow, gCol, k, row, col + 1));
    return 1 + std::max(r , c);
};

int main() {
    std::vector<std::vector<int>> grid{
            {1, 2, 3},
            {4, 100, 6}
    };

    auto gRow = grid.size();
    auto gCol = grid[0].size();
    int k = 0;

    int row = 0;
    int col = 0;

    std::vector<int> route;
    std::cout << GridProblemWithObstacle(grid, route, gRow, gCol, k, row, col) << std::endl;
    return 0;
}