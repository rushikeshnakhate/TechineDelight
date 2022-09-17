#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>

std::vector<std::string> visited;

int GridProblemWithObstacle(std::vector<std::vector<int>> &grid,
                            std::vector<int> route,
                            int gRow, int gCol, int k, int row, int col) {


    if (row >= gRow || row < 0 || col >= gCol || col < 0) {
        return 0;
    }
    std::cout << grid[row][col] << " row=" << row << " col=" << col << " " << gRow << " " << gCol << std::endl;

    if (grid[row][col] == 100) {
        k--;
    }
    if (k < 0) {
        return 0;
    }
    std::string key = std::to_string(row) + "|" + std::to_string(col);
    if (std::find(visited.begin(), visited.end(), key) != visited.end()) {
        return 0;
    }

    route.emplace_back(grid[row][col]);
    if (row == gRow - 1 && col == gCol - 1) {
        std::cout << " we rached" << std::endl;
        for (auto x : route) {
            std::cout << x << "  ";
        }
        std::cout << std::endl;
        return 1;
    }
    visited.push_back(key);

    auto down = GridProblemWithObstacle(grid, route, gRow, gCol, k, row + 1, col);
    auto right = (GridProblemWithObstacle(grid, route, gRow, gCol, k, row, col + 1));
    auto up = GridProblemWithObstacle(grid, route, gRow, gCol, k, row - 1, col);
    auto left = (GridProblemWithObstacle(grid, route, gRow, gCol, k, row, col - 1));
    return 1 + std::max(std::max(left, right), std::max(up, down));


    return 0;
};

int main() {
//    std::vector<std::vector<int>> grid{
//            {1,   2, 3},
//            {100, 5, 6},
//            {7,   8, 9}
//    };

    std::vector<std::vector<int>> grid{
            {1,   2,   3},
            {100, 100, 6},
            {7,   8,   9},
            {10,  100, 100},
            {13,  14,  15}
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