#include <iostream>
#include <vector>
#include <map>

using namespace std;


/**
 * returns the partial table used for KMP algo
 * returns the list whose value at index i gives the length of longest prefix which is also the suffix
 * @param pattern whose partial table to be returned
 * @return partial table
 * */
vector<int> getPartial(string pattern) {
    vector<int> ret = { 0 };
    for (int i = 1, j; i < pattern.size(); i++)
    {
        j = ret[i-1];
        while (j > 0 and pattern[j] != pattern[i]) j = ret[j-1];
        ret.push_back(pattern[j] == pattern[i] ? j+1: j);
    }
    return ret;
}

/**
 * returns the index of the starting character of the first occurrence of needle in the haystack, or -1 if the needle does not exist in the haystack
 * NOTE: uses KMP algorithm
 * @param needle is the string to be searched
 * @param haystack is the string on which search has to be done
 * @return index of starting char of first occurence of needle in haystack if existss else -1
 * */
int strstrx(string needle, string haystack) {
    vector<int> partial = getPartial(needle);
    for (int i = 0, j=0; i < haystack.size(); i++)
    {
        while (j > 0 and needle[j] != haystack[i]) j = partial[j-1];
        if (haystack[i] == needle[j]) j += 1;
        if (j == needle.size()) return (i-(j-1));
    }
    return -1;
}

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
vector<int> anagram(string& needle, string& haystack) {
    vector<int> ans;
    map<char, int> needle_map = getCharMap(needle), haystack_map;
    int i = 0;
    while (i < haystack.length())
    {
        haystack_map[haystack[i++]] += 1;
        if (haystack_map.size() < needle.size()) continue;
        if (equal(haystack_map.begin(), haystack_map.end(), needle_map.begin())) ans.push_back(i-needle.length());
        if (haystack_map[haystack[i-needle.length()]]) haystack_map[haystack[i-needle.length()]] -= 1;
        if (haystack_map[haystack[i-needle.length()]] <= 0) haystack_map.erase(haystack[i-needle.length()]);
    }
    return ans.size() > 0 ? ans: vector<int>{ -1 };
}


/**
 *  returns the number of occurrences of needle in the haystack
 * @param needle is the string to be searched
 * @param haystack is the string on which search has to be done
 * @return an integer representing the number of occurrences of needle in haystack
 * */
int numOccurrences(string& needle, string& haystack) {
    int occurrences = 0;
    for (int i = 0; i < haystack.length()-needle.length()+1; i++)
        if (haystack.substr(i, needle.length()) == needle)
            occurrences++;
    return occurrences;
}

/**
 *  returns the index of the starting character of the first occurrence of needle in the haystack, or -1 if the needle does not exist in the haystack
 * @param needle is the string to be searched
 * @param haystack is the string on which search has to be done
 * @return index of starting char of first occurence of needle in haystack if existss else -1
 * */
int strstr(string& needle, string& haystack) {
    for (int i = 0; i < haystack.length()-needle.length()+1; i++)
        if (haystack.substr(i, needle.length()) == needle)
            return i;
    return -1;
}

int main(int argc, char const *argv[])
{
    string ha1 = "alchemy", na1 = "chem"; cout << strstr(na1, ha1) << endl;  
    string ha2 = "heartache", na2 = "chem"; cout << strstr(na2, ha2) << endl;
    cout << "-----" << endl;
    string hb1 = "bananas", nb1 = "na"; cout << numOccurrences(nb1, hb1) << endl;
    string hb2 = "potato", nb2 = "na"; cout << numOccurrences(nb2, hb2) << endl;
    cout << "-----" << endl;
    string hc1 = "captain", nc1 = "tap";
    for (auto &&each : anagram(nc1, hc1))
        cout << each << endl;
    cout << "-----" << endl;
    string hc2 = "talapia", nc2 = "tap";
    for (auto &&each : anagram(nc2, hc2))
        cout << each << endl;
    cout << "-----" << endl;
    string hd1 = "alchemy", nd1 = "chem"; cout << strstrx(nd1, hd1) << endl;  
    string hd2 = "heartache", nd2 = "chem"; cout << strstrx(nd2, hd2) << endl;

    return 0;
}
