#include<string>
#include<iostream>
#include <algorithm>
#include <map>
#include <memory>
#include <string>

template<typename T1, typename T2>
T1 &operator<<(T1 &t1, T2 &t2) {
    for (auto x : t2) {
        t1 << x << " ";
    }
    return t1;
}

class LCS {
public:
    virtual int getLCS(std::string str1, std::string str2) = 0;
};

class LCSByRecursion : public LCS {
public:
    int getLCS(std::string str1, std::string str2) override {
        if (str1.empty() || str2.empty())
            return 0;

        if (str1.front() == str2.front())
            return 1 + getLCS(str1.substr(1), str2.substr(1));

        return std::max(getLCS(str1, str2.substr(1)), getLCS(str1.substr(1), str2));
    }
};

#include <vector>
#include <mutex>

class LCSByMemorizatrion : public LCS {
    static std::map<std::string, int> makrs1;
public:
    int getLCS(std::string str1, std::string str2) override {
        if (str1.empty() || str2.empty())
            return 0;

        std::string key = std::to_string(str1.size()) + std::to_string(str2.size());
        if (makrs1.find(key) == makrs1.end()) {
            if (str1.front() == str2.front()) {
                makrs1[key] = 1 + this->getLCS(str1.substr(1), str2.substr(1));
            } else
                makrs1[key] = std::max(this->getLCS(str1.substr(1), str2),
                                       this->getLCS(str1, str2.substr(1)));
        }
        return makrs1[key];
    }
};

std::map<std::string, int> LCSByMemorizatrion::makrs1;


class LCSByTopDown : public LCS {
    static int t[100][100];
public:
    int getLCS(std::string str1, std::string str2) override {
        return 0;
    }
};

int LCSByTopDown::t[100][100];


class LCSubstringByRecursion : public LCS {
public:
    int getLCS(std::string str1, std::string str2) override {
        if (str1.empty() || str2.empty())
            return 0;

        if (str1.front() == str2.front())
            return 1 + getLCS(str1.substr(1), str2.substr(1));

        return 0;
    }
};

int main() {
    std::string s1 = "abc";
    std::string s2 = "ab";
    std::unique_ptr<LCS> p = std::make_unique<LCSByTopDown>();
    std::cout << p->getLCS(s1, s2) << std::endl;
    return 0;
}