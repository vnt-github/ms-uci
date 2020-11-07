#include <iostream>
using namespace std;
string reverse(string str) {
    string ans;
    for (auto &&each : str)
        ans = each+ans;
    return ans;
}

int main(int argc, char const *argv[])
{
    cout << reverse("");
    return 0;
}
