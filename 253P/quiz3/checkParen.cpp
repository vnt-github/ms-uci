#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


// returns if currChar is closing bracket
bool isClosingParen(char currChar) {
    return currChar == ')' || currChar == ']';
}

// pops matching bracket else pushes currChar
void handleParen(vector<int>& parenGroupStack,\
                char currChar) {
    unordered_map<char, char> opp =\
     { {'(', ')'}, {')', '('}, {'[', ']'}, {']', '['} };
    if (isClosingParen(currChar) &&\
        !parenGroupStack.empty() &&\
        parenGroupStack.back() == opp[currChar])
        parenGroupStack.pop_back();
    else
        parenGroupStack.push_back(currChar);
}

//fill neededParens from unmatched curved bracket
void fillRequiredCurvedParens(vector<int>& curvedParenStack,\
                              vector<int>& neededParens) {
    for (auto &&each : curvedParenStack) {
        switch (each) {
        case ')':
            neededParens[0] += 1; break;
        case '(':
            neededParens[1] += 1; break;
        default:
            break;
        }
    }
}

//fill neededParens from unmatched square bracket
void fillRequiredSquareParens(vector<int>&\
 squareParenStack, vector<int>& neededParens) {
    for (auto &&each : squareParenStack) {
        switch (each) {
        case ']':
            neededParens[2] += 1; break;
        case '[':
            neededParens[3] += 1; break;
        default:
            break;
        }
    }
}

// main fn parsing the input and invoking helpers fns
vector<int> checkParen(string input) {
    vector<int> curvedParenStack, squareParenStack;
    for (auto &&currChar : input) {
        switch (currChar) {
        case ')':
        case '(':
            handleParen(curvedParenStack, currChar);
            break;
        case ']':
        case '[':
            handleParen(squareParenStack, currChar);
            break;
        default:
            break;
        }  
    }
    vector<int> neededParens = { 0, 0, 0, 0 };
    fillRequiredCurvedParens(curvedParenStack, neededParens);
    fillRequiredSquareParens(squareParenStack, neededParens);
    return neededParens;
}

int main(int argc, char const *argv[])
{
    vector<int> ans;
    ans = checkParen("fill]]with[[)whatever)(even(@@^^!");
    for (auto &&each : ans)
        cout << each << " ";
    cout << endl;


    ans = checkParen("hello) ) my ) name ( ( is !( )");
    for (auto &&each : ans)
        cout << each << " ";
    cout << endl;

    ans = checkParen("(hello [my)name is ]");
    for (auto &&each : ans)
        cout << each << " ";
    cout << endl;

    ans = checkParen("(hello(my[name)");
    for (auto &&each : ans)
        cout << each << " ";
    cout << endl;

    ans= checkParen("(hello[ my[ (name is (ray) ] ] ]");
    for (auto &&each : ans)
        cout << each << " ";
    cout << endl;
    return 0;
}
