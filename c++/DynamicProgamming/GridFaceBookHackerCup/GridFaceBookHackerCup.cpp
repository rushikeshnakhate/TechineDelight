#include <vector>
#include <iostream>
#include<map>
#include <string>

using namespace std;
using Grid = std::vector<std::vector<char>>;
using Lookup = map<string, std::pair<int, int>>;

bool draw(Grid &grid, int row, int col, Lookup &lookup) {
    if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size()) {
        std::cout << "1go ahead   row=" << row << " col=" << col << std::endl;
        return false;
    }
    std::cout << "go ahead   row=" << row << " col=" << col << std::endl;

    std::string key = std::to_string(row) + "|" + std::to_string(col);
    if (lookup.find(key) == lookup.end()) {
        int count = 0;
        int newRow = row;
        int newCol = col;

        if (draw(grid, row - 1, col, lookup)) {
            newRow = row - 1;
            count++;
        }
        if (draw(grid, row + 1, col, lookup)) {
            newRow = row + 1;
            count++;
        }
        if (draw(grid, row, col - 1, lookup)) {
            newCol = col - 1;
            count++;
        }

        if (draw(grid, row, col + 1, lookup)) {
            newCol = col + 1;
            count++;
        }
        if (grid[row][col] == '^' && count <= 1)
            lookup[key] = std::make_pair(newRow, newCol);
        else
            lookup[key] = std::make_pair(-1, -1);
    }

    auto value = lookup[key];
    if (value.first != -1 && value.second != -1) {
        grid[value.first][value.second] = '^';
    } else
        return false;

    return true;
}

int main() {


    Grid grid{
            {'^'},
            {'.'}
    };




//    Grid grid{
//            {'.', '.', '^', '.'},
//            {'.', '.', '^', '.'},
//            {'.', '.', '.', '.'},
//            {'.', '.', '.', '^'}
//    };
//


    int row = 0;
    int col = 0;
    Lookup lookup;
    draw(grid, row, col, lookup);

    for (auto x : grid) {
        for (auto y :x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}