#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * generates all the non-empty perfect substrings of a string
 * @param word is the string whose substring are to be generated
 * @return list of non-empty perfect substrings
 * */
vector<string> getSubstrings(string word) {
    vector<string> sub_strings;
    for (int i = 0; i < word.size(); i++)
    {
        for (int j = i+1; j < word.size()+1; j++)
        {
            if (i == 0 && j == word.size()) continue;
            sub_strings.push_back(word.substr(i, j-i));
        }
    }
    return sub_strings;
}

/**
 * logs the final output
 * @param words is the list of input words
 * @param words_map is the hash map of words with their corresponding superstrings list
 * @param duplicates is the frequency count map to handle the duplicates
 * */
void printOutput(vector<string>& words, unordered_map<string, vector<string>>& words_map, unordered_map<string, int> duplicates) {
    cout << "output:" << endl;
    for (auto &&word : words)
    {
        cout << "\t" << word << ": ";
        for (auto &&value : words_map[word])
            cout << value << " ";
        for (int i = 0; i < duplicates[word]-1; i++)
            cout << word << " ";
        cout << endl;
    }
}

/**
 * main method which checks substring check for each word in list of words
 * @param words is the list of input words
 * */
void containsSubstrings(vector<string>& words) {
    unordered_map<string, vector<string>> words_map;
    unordered_map<string, int> duplicates;
    for (auto &&each : words) { words_map[each] = {}; duplicates[each] += 1; }
    for (auto &&word : words)
        for (auto &&sub_string : getSubstrings(word))
            if (words_map.find(sub_string) != words_map.end())
                words_map[sub_string].push_back(word);
    printOutput(words, words_map, duplicates);
}

int main(int argc, char const *argv[]) {
    int len_words = argc-1;
    vector<string> words;
    cout << "input:" << endl;
    for (int i = 1; i <= len_words; i++)
    {
        words.push_back(argv[i]);
        cout << "\t" << argv[i] << endl;
    }
    containsSubstrings(words);
    return 0;
}
