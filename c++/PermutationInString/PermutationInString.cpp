#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


bool checkInclusion(string s1, string s2) {
    if ( s2.length() < s1.length())
        return false;
    std::transform(s1.begin(), s1.end(), s1.begin(), [](char c) {
        return toupper(c);
    });

    std::transform(s2.begin(), s2.end(), s2.begin(), [](char c) {
        return toupper(c);
    });

    std::vector<int> s1Hash(26, 0);
    std::vector<int> s2Hash(26, 0);

    int left = 0;
    int right = 0;

    while (right < s1.size()) {
        int s1Index = s1[right] - 'A';
        int s2Index = s2[right] - 'A';

        s1Hash[s1Index] += 1;
        s2Hash[s2Index] += 1;
        right++;
    }

    right--;

    while (right < s2.size()) {
        if (s1Hash == s2Hash)
            return true;

        int s2LeftIndex = s2[left] - 'A';
        s2Hash[s2LeftIndex] -= 1;

        right++;
        if (right < s2.size()) {
            int s2rightIndex = s2[right] - 'A';
            s2Hash[s2rightIndex] += 1;
        }
        left++;
    }
    return false;
}

int main() {

    std::cout << checkInclusion("ab", "eidbaooo") << std::endl;
    return 0;
}