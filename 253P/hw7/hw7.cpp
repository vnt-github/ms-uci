#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<int, string> int_roman_map = {
    { 1, "I" },
    { 4, "IV" },
    { 5, "V" },
    { 9, "IX" },
    { 10, "X" },
    { 40, "XL" },
    { 50, "L" },
    { 90, "XC" },
    { 100, "C" },
    { 400, "CD" },
    { 500, "D" },
    { 900, "CM" },
    { 1000, "M" }
};

vector<int> divisors = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };

// return division and modulus for num and divisor
pair<int, int> divmod(int num, int divisor) {
    return make_pair(num/divisor, num%divisor);
}

// build the new @ans based on divmod of @num @divisor and return quotient for @num  
int extendAns(int num, int divisor, string& ans) {
    pair<int, int> quo_rem = divmod(num, divisor);
    for (int i = 0; i < quo_rem.first; i++)
        ans += int_roman_map[divisor];
    return quo_rem.second;
}

// convert non negative integer to roman numeral
string intToRoman(int num) {
    string ans;
    for (auto &&divisor : divisors)
    {
        num = extendAns(num, divisor, ans);
        if (!num)
            break;
    }
    return ans;
}


unordered_map<char, int> roman_int_map = {
    { 'I',  1 },
    { 'V',  5 },
    { 'X',  10 },
    { 'L',  50 },
    { 'C',  100 },
    { 'D',  500 },
    { 'M',  1000 }
};

unordered_set<char> roman_digits = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

// check if the current character goes with next character to make 4(IV) 9(IX) etc. 
bool isCombined(string& s, int i) {
    return i+1 < (int) s.length() && (
            (s[i] == 'I' && (s[i+1] == 'V' || s[i+1] == 'X')) ||\
            (s[i] == 'X' && (s[i+1] == 'L' || s[i+1] == 'C')) ||\
            (s[i] == 'C' && (s[i+1] == 'D' || s[i+1] == 'M'))
        );
}

// convert roman numeral to integer
int romanToInt(string s) {
    int i = 0, value = 0;
    while (i < (int) s.length()) {
        if (isCombined(s, i)) {
            value += roman_int_map[s[i+1]]-roman_int_map[s[i]];
            i += 2;
        } else {
            value += roman_int_map[s[i]];
            i += 1;
        }
    }
    return value;
}

// check if string is integer
bool isNumber(string s)
{
    for (auto &&each : s)
        if (!isdigit(each))
            return false;
    return true;
}

// check if string fits roman numeral
bool isRomanNumber(string s) {
    for (auto &&each : s)
        if (roman_digits.find(each) == roman_digits.end())
            return false;
    return true;
    
}

// process input and call appropriate handler
void handleInput() {
    string ip;
    while (true)
    {
        cin >> ip;
        cin.clear(); cin.ignore();
        transform(ip.begin(), ip.end(), ip.begin(), ::toupper);
        if (isNumber(ip))
            cout << intToRoman(stoi(ip)) << endl;
        else if (isRomanNumber(ip))
            cout << romanToInt(ip) << endl;
        else
            cout << "input does not fit non negative integer or roman numeral" << endl;
    }
}

int main()
{
    handleInput();
    return 0;
}
