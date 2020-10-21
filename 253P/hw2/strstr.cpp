#include <iostream>

using namespace std;

/**
 *  returns the index of the starting character of the first occurrence of needle in the haystack, or -1 if the needle does not exist in the haystack
 * @param needle is the string to be searched
 * @param haystack is the string on which search has to be done
 * @return index of starting char of first occurence of needle in haystack if existss else -1
 * */
int strstr(string needle, string haystack) {
    if (needle.size() > haystack.size())
        return -1;
    for (int i = 0; i < haystack.length()-needle.length()+1; i++)
        if (haystack.substr(i, needle.length()) == needle)
            return i;
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
    cout << "\t" << strstr(argv[1], argv[2]) << endl;
    return 0;
}
