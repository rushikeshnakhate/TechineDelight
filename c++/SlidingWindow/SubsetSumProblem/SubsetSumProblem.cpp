#include <iostream>
#include <vector>
#include <memory>

class SubsetSum {
public:
    virtual bool SubsetSumExists(std::vector<int> arr, int size, int k) = 0;
};

class SubsetSumByRecursion : public SubsetSum {
public:
    bool SubsetSumExists(std::vector<int> arr, int size, int k) {
        if (k == 0)
            return true;

        if (size < 0 || k < 0)
            return false;

        if (k <= arr[size]) {
            bool include = this->SubsetSumExists(arr, size - 1, k - arr[size]);
            bool exclude = this->SubsetSumExists(arr, size - 1, k);
            return include || exclude;
        } else {
            return this->SubsetSumExists(arr, size - 1, k);
        }
    }
};

int main() {
    std::vector<int> arr = {7, 3};
    int k = 10;
    std::unique_ptr<SubsetSum> pSubset = std::make_unique<SubsetSumByRecursion>();
    std::cout << pSubset->SubsetSumExists(arr, arr.size() - 1, k) << std::endl;
    return 0;
}