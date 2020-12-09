#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:

// max contiguous subarray sum using KADANE'S ALGO
int max_subarray(vector<int> nums) {
    int max_current = nums[0];
    int max_global = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        max_current = max(max_current + nums[i],\
                         nums[i]);
        max_global = max(max_global, max_current);
    }
    return max_global;
}

};

int main(int argc, char const *argv[])
{
    Solution s = Solution();
    cout << s.max_subarray({-1, -5, 5, -1, -2, 1, 6, -3}) << endl;
    cout << s.max_subarray({1, 20, -100, 40, 25, -80, 60}) << endl;
    cout << s.max_subarray({10000, -9999999, 10000}) << endl;
    cout << s.max_subarray({10000, -999, 10000}) << endl;

    return 0;
}
