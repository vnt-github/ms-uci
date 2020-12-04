#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// returns @return bool stating if two chars @param c1 and @param c2 are aligned or not
bool isAlign(char c1,  char c2) {
    return (c1 == 'A' && c2 == 'T') ||\
           (c1 == 'T' && c2 == 'A') ||\
           (c1 == 'C' && c2 == 'G') ||\
           (c1 == 'G' && c2 == 'C');
}

// @return cost associated with @param c1 and @param c2 mismatch
int getCost(char c1,  char c2) {
    if ((c1 == 'T' && c2 == 'T') || (c1 == 'C' && c2 == 'C') || (c1 == 'T' && c2 == 'C') || (c1 == 'C' && c2 == 'T'))
        return -6;
    if ((c1 == 'T' && c2 == 'G') || (c1 == 'G' && c2 == 'T') || (c1 == 'A' && c2 == 'C') || (c1 == 'C' && c2  == 'A'))
        return -7;
    if ((c1 == 'A' && c2 == 'A') || (c1 == 'G' && c2 == 'G') || (c1 == 'A' && c2 == 'G') || (c1 == 'G' && c2 == 'A'))
        return -10;
    return -1000000;
}

// build and log the final string usign @param s1, @param s2 and @param dp
void buildAndLog(string& s1, string& s2, vector<vector<int>>& dp) {
    string s1_ans;
    string s2_ans;
    int i = s1.size(), j = s2.size();

    while (i != 0 && j != 0) {
        if (isAlign(s1[i-1], s2[j-1]) ||\
            (dp[i-1][j-1] + getCost(s1[i-1], s2[j-1]) == dp[i][j])) {
            s1_ans = s1[--i] + s1_ans;
            s2_ans = s2[--j] + s2_ans;
        } else if (dp[i-1][j] - 4 == dp[i][j]){
            s1_ans = s1[--i] + s1_ans;
            s2_ans = "_" + s2_ans;
        } else {
            s1_ans = "_" + s1_ans;
            s2_ans = s2[--j] + s2_ans;
        }
    }
    while (i && !j) {
        s1_ans = s1[--i] + s1_ans;
        s2_ans = '_' + s2_ans;
    }

    while (!i && j) {
        s2_ans = s2[--j] + s2_ans;
        s1_ans = '_' + s1_ans;
    }
    cout << "output:" << endl << '\t' << s1_ans << endl << '\t' << s2_ans << endl << endl;
}

// @return the initiated dp with filled value for @param s1 and @param s2
vector<vector<int>> getInitDP(string& s1, string& s2) {
    vector<vector<int>> dp(s1.size()+1, vector<int>(s2.size()+1, 0)); 
    for (int i = 0; i <= (int) s1.size(); i++)
        dp[i][0] = -i;

    for (int i = 0; i <= (int) s2.size(); i++)
        dp[0][i] = -i;
    
    return dp;
}

// dp solver for DNA sequence alignment with penalty
void shiftAlign(string s1, string s2) {
    vector<vector<int>> dp = getInitDP(s1, s2);
    for (int i = 0; i < (int) s1.size(); i++)
        for (int j = 0; j < (int) s2.size(); j++)
            if (isAlign(s1[i], s2[j]))
                dp[i+1][j+1] = dp[i][j];
            else
                dp[i+1][j+1] = max({getCost(s1[i], s2[j]) + dp[i][j], -4 + dp[i][j+1], -4 + dp[i+1][j]});
    buildAndLog(s1, s2, dp);
}

int main()
{
    // shiftAlign("A", "T");
    // shiftAlign("A", "C");
    // shiftAlign("A", "G");
    // shiftAlign("T", "C");
    // shiftAlign("T", "G");
    // shiftAlign("C", "G");
    // shiftAlign("AGGGCT", "AGGCA");
    // shiftAlign("TTCGCT", "AAGGCT");
    // shiftAlign("AGCTTG", "TGCGAA");
    // shiftAlign("ACCTCG", "TGGAGC");
    string s1, s2;
    cout << "input:" << endl;
    cout << '\t';
    cin >> s1;
    cout << '\t';
    cin >> s2;
    shiftAlign(s1, s2);
    return 0;
}
