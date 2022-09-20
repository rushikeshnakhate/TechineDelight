#include <iostream>
#include <memory>
#include <map>
#include <algorithm>
#include <vector>

class KnapSack {
public:
    virtual int GetMaxProfitFromKnapSack(int value[], int weight[], int w, int n) = 0;
};

class KnapSackUsingRecursion : public KnapSack {
public:
    int GetMaxProfitFromKnapSack(int value[], int weight[], int w, int n) override {
        if (w == 0 || n < 0)
            return 0;

        if (weight[n] <= w) {
            int include = value[n] + this->GetMaxProfitFromKnapSack(value, weight, w - weight[n], n - 1);
            int exclude = this->GetMaxProfitFromKnapSack(value, weight, w, n - 1);
            return std::max(include, exclude);
        } else {
            return this->GetMaxProfitFromKnapSack(value, weight, w, n - 1);
        }
    }
};

class KnapSackUsingMemorizationUsingMatrix : public KnapSack {
    std::vector<std::vector<int>> lookUp ;
public:
    int GetMaxProfitFromKnapSack(int value[], int weight[], int W, int n) override {
        if (W <= 0 || n < 0)
            return 0;
        std::string key = std::to_string(W) + "|" + std::to_string(n);
        if (lookup.find(key) == lookup.end()) {
            if (weight[n] <= W) {
                int include = value[n] + this->GetMaxProfitFromKnapSack(value, weight, W - weight[n], n - 1);
                int exclude = this->GetMaxProfitFromKnapSack(value, weight, W, n - 1);
                lookup[key] = std::max(include, exclude);
            } else {
                lookup[key] = this->GetMaxProfitFromKnapSack(value, weight, W, n - 1);
            }
        }
        return lookup[key];
    }
};

class KnapSackUsingMemorizationUsingMap : public KnapSack {
    std::map<std::string, int> lookup;
public:
    int GetMaxProfitFromKnapSack(int value[], int weight[], int W, int n) override {
        if (W <= 0 || n < 0)
            return 0;
        std::string key = std::to_string(W) + "|" + std::to_string(n);
        if (lookup.find(key) == lookup.end()) {
            if (weight[n] <= W) {
                int include = value[n] + this->GetMaxProfitFromKnapSack(value, weight, W - weight[n], n - 1);
                int exclude = this->GetMaxProfitFromKnapSack(value, weight, W, n - 1);
                lookup[key] = std::max(include, exclude);
            } else {
                lookup[key] = this->GetMaxProfitFromKnapSack(value, weight, W, n - 1);
            }
        }
        return lookup[key];
    }
};

auto x = [](auto row) {
    std::for_each(row.begin(), row.end(), [](int &x) {
        std::cout << x << " ";
    });
    std::cout << std::endl;
};


class KnapSackByTopDown : public KnapSack {
public:
    int GetMaxProfitFromKnapSack(int value[], int weight[], int W, int n) override {
        int matrix[n + 1][W + 1];
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= W; j++) {
                if (i == 0 || j == 0)
                    matrix[i][j] = 0;
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= W; ++j) {
                if (weight[i - 1] <= j) {
                    int include = value[i - 1] + matrix[i - 1][j - weight[i - 1]];
                    int exclude = matrix[i - 1][j];
                    matrix[i][j] = std::max(include, exclude);
                } else {
                    matrix[i][j] = matrix[i - 1][j];
                }
            }
        }
        return matrix[n][W];
    }
};

int main() {
    int value[] = {20, 5, 10, 40, 15, 25};
    int weight[] = {1, 2, 3, 8, 7, 4};
    int W = 10;
    int n = sizeof(value) / sizeof(value[0]);

    std::unique_ptr<KnapSack> pKnapSack = std::make_unique<KnapSackUsingMemorizationUsingMap>();
//    std::unique_ptr<KnapSack> pKnapSack = std::make_unique<KnapSackByTopDown>();
    std::cout << pKnapSack->GetMaxProfitFromKnapSack(value, weight, W, n - 1) << std::endl;

    return 0;
}