/**
 * validate weather the given pushed and popped values are valid when
 * operated on an empty stack
 * @param pushed is the input pushed element stack
 * @param popped is the popped input element stack
 * @return bool representing weather it's valid or not to do so
 * */
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    int popped_i = 0, push_i = 0, popped_num;
    vector<int> stack;
    while (popped_i < popped.size() && push_i <= pushed.size()) {
        popped_num = popped[popped_i];
        if (stack.size() && stack.back() == popped_num) {
            stack.pop_back(); popped_i += 1;
        } else if (push_i < pushed.size())
            stack.push_back(pushed[push_i++]);
        else
            return false;
    }
    return !stack.size();
}