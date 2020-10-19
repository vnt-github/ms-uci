// no main

// - [ ] edge cases
#include <iostream>
#include <string>

using namespace std;

/**
 * starts matching the two string from the begging and returns the largest match from the start
 * @param s1 is the first string
 * @param s2 is the second string
 * @return the biggest common string from start
 * */
string matchFromStart(string  s1, string s2) {
    int len_1 = s1.length();
    int len_2 = s2.length();
    int i;
    for(i = 0; i <= min(len_1, len_2); i++) {
        if (s1[i] != s2[i])
            break;
    }
    return s1.substr(0, i);
}
/**
 * determines if strings can be made by concatenating string sub only
 * @param s is the larger string
 * @param sub is the smaller or equal string
 * @return boolean determining the if it's possible
 * */
bool isStringDiv(string s, string sub) {
    int len_s = s.size();
    int len_sub = sub.size();

    if (!len_sub || len_s%len_sub)
        return false;

    int sub_i = 0;
    for (int i = 0; i < len_s; i++)
    {
        if (sub_i == len_sub)
            sub_i = 0;
        if (sub[sub_i] == s[i])
            sub_i += 1;
        else
            return false;
    }
    return true;
}

/**
 * returns the largest devising string of the two string
 * @param s1 is the first string
 * @param s2 is the second string
 * @return the largest common devising string
 * */
string getLongestDivString(string s1, string s2) {
    string longest_match = matchFromStart(s1, s2);
    int i;
    for (i = longest_match.size(); i > 0; i--)
    {
        string sub = longest_match.substr(0, i);
        if (isStringDiv(s1, sub) && isStringDiv(s2, sub))
            return sub;
    }

    if (i <= 0)
        return "";
}


int main(int argc, char const *argv[])
{
    string s1, s2, ans;
    s2 = "ababab";
    s1 = "abab";
    cout << getLongestDivString(s1, s2) << endl;
    
    
    s1 = "batman";
    s2 = "batman";
    cout << getLongestDivString(s1, s2) << endl;


    s1 = "abcabcabcabc";
    s2 = "abcabc";
    
    cout << getLongestDivString(s1, s2) << endl;
    

    s1 = "manbat";
    s2 = "man";
    
    cout << getLongestDivString(s1, s2) << endl;
    


    s1 = "xab";
    s2 = "yabc";
    
    cout << getLongestDivString(s1, s2) << endl;
    
    s2 = "aaaaa";
    s1 = "a";
    
    cout << getLongestDivString(s1, s2) << endl;
    
    s2 = "aaaaaa";
    s1 = "aaa";
    
    cout << getLongestDivString(s1, s2) << endl;
    

    return 0;
}
