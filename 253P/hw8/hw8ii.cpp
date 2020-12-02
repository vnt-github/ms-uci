#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool isAlign(char c1,  char c2) {
    return (c1 == 'A' && c2 == 'T') ||\
           (c1 == 'T' && c2 == 'A') ||\
           (c1 == 'C' && c2 == 'G') ||\
           (c1 == 'G' && c2 == 'C');
}

int getCost(char c1,  char c2) {
    if ((c1 == 'T' && c2 == 'T') || (c1 == 'C' && c2 == 'C') || (c1 == 'T' && c2 == 'C') || (c1 == 'C' && c2 == 'T'))
        return -6;
    if ((c1 == 'T' && c2 == 'G') || (c1 == 'G' && c2 == 'T') || (c1 == 'A' && c2 == 'C') || (c1 == 'C' && c2  == 'A'))
        return -7;
    if ((c1 == 'A' && c2 == 'A') || (c1 == 'G' && c2 == 'G') || (c1 == 'A' && c2 == 'G') || (c1 == 'G' && c2 == 'A'))
        return -10;
    return -1000000;
}


pair<string, string> build(string& s1, string& s2, vector<vector<int>>& dp) {
    string s1_ans;
    string s2_ans;
    int i = s1.size();
    int j = s2.size();

    while (i != 0 && j != 0) {
        if (isAlign(s1[i-1], s2[j-1])) {
            s1_ans = s1[i-1] + s1_ans;
            s2_ans = s2[j-1] + s2_ans;
            i -= 1;
            j -= 1; 
        } else if (dp[i-1][j-1] + getCost(s1[i-1], s2[j-1]) == dp[i][j]) {
            s1_ans = s1[i-1] + s1_ans;
            s2_ans = s2[j-1] + s2_ans;
            i -= 1;
            j -= 1; 
        } else if (dp[i-1][j] - 4 == dp[i][j]){
            s1_ans = s1[i-1] + s1_ans;
            s2_ans = "_" + s2_ans;
            i -= 1;
        } else if (dp[i][j-1] - 4 == dp[i][j]) {
            s1_ans = "_" + s1_ans;
            s2_ans = s2[j-1] + s2_ans;
            j -= 1;
        } else {
            s1_ans = s1[i-1] + s1_ans;
            s2_ans = s2[j-1] + s2_ans;
            i -= 1;
            j -= 1; 
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
    return make_pair(s1_ans, s2_ans);
}

void shiftAlign(string s1, string s2) {
    vector<vector<int>> dp(s1.size()+1, vector<int>(s2.size()+1, 0)); 
    for (int i = 0; i <= (int) s1.size(); i++)
        dp[i][0] = -i;

    for (int i = 0; i <= (int) s2.size(); i++)
        dp[0][i] = -i;

    vector<char> s1_ans;
    vector<char> s2_ans;
    for (int i = 0; i < (int) s1.size(); i++)
    {
        for (int j = 0; j < (int) s2.size(); j++)
        {   
            if (isAlign(s1[i], s2[j])) {
                dp[i+1][j+1] = dp[i][j];
            } else {
                dp[i+1][j+1] = max({getCost(s1[i], s2[j]) + dp[i][j], -4 + dp[i][j+1], -4 + dp[i+1][j]});
            }
        }
    }
    pair<string, string> ans = build(s1, s2, dp);
    cout << ans.first << endl << ans.second << endl << endl;
}

int main()
{
    shiftAlign("A", "T");
    shiftAlign("A", "C");
    shiftAlign("A", "G");
    shiftAlign("T", "C");
    shiftAlign("T", "G");
    shiftAlign("C", "G");
    shiftAlign("AGGGCT", "AGGCA");
    shiftAlign("TTCGCT", "AAGGCT");
    shiftAlign("AGCTTG", "TGCGAA");
    shiftAlign("ACCTCG", "TGGAGC");
    return 0;
}
