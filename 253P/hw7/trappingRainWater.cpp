int trap(vector<int>& height) {
    if (!height.size()) return 0;
    
    vector<int> left_max = { height[0] };
    for (int i=1; i < height.size(); i++)
        left_max.push_back(max(left_max.back(), height[i]));
    
    vector<int> right_max = { height.back() };
    for (int i = height.size() - 2; i >= 0; i--)
        right_max.push_back(max(right_max.back(), height[i]));

    int ans = 0;
    int n = right_max.size()-1;
    for(int i=0; i < height.size(); i++)
        ans += min(left_max[i], right_max[n-i])-height[i];
    return ans;
}