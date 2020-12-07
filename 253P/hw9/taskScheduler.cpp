// retuns a character frequency map for @param tasks
unordered_map<char, int> getCharMap(vector<char>& tasks) {
    unordered_map<char, int> char_map;
    for (auto &&each : tasks)
    {
        if (!char_map.count(each))
            char_map[each] = 0;
        char_map[each] += 1;
    }
    return char_map;
}

// return frequency of most frequenct char in @param character map
int getMaxCount(unordered_map<char, int>& char_map) {
    int max_count = 0;
    for (auto &&char_count : char_map)
        if (max_count < char_count.second)
            max_count = char_count.second;
    return max_count;
}

int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> char_map = getCharMap(tasks);
    int max_count = getMaxCount(char_map);
    int most_freq_elems_count = 0;
    
    for (auto &&char_count : char_map)
        if (char_count.second == max_count)
            most_freq_elems_count += 1;
    
    int emptySlots = (n - (most_freq_elems_count - 1))*(max_count-1);
    int availableTasks = tasks.size() - (max_count*most_freq_elems_count);
    int idle_cycles = emptySlots-availableTasks <= 0 ? 0 : emptySlots-availableTasks;

    return tasks.size() + idle_cycles;
}
