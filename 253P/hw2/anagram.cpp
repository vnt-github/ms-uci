#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * generates the character frequency map
 * @param str is the string whose character frequency map is to be returned
 * @return an character frequency map
 * */
map<char, int> getCharMap(string str) {
    map<char, int> char_map;
    for (auto &&each : str)
        char_map[each] += 1;
    return char_map;
}

/**
 * returns a list of indices of characters in haystack that mark the beginning of an anagram for needle.
 * @param needle is the string to be searched
 * @param haystack is the string on which search has to be done
 * @return list of indicies of occurence of anagram of needle in haystack
**/
vector<int> anagram(string needle, string haystack) {\
    if (needle.size() > haystack.size()) return vector<int> { -1 };
    vector<int> ans;
    map<char, int> needle_map = getCharMap(needle), haystack_map;
    int i = 0;
    while (i < haystack.length())
    {
        haystack_map[haystack[i++]] += 1;
        if (i < needle.size())
            continue;
        if (equal(haystack_map.begin(), haystack_map.end(), needle_map.begin())) ans.push_back(i-needle.length());
        if (haystack_map[haystack[i-needle.length()]]) haystack_map[haystack[i-needle.length()]] -= 1;
        if (haystack_map[haystack[i-needle.length()]] <= 0) haystack_map.erase(haystack[i-needle.length()]);
    }
    return ans.size() > 0 ? ans: vector<int>{ -1 };
}

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        cerr << "usage: ./executable needle_string haystack_string" << endl;
        return -1;
    }
    cout << "input:" << endl;
    cout << "\tneedle <-- " << argv[1] << endl;
    cout << "\thaystack <-- " << argv[2] << endl;
    cout << "output:" << endl;
    cout << "\t";
    for(auto &&each: anagram(argv[1], argv[2]))
        cout << each << " ,";
    cout << endl;
    return 0;
}

