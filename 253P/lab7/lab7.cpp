unordered_map<char, string> digitCharsMap = {
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}
};
    
// add new char permutations to build new answer
vector<string> pushToAns(vector<string>& ans, char digit_char) {
    vector<string> new_ans;
    for (auto &&each_char: digitCharsMap[digit_char])
        for (auto &&each: ans)
            new_ans.push_back(each+each_char);
    return new_ans;
}

// iterate to build answer based on digits to character mapping
vector<string> letterCombinations(string digits) {
    vector<string> ans = {""};
    for (auto &&each_digit_char : digits)
        ans = pushToAns(ans, each_digit_char);
    if (ans[0] == "")
        return {};
    return ans;
}
