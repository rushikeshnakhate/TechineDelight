#include <string>
#include <iostream>
#include <algorithm>


using namespace std;


const char wildCard = '?';
//const char Filter.aFilter = 'a';
//const char Filter::bFilter = 'b';

enum Filter {
    aFilter = 'a',
    bFilter = 'b'
};

bool CheckIfCombinationValid(Filter c, std::string const &s, unsigned int index) {
    //corner case
    return ((index < 2 || s[index - 2] != c || s[index - 1] != c)
            && (index < 1 || index + 1 >= s.length() || s[index - 1] != c || s[index + 1] != c)
            && (index + 2 >= s.length() || s[index + 1] != c || s[index + 2] != c));
}

void TryForBothFilters(string &out, unsigned int &index, int &direction) {
    direction = 1;
    if (CheckIfCombinationValid(Filter::aFilter, out, index)) {
        out[index] = Filter::aFilter;
        index += direction;
    } else if (CheckIfCombinationValid(Filter::bFilter, out, index)) {
        out[index] = Filter::bFilter;
        index += direction;
    } else {
        direction = -1;
        index += direction;
    }
}

string solution(string &in) {
    std::string out = "";
    unsigned int index = 0;
    int direction = 1;
    out = in;

    while (index < in.size()) {
        if (in[index] != wildCard) {
            index += direction;
        } else if (out[index] == wildCard) {
            TryForBothFilters(out, index, direction);
        } else if (out[index] == Filter::aFilter && CheckIfCombinationValid(Filter::bFilter, out, index)) {
            out[index] = Filter::bFilter;
            direction = 1;
            index += direction;
        } else {
            direction = -1;
            out[index] = wildCard;
            index += direction;
        }
    }
    return out;
}


int main() {

    std::string in = "a?bb";
    std::cout << solution(in) << std::endl;

    return 0;
}