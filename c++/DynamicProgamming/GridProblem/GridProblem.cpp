#include <map>
#include <iostream>

int GetU(int maxRow, int maxCol, int row, int col, std::map<std::string, int> &LookUp) {
    if (row > maxRow || col > maxCol)
        return 0;

    if (row == maxRow-1 || col == maxCol-1)
        return 1;

    std::string key = std::to_string(row) + "|" + std::to_string(col);
    if (LookUp.find(key) == LookUp.end()) {
        LookUp[key] = GetU(maxRow, maxCol, row + 1, col, LookUp) +
                      GetU(maxRow, maxCol, row, col + 1, LookUp);
    }
    return LookUp[key];
}

int GetUniquePath(int m, int n) {
    std::map<std::string, int> LookUp;
    return GetU(m, n, 0, 0, LookUp);
}

int main() {
    int m = 3; //row
    int n = 7; //columns
    std::cout<<GetUniquePath(m, n) <<std::endl;

    return 0;
}