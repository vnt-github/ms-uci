#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// @return sum of elements in the @param num_list
unsigned long int sum_list(vector<int>& num_list) {
    unsigned long int sum = 0;
    for (auto &&each : num_list)
        sum += each;
    return sum;
}

// @return missing no. value from @param num_list
int find_missing_item(vector<int> num_list) {
    unsigned long int n = num_list.size() + 1;
    return n*(n+1)/2 - sum_list(num_list);
}

int main(int argc, char const *argv[])
{
    unsigned long int n = 2147483647;
    cout << numeric_limits<int>::max() << endl;
    cout << (n*(n+1))/2 << endl;
    cout << find_missing_item({2, 4, 1}) << endl;
    cout << find_missing_item({1}) << endl;
    cout << find_missing_item({3, 4, 1, 2}) << endl;
    cout << find_missing_item({2, 1}) << endl;
    cout << find_missing_item({3, 1}) << endl;
    cout << find_missing_item({3, 2}) << endl;
    cout << find_missing_item({1,2,3,4,6,7, 8,9, 10,11, 12,13,14, 15}) << endl;
    return 0;
}
