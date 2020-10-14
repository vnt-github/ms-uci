#include <iostream>
#include <vector>

using namespace std;

vector<int> getPartial(string pattern) {
    int j;
    vector<int> ret = { 0 };
    for (int i = 1; i < pattern.size(); i++)
    {
        j = ret[i-1];
        while (j > 0 and pattern[j] != pattern[i]) {
            j = ret[j-1];
        }
        if (pattern[j] == pattern[i]) {
            ret.push_back(j+1);
        } else {
            ret.push_back(j);
        }
    }
    return ret;
}

vector<int> matches(string key, string haystack) {
    vector<int> partial = getPartial(key);
    int j = 0;
    vector<int> ret;

    for (int i = 0; i < haystack.size(); i++)
    {
        while (j > 0 and key[j] != haystack[i]) {
            j = partial[j-1];
        }
        if (haystack[i] == key[j]) {
            j += 1;
        }
        if (j == key.size()) {
            ret.push_back(i-(j-1));
            j = partial[j-1];
        }
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    vector<int> ans;
    ans = matches("man", "BatmanSupermanAquamanWonderWoman");
    for (auto &&each : ans)
    {
        cout << each << " ";
    }
    cout << endl;
    
}

// 1. casesenetivee 
// 2. needle and haystack wont be null
// 3. aaaa , aa => 0, 1, 2
// 4. complexity of each function to keep it small