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
    if (needle.size() > haystack.size()) return -1;
    vector<int> partial = getPartial(needle);
    for (int i = 0, j=0; i < haystack.size(); i++)
    {
        while (j > 0 and needle[j] != haystack[i]) j = partial[j-1];
        if (haystack[i] == needle[j]) j += 1;
        if (j == needle.size()) return (i-(j-1));
    }
    return -1;
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
    cout << "\t" << strstrx(argv[1], argv[2]) << endl;
    return 0;
}
