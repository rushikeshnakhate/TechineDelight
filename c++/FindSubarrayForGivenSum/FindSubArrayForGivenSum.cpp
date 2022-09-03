#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

void findSubarray(int nums[], int sizeOfNums, int target) {
    int start = 0;
    int end = 0;
    int sum = 0;
    int *p = nums;

    for (int start = 0; start < sizeOfNums; ++start) {
        while (sum < target && end < sizeOfNums) {
            sum += nums[end];
            end++;
        }
        if (sum == target) {
            std::cout << "----\n";
            std::copy(nums + start, p + end, std::ostream_iterator<int>(std::cout, " "));
        }
        sum = sum - nums[start];
    }

}

int main() {
    int nums[] = {2, 6, 0, 9, 7, 3, 1, 4, 1, 10};
    int target = 15;
    int sizeOfNums = sizeof(nums) / sizeof(nums[0]);
    findSubarray(nums, sizeOfNums, target);
    return 0;
}