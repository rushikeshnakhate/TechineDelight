//Please wahtch https://www.youtube.com/watch?v=XFh_AoEdOTw

#include <vector>
#include <string>
#include <iostream>

void BuildWindow(const std::string &s2, std::string s1) {

    std::vector<int> s1Hash(26, 0);
    std::vector<int> s2Hash(26, 0);
    std::vector<int> result;

    int left = 0;
    int right = 0;
    while (right < s2.length()) {
        s2Hash[s2[right] - 'A'] += 1;
        s1Hash[s1[right] - 'A'] += 1;
        right++;
    }
    right--;

    while (right < s1.length()) {
        if (s1Hash == s2Hash) {
            result.push_back(left);
        }
        right++;
        if (right < s1.length())
            s1Hash[s1[right] - 'A']++;
        s1Hash[s1[left] - 'A']--;
        left++;
    }

    for (auto x : result) {
        std::cout << x << std::endl;
    }
}

int main() {
    std::string s1 = "ABC";
    std::string s2 = "BC";

    BuildWindow(s2, s1);


    return 0;
}

