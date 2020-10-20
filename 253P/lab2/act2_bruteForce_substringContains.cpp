#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

bool contains(string s1, string s2) {
    bool ans = s2.size() >= s1.size() && (s2.find(s1) != string::npos);
    return ans;
}

vector<vector<string>> getContainsPair(vector<string> strings) {
    vector<vector<string>> ans;
    vector<string> sub;
    for (int i = 0; i < strings.size(); i++)
    {
        sub = {};
        for (int j = 0; j < strings.size(); j++)
        {
            /* code */
            if (i == j) continue;
            if (contains(strings[i], strings[j])) {
                sub.push_back(strings[j]);
            }
        }
        ans.push_back(sub);
    }
    return ans;
}


void printResult(vector<string> strings) {
	vector<vector<string>> contains = getContainsPair(strings);
    for (int i = 0; i < strings.size(); i++)
    {
        cout << strings[i] << ": ";
        for (auto &&each : contains[i])
        {
            cout << each << " ";
        }
        cout << endl;
    }   
}


int main(int argc, char const *argv[])
{
    vector<string> strings = { "carry", "corporate", "roll", "came", "greedy", "ca", "face", "selfish", "corollary", "bad", "carry-on" };
    printResult(strings);
    return 0;
}
