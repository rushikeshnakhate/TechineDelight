#include <vector>
#include <iostream>

bool isVaild(std::vector<std::vector<char>> grid, int row, int col) {
    return true;
}

void draw(std::vector<std::vector<char>> grid, int row, int col) {
    if (row < 0 || col > 0)
        return;

    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col)
            if (grid[row][col] == '^') {

            }
    }

}

void check(std::vector<std::vector<char>> grid, int row, int col) {
    if (row <= 1 || col <= 1) {
        std::cout << "Impossible" << std::endl;
    }
    draw(grid, row, col);
}

int main() {

    std::vector<std::vector<char>> grid{
            {'.', '.'},
            {'.', '^'},
            {'.', '.'},
    };

    int row = 3;
    int col = 1;


    check(grid, row, col);
    return 0;
}