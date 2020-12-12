#include <iostream>
// #include <cmath>

using namespace std;

// return @param base to the power @param radix
int pow(int base, int radix) {
    if (radix == 1) return base;
    if (radix == 0) return 1;
    int sub = pow(base, radix/2);
    return (sub*sub) * pow(base, radix%2);
}

int find_cool_number(int A) {
    int num = 0, p = 0;
    for (int i = 9; i >= 2 && A > 1; i--)
        if (!(A%i)) {
            num = i*pow(10, p++) + num;
            A = A/(i++);
        }
    return A == 1? num: 0;
}

int main(int argc, char const *argv[])
{



    cout << find_cool_number(100) << endl;
    cout << find_cool_number(2520) << endl;

    cout << find_cool_number(10) << endl;

    cout << find_cool_number(17) << endl;
    cout << find_cool_number(143) << endl;

    cout << find_cool_number(48) << endl;
    cout << find_cool_number(12) << endl;
    cout << find_cool_number(144) << endl;
    cout << find_cool_number(22) << endl;
    return 0;
}
