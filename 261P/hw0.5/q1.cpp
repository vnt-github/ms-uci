#include <vector>
#include <iostream>
#include <queue>

using namespace std;

// class minStack
// {
// private:
//     vector<int> stack;
//     vector<int> min_indices;
// public:
//     void push_back(int val) {
//         if (min_indices.empty() || stack[min_indices.back()] >= val)
//             min_indices.push_back(stack.size());
//         stack.push_back(val);
//     }
//     int pop_back() {
//         int return_val = stack.back();
//         stack.pop_back();
//         if (min_indices.back() == stack.size())
//             min_indices.pop_back();
//         return return_val;
//     }
//     int findMin() {
//         if (!stack.size())
//             throw "can't min for empty stack";

//         return stack[min_indices.back()];
//     }
// };

class minStack
{
private:
    vector<int> stack;
    vector<int> minimums;
public:
    void push_back(int val) {
        if (minimums.empty() || minimums.back() >= val)
            minimums.push_back(val);
        stack.push_back(val);
    }
    int pop_back() {
        int return_val = stack.back();
        stack.pop_back();
        if (minimums.back() == return_val)
            minimums.pop_back();
        return return_val;
    }
    int findMin() {
        if (!stack.size())
            throw "can't min for empty stack";

        return minimums.back();
    }
};

class QueueStack
{
private:
    queue<int> q;
public:
    void push_back(int val) {
        q.push(val);
    }

    int pop_back() {
        for (int i = 0; i < q.size()-1; i++)
        {
            int val = q.front();
            q.pop();
            q.push(val);
        }
        int toRet = q.front();
        q.pop();
        return toRet;
    }

    int top() {
        return q.back();
    }

    int size() {
        return q.size();
    }

    int isEmpty() {
        return q.empty();
    }
};



int main() {
    minStack stack;
    stack.push_back(1);
    cout << stack.findMin() << endl;
    stack.push_back(3);
    cout << stack.findMin() << endl;
    stack.push_back(-1);
    cout << stack.findMin() << endl;
    stack.push_back(100);
    cout << stack.findMin() << endl;
    stack.pop_back();
    stack.pop_back();
    cout << stack.findMin() << endl;
    stack.pop_back();
    cout << stack.findMin() << endl;

    cout << "---" << endl;

    minStack s;
    s.push_back(10);
    cout << s.findMin() << endl;
    s.push_back(9);
    cout << s.findMin() << endl;
    s.push_back(8);
    cout << s.findMin() << endl;
    s.push_back(10);
    cout << s.findMin() << endl;
    s.push_back(9);
    cout << s.findMin() << endl;
    s.push_back(8);
    cout << s.findMin() << endl;
    s.push_back(12);
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;
    s.push_back(7);
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;
    s.pop_back();
    cout << s.findMin() << endl;

    // QueueStack stack;
    // stack.push_back(10);
    // stack.push_back(9);
    // stack.push_back(8);
    // cout << stack.pop_back() << endl;
    // cout << stack.pop_back() << endl;
    // stack.push_back(1);
    // stack.push_back(2);
    // cout << stack.pop_back() << endl;
    // cout << stack.pop_back() << endl;
    // cout << stack.pop_back() << endl;
    // cout << stack.pop_back() << endl;

}