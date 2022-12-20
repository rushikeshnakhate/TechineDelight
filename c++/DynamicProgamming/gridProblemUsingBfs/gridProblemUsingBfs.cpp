#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <functional>

struct CoOrdinate {
    signed int row;
    signed int col;

    CoOrdinate(signed int row, signed int col) : row(row), col(col) {}
};

struct CoOrdinateWithObstacles {
    CoOrdinate coOrdinate;
    int obstacle;

    CoOrdinateWithObstacles(const CoOrdinate coOrdinate, int obstacle) :
            coOrdinate(coOrdinate), obstacle(obstacle) {};

    static bool findByCordinates(const CoOrdinateWithObstacles &coOrdinateWithObstacles,
                                 const CoOrdinate &_coOrdinate) {
        return (coOrdinateWithObstacles.coOrdinate.col == _coOrdinate.col &&
                coOrdinateWithObstacles.coOrdinate.row == _coOrdinate.row);
    }
};


bool IsValidDirection(unsigned int gRow, unsigned int gCol, int row, int col) {
    return row < gRow || col < gCol || row >= 0 || col >= 0;
}

bool IsDestination(unsigned int gRow, unsigned int gCol, int row, int col) {
    return row == gRow - 1 && col == gCol - 1;
}

std::vector<CoOrdinate> directions{
        CoOrdinate{-1, 0},
        CoOrdinate{1, 0},
        CoOrdinate{0, 1},
        CoOrdinate{0, -1}
};


std::vector<CoOrdinateWithObstacles> visited;

bool IsVisited(CoOrdinate coOrdinate) {
    auto itr = std::find_if(visited.begin(), visited.end(),
                            bind(CoOrdinateWithObstacles::findByCordinates,
                                 std::placeholders::_1, coOrdinate));

    return itr == visited.end();
};


int gridProblemUsingBfs(std::vector<std::vector<int>> &grid,
                        int k) {
    auto gRow = grid.size();
    auto gCol = grid[0].size();
    auto steps = 0;
    std::queue<CoOrdinateWithObstacles> myQueue;
    CoOrdinate coOrdinate{0, 0};
    myQueue.push(CoOrdinateWithObstacles(coOrdinate, k));

    while (!myQueue.empty()) {
        auto row = myQueue.front().coOrdinate.row;
        auto col = myQueue.front().coOrdinate.col;
        auto _coOrdinate = myQueue.front().coOrdinate;
        auto obstacle = myQueue.front().obstacle;
        myQueue.pop();

        if (IsDestination(gRow, gCol, row, col))
            return steps;

        for (auto direction : directions) {
            auto newRow = row + direction.row;
            auto newCol = col + direction.col;

            if (IsValidDirection(gRow, gCol, row, col)) {
                if (grid[newRow][newCol] == 1 && obstacle > 0 && IsVisited(_coOrdinate)) {
                    visited.push_back(CoOrdinateWithObstacles{_coOrdinate, obstacle - 1});
                    myQueue.push(CoOrdinateWithObstacles{_coOrdinate, obstacle - 1});
                } else {
                    visited.push_back(CoOrdinateWithObstacles{_coOrdinate, obstacle});
                    myQueue.push(CoOrdinateWithObstacles{_coOrdinate, obstacle});
                }
            }
            steps++;
        }
    }
    return steps;
}


int main() {
    std::vector<std::vector<int>> grid{
            {1,   2,   3},
            {100, 100, 6},
            {7,   8,   9},
            {10,  100, 100},
            {13,  14,  15}
    };
    int k = 1;

    gridProblemUsingBfs(grid, k);

    return 0;
}