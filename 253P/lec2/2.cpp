#include <iostream>
#include <vector>
#include <map>

using namespace std;


int match_anagram(int start_s_i, string s, int w_size, map<char, int> w_map) {
    for(int i=start_s_i; i < start_s_i+w_size; i++) {
        if (w_map.find(s[i]) == w_map.end() || w_map[s[i]] <= 0) {
            return 0;
        } else {
            w_map[s[i]] -= 1;
        }
    }
    return 1;
}

vector<int> find_anagrams(string w, string s) {
   map<char, int> w_map;
    for(int i=0; i< w.size(); i++) {
        w_map[w[i]] += 1;
    }
    vector<int> ans;
    for (int i = 0; i < s.size(); i++)
    {
	if (match_anagram(i, s, w.size(), w_map))
        ans.push_back(i);
    }
	return ans;
}

int main(int argc, char const *argv[])
{
    vector<int> ans = find_anagrams("man", "vanmietanma");
    for (auto &&each : ans)
    {
        cout << each << endl;
    }
    
    return 0;
}

// min 3 test cases per function


// hw2 

// quiz on thurday but 24 hours to complete the quiz