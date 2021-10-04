#include <iostream>

using namespace std;

template<typename Object>
Object test() {
    Object arr[10];
    return arr[0]++;
}

int main() {
    cout << test() << endl;
    return 1;
}
