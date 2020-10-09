
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector<int> handleCarry(vector<int> num_arr) {
	vector<int> final_ans;
    int carry = 0, digit, next_carry;
    for (auto &&each : num_arr)
    {
        digit = each%10 + carry;
        next_carry = each/10;
        final_ans.push_back(digit);
        carry = next_carry;
    }
    if (carry) {
        final_ans.push_back(carry);
    }
    for (auto &&each : final_ans)
    {
        if (each >= 10)
            return handleCarry(final_ans);
    }
    
    return final_ans;
}


int multDigit(char a, char b) {
	return (a-'0')*(b-'0');
}

int multNums(string num1, string num2) {

    string rev_num1 = num1;
    string rev_num2 = num2;

    reverse(rev_num1.begin(), rev_num1.end());
    reverse(rev_num2.begin(), rev_num2.end());

    vector<vector<int>> ans;
    for (auto &&digit1 : rev_num1)
    {
        vector<int> sub_ans;
        for (auto &&digit2 : rev_num2)
        {
	        sub_ans.push_back(multDigit(digit1, digit2));
        }

        ans.push_back(handleCarry(sub_ans));
    }

    for (auto &&sub : ans)
    {
        for (auto &&each : sub)
        {
            cout << each;
        }
        cout << endl;
    }

    
    vector<int> final_ans;
    for (int i = 0; i < ans.size(); i++)
    {
        int carry = 0;
        for (int j = 0; j < ans[i].size(); j++)
        {
            while (i+j >= final_ans.size()) {
                final_ans.push_back(0);
            }

            final_ans[i+j] += ans[i][j];
            
        }

        final_ans = handleCarry(final_ans);
        
    }
    
    reverse(final_ans.begin(), final_ans.end());
    for (auto &&each : final_ans)
    {
        cout << each;
    }
    

}

int main(int argc, char const *argv[])
{
    // if (argc != 3) {
    //     cout << "usage main num1 num2" << endl;
    //     exit(0);
    // }

    string num2 = "654154154151454545415415454";// argv[1];
    string num1 = "63516561563156316545145146514654"; //argv[2];

    multNums(num1, num2);

    return 0;
}

    //     1 2 3
    //       4 5
    //     -----
    //     6 1 5
    //   4 9 2 *
    // ----------
    //   5 5 3 5 