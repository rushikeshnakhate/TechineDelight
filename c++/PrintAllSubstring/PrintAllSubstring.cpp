https://www.youtube.com/watch?v=b7AYbpM5YrE&t=522s Please watch video to understand bitwise operation
#include<bits/stdc++.h>

using namespace std;

//There are multiple ways
//From techie Delight
// Function to print all non-empty substrings of the specified string
void printAllSubstrings(string str)
{
    int n = str.length();

    // consider all substrings starting from `i`
    for (int i = 0; i < n; i++)
    {
        // consider all substrings ending at j
        for (int j = i; j < n; j++) {
            cout << "'" << str.substr(i, j - i + 1) << "', ";
        }
    }
}


vector<string> AllPossibleStrings(string s) {
    int n = s.length();
    vector<string> ans;
    //1<<n  this is equivalent of writing pow(2,n)
    for (int num = 0; num < (1 << n); num++) {
        string sub = "";
        for (int i = 0; i < n; i++) {
            //check if the ith bit is set or not
            if (num & (1 << i)) {
                sub += s[i];
            }
        }
        if (sub.length() > 0) {
            ans.push_back(sub);
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {


    string s = "abc";
    vector<string> ans = AllPossibleStrings(s);
    //printint all the subsequence.
    cout << "All possible subsequences are " << endl;
    for (auto it : ans) {
        cout << it << " ";
    }

}
