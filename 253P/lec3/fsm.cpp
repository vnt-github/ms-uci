#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Stack {
    public:
        Stack() {}; // constructs an empty stack (as linked list)
        vector<char> vec_stack;
        bool isFull() {
            // true iff this stack is full
            return false;
        } 
        bool isEmpty() {
            return !vec_stack.size();
        } // true iff this stack is empty
        char pop() {
            int val = vec_stack.back();
            vec_stack.pop_back();
            return val;
        } // removes and returns top item
        char top() {
            return vec_stack[0];
        } // return top item without removing it
        void push(char c) {
            return vec_stack.push_back(c);
        }// adds c to top of this stack
};

bool isBalanced(string s) {
    unordered_map<char, char> opp;
    char top;
    opp[')'] = '(';
    opp['}'] = '{';
    opp[']'] = '[';
    Stack* stk = new Stack();
    for (auto &&each_char : s)
    {
        switch (each_char)
        {
            case '(':
            case '[':
            case '{':
                stk->push(each_char);
                break;
            case ')':
            case '}':
            case ']':
                if (stk->isEmpty()) return false;
                top = stk->top();
                if (top != opp[top])
                    return false;
                else
                    stk->pop();
                break;
            default:
                break;
        }
    }

    return stk->isEmpty();
}

int main(int argc, char const *argv[])
{
    cout << isBalanced("((([[[{{{}}}]]])))") << endl;
    cout << isBalanced("[[[]]]{{{}}}((()))") << endl;
    cout << isBalanced("((([[[{{{}}}]]]))") << endl;
    cout << isBalanced("[[[]]]{{{}}}((())))") << endl;
    return 0;
}

// trick is to use  push ) for ()
