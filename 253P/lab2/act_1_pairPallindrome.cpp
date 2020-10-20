#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isPalindrome(string s1, string s2) {
	string s = s1 + s2;

	int len_s = s.length();
	int inc_i =  len_s/2;
	int dec_i = (len_s%2) ? inc_i : inc_i - 1;

 	while (dec_i >= 0 && inc_i < len_s) {
	    if (s[inc_i] != s[dec_i])
            return false;
                inc_i += 1;
                dec_i -= 1;
    }
    return true;
}

vector<pair<int, int>> getPallindromPairs(vector<string> strings) {
    vector<pair<int, int>> ans;
	for (int i = 0; i < strings.size(); i++) {
		for(int j = i ; j < strings.size(); j++) {
			if (isPalindrome(strings[i], strings[j]))
				ans.push_back(make_pair(i, j));
				if (isPalindrome(strings[j], strings[i]))
					ans.push_back(make_pair(j, i));
		}
	}
	return ans;
}


int main(int argc, char const *argv[])
{
    return 0;
}
