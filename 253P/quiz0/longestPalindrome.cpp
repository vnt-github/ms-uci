#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * returns the reverse of the input string
 * @param s is the string to be reversed
 * @return reversed string
 * */
string rev_string(string& s) {
    string ans;
    for (auto &&each : s)
        ans = each + ans;
    return ans;
}

/**
 * checks if a string is palindrome
 * @param s is the string to be checked for palindrome
 * @return bool representing if s is palindrome or not
 * */
bool isPalindrome(string& s) {
    return rev_string(s) == s;
}

/**
 * Returns a hash map with the corresponding word in the strings vector as key and two value pair
 * representing whether the keyword is a palindrome and if it has opposite pair in the strings vector
 * and if has pair is true the other pair is not inserted into the hash map
 * for ex: input {"abc", "cba", "xyz", "bcb"}
 * returns { "abc": (false, true), "xyz": (false, false), "bcb": (true, false) }
 * @param strings is the list of input strings
 * @return a hash map with key as a word in a string and pair value representing ('is palindrome', 'has opposite pair in the list')
 * */
unordered_map<string, pair<bool, bool>> getIsPalindromeAndHasPair(vector<string> strings) {
    unordered_map<string, pair<bool, bool>> isPalindromeAndHasPair;
    string rev_each;
    for (int i = 0; i < strings.size(); i++)
    {
        rev_each = rev_string(strings[i]);
        if (isPalindromeAndHasPair.find(rev_each)\
            != isPalindromeAndHasPair.end()\
            && !isPalindromeAndHasPair[rev_each].second)
            isPalindromeAndHasPair[rev_each].second = true;
        else
            isPalindromeAndHasPair[strings[i]] = make_pair(isPalindrome(strings[i]), false);
    }
    return isPalindromeAndHasPair;
}

/**
 * main function which returns the largest palindrome possible by concatenating words in the list of strings
 * where each word is distinct, lowercase and is of same fixed length
 * @param strings is the list of input strings
 * @return largest palindrome string made by concatenation
 * */
string longestPalindrome(vector<string> strings) {
    bool isPalindrome, hasOppositePair;
    string middle_palindrome = "", ans;
    for (auto &&each : getIsPalindromeAndHasPair(strings))
    {
        isPalindrome = each.second.first;
        hasOppositePair = each.second.second;
        if (hasOppositePair)
            ans += each.first;
        else if (!hasOppositePair\
                && isPalindrome \
                && !middle_palindrome.size())
            middle_palindrome = each.first;   
    }
    return ans + middle_palindrome + rev_string(ans);
} 

int main()
{
    vector<string> s1 = {"aba", "aba" }; // invalid case unique strings of same size
    vector<string> s2 = {"bat", "dba", "pop", "abd", "tab"};
    vector<string> s3 = { "abc", "cba", "aaa", "bbb" };
    vector<string> s5 = {"xyz", "zyx", "aaa", "bcd"};

    cout << longestPalindrome({}) << endl;
    cout << longestPalindrome({""}) << endl;
    cout << longestPalindrome({"a", "b", "c"}) << endl;
    cout << longestPalindrome({"axz", "act", "bcb"}) << endl;


    cout << longestPalindrome(s1) << endl;
    cout << longestPalindrome(s2) << endl;
    cout << longestPalindrome(s3) << endl;
    cout << longestPalindrome(s5) << endl;
    return 0;
}
