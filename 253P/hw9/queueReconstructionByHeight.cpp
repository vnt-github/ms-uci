// comparison function for two person
static bool compare(vector<int> p1, vector<int> p2) {
    return p1[0] > p2[0] || (p1[0] == p2[0] && p1[1] < p2[1]);
}

// solution to 406. Queue Reconstruction by Height
vector<vector<int>> reconstructQueue(vector<vector<int>>& vec_people) {
    sort(vec_people.begin(), vec_people.end(), compare);
    vector<vector<int>> sol;
    for (auto person : vec_people)
        sol.insert(sol.begin() + person[1], person);
    return sol;
}
