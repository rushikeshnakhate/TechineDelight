#include<vector>
#include <queue>

using coordinates = std::pair<int, int>;
using coordinatesWithObstacle = std::pair<coordinates, int>;

int gridProblemUsingBfs(std::vector<std::vector<int>> &grid, int k) {


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


