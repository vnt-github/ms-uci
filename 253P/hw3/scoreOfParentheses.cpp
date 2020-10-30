/**
 * returns an hash map with mapping of each opening brackets index
 * to it's corresponding closing bracket
 * @param S the input string
 * @return hash map with key as opening bracket index and value as closing bracket index
 * */
unordered_map<int, int> getClosingIndex(string& S) {
    unordered_map<int, int> closing;
    vector<int> stack;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == '(')
            stack.push_back(i);
        else {
            closing[stack.back()] = i;
            stack.pop_back();
        }

    }
    return closing;
}

/**
 * recursively calculates the score st
 * when start+1 == closing[start] i.e score("()outer") = 1+score(outer)
 * else score("(inner)outer") = 2*score(inner) + score(outer)
 * with terminating conditions if start > end return 0
 * @param start is the start index for the current recurssion call
 * @param end is the end index for the current recurssion call
 * @param S is the input string
 * @param closing is the hash map with matched opening index to closed index for S.
 * @return int representing score
 * */
int scoreRec(int start, int end, string& S, unordered_map<int, int>& closing) {
    if (start > end)
            return 0;
    else if (start+1 == closing[start]) {
        return 1 + scoreRec(closing[start]+1, end, S, closing);
    } else {
        return 2*scoreRec(start+1, closing[start]-1, S, closing) +\
         scoreRec(closing[start]+1, end, S, closing);
    }
}

/**
 * main function which is called to calculate the score of paretheses string
 * @param S is the input string
 * @return int representing score
 * */
int scoreOfParentheses(string S) {
    unordered_map<int, int> closing = getClosingIndex(S);
    return scoreRec(0, S.size()-1, S, closing);
}