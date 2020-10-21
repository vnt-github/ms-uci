#include <iostream>

using namespace std;

/**
 *  returns the number of occurrences of needle in the haystack
 * @param needle is the string to be searched
 * @param haystack is the string on which search has to be done
 * @return an integer representing the number of occurrences of needle in haystack
 * */
int numOccurrences(string needle, string haystack) {
    if (needle.size() > haystack.size()) return 0;
    int occurrences = 0;
    for (int i = 0; i < haystack.length()-needle.length()+1; i++)
        if (haystack.substr(i, needle.length()) == needle) {
            i += needle.length()-1;
            occurrences++;
        }
    return occurrences;
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
    cout << "\t" << numOccurrences(argv[1], argv[2]) << endl;
    return 0;
}
