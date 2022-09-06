#include<vector>
#include<iostream>
#include <tuple>


bool findAllSubstr(std::string s, std::string out) {
    if (s.length() < 1) {
        std::cout << out << std::endl;
        return true;
    }
    findAllSubstr(s.substr(1), out + s[0]);
    findAllSubstr(s.substr(1), out);
    return true;

}

int main() {
    std::string str = "abc";
    findAllSubstr(str, "");
}
