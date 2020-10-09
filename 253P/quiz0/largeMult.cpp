
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector<int> handleCarry(vector<int> num_arr) {
	vector<int> final_ans;
    int carry = 0, digit;
    for (auto &&each : num_arr)
    {
        digit = (each + carry)%10;
        carry = (each + carry)/10;
        final_ans.push_back(digit);
    }
    if (carry) {
        final_ans.push_back(carry);
    }

    return final_ans;
}


int multDigit(char a, char b) {
	return (a-'0')*(b-'0');
}

string multNums(string num1, string num2) {

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
    
    vector<int> final_ans;
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            if (i+j >= final_ans.size()) {
                final_ans.push_back(ans[i][j]);
            } else {
                final_ans[i+j] += ans[i][j];
            }
        }

        final_ans = handleCarry(final_ans);
        
    }
    
    reverse(final_ans.begin(), final_ans.end());
    string string_ans;
    for (auto &&digit : final_ans)
    {
        string_ans += (digit+'0');
    }
    
    return string_ans;
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        cout << "usage main num1 num2" << endl;
        exit(0);
    }

    string num1 = argv[1]; // "1235421415454545454545454544"; 
    string num2 = argv[2]; // "1714546546546545454544548544544545";

    cout << multNums(num1, num2) << endl;

    return 0;
}

    //     1 2 3
    //       4 5
    //     -----
    //     6 1 5
    //   4 9 2 *
    // ----------
    //   5 5 3 5 