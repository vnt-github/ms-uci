// C++ program for the above approach 
#include <bits/stdc++.h> 
using namespace std; 
 
void max_len(string s[], int N, int M) 
{ 
    // Stores the distinct strings 
    // from the given array 
    unordered_set<string> set_str; 
 
    // Insert the strings into set 
    for (int i = 0; i < N; i++) { 
 
        set_str.insert(s[i]); 
    } 
 
    // Stores the left and right 
    // substrings of the given string 
    vector<string> left_ans, right_ans; 
 
    // Stores the middle substring 
    string mid; 
 
    // Traverse the array of strings 
    for (int i = 0; i < N; i++) { 
 
        string t = s[i]; 
 
        // Reverse the current string 
        reverse(t.begin(), t.end()); 
 
        // Checking if the string is 
        // itself a palindrome or not 
        if (t == s[i]) { 
 
            mid = t; 
        } 
 
        // Check if the reverse of the 
        // string is present or not 
        else if (set_str.find(t) 
                != set_str.end()) { 
 
            // Append to the left substring 
            left_ans.push_back(s[i]); 
 
            // Append to the right substring 
            right_ans.push_back(t); 
 
            // Erase both the strings 
            // from the set 
            set_str.erase(s[i]); 
            set_str.erase(t); 
        } 
    } 
 
    // Print the left substring 
    for (auto x : left_ans) { 
 
        cout << x; 
    } 
 
    // Print the middle substring 
    cout << mid; 
 
    reverse(right_ans.begin(), 
            right_ans.end()); 
 
    // Print the right substring 
    for (auto x : right_ans) { 
 
        cout << x; 
    } 
	cout << endl;
} 
 

int main(int argc, char const *argv[])
{
    string s1[2] = {"aba", "aba" };
    string s2[5] = {"abc", "dba", "kop", "cba", "abd"};
    string s3[4] = { "abc", "cba", "aaa", "bbb" };
    max_len(s1, 2, 3);
    max_len(s2, 5, 3);
    max_len(s3, 4, 3);
    return 0;
}
