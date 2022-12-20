#include <vector>
#include <iostream>
#include<map>
#include <string>

using namespace std;
using Grid = std::vector<std::vector<char>>;

int Check(Grid &grid, int row, int col) {
    if (row < 0 || col < 0)
        return 0;

    if (row >= grid.size() || col >= grid[0].size())
        return 0;

    if (grid[row][col] == '0')
        return 0;

    grid[row][col] = '0';

    Check(grid, row + 1, col);
    Check(grid, row, col + 1);
    Check(grid, row - 1, col);
    Check(grid, row, col - 1);

}

int NumsOfIsland(Grid &grid) {
    int flg = 0;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col] == '1') {
                Check(grid, row, col);
                flg++;
            }
        }
    }
    return flg;
}

int main() {
    Grid grid{
            {'1', '1', '1', '0'},
            {'1', '0', '1', '0'},
            {'1', '0', '1', '0'},
            {'0', '0', '0', '1'}
    };
    std::cout << NumsOfIsland(grid) << std::endl;
    return 0;
}