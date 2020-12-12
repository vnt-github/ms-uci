vector<int> matches;
vector<int> stack;
// match the parentheses in the @param string s
void match(string& s) {
    for (short i = 0; i < s.length(); i++)
    {
        if (stack.size() && s[stack.back()] == '(' && s[i] == ')') {
            matches[stack.back()] = i;
            matches[i] = stack.back();
            stack.pop_back();
        } else {
            stack.push_back(i);
        }
    }
}

// return length of the longest valid parentheses substring using matches
int getLength() {
    int i = 0, counter = 0, ans = 0;
    while (i < matches.size()) {
        if (matches[i] == -1) {
            if (counter > ans) ans = counter;
            counter = 0;
            i+=1;
        } else {
            counter += matches[i] - i + 1;
            i = matches[i] + 1;
        }
    }
    if (counter > ans) ans = counter;
    return ans;
}

// solution to leetcode 32. longest valid parentheses
int longestValidParentheses(string s) {
    matches = vector<int>(s.length(), -1);
    int i = 0;
    match(s);
    return getLength();
}
