#include <iostream>
#include <vector>
#include <map>

using namespace std;

// char stack implemented using vector<char>
class Stack {
    public:
        Stack() {};
        vector<char> vec_stack;
        // true iff this stack is full
        bool isFull() {
            return false;
        }
        // true iff this stack is empty
        bool isEmpty() {
            return !vec_stack.size();
        }
        // removes and returns top item
        char pop() {
            int val = vec_stack.back();
            vec_stack.pop_back();
            return val;
        }
        // return top item without removing it
        char top() {
            return vec_stack.back();
        }
        
        // adds c to top of this stack
        void push(char c) {
            return vec_stack.push_back(c);
        }
        // return current size of the stack
        int getSize() {
            return vec_stack.size();
        }
};

/**
 * handles the incoming new word
 * @param depth_word_map the map in which word has to be pushed
 * @param stk is the stack used for parsing
 * @param word is the current word to be pushed
 * */
void handleNewWord(map<int, vector<string>>& depth_word_map, Stack* stk, string& word) {
    if (word.size())
        depth_word_map[stk->getSize()].push_back(word);
    word = "";
}

/**
 * handles the final formatting and logging of the output
 * @param depth_word_map the map from which the words to depth mapping is saved
 * @param stk is the stack used for parsing
 * */
void logFinalOutput(map<int, vector<string>>& depth_word_map, Stack* stk) {
    if (!stk->isEmpty()) {
        cout << "\t|mismatched groups!" << endl;
        return;
    }
    if (!depth_word_map.size()) {
        cout << "\t|" << endl;
        return;
    }
    for (auto &&depth_words : depth_word_map)
    {
        cout << "\t|";
        for (int i = 0; i < depth_words.first; i++)
            cout << "  ";
        for (auto &&word : depth_words.second)
            cout << word << " ";
        cout << endl;
    }
}

/**
 * reads in parenthesized text and, if valid, 
 * on a new line prints the text of each nesting level preceded with two spaces for level of nesting.
 * The text should be printed in order of nesting
 * @param s is the input string of parenthesized text
 * */
void logWordsWithLevel(string s) {
    map<int, vector<string>> depth_word_map;
    Stack* stk = new Stack();
    string word;
    for (auto &&each_char : s)
    {
        switch (each_char)
        {
            case '(':
                handleNewWord(depth_word_map, stk, word);
                stk->push(')');
                break;
            case '[':
                handleNewWord(depth_word_map, stk, word);
                stk->push(']');
                break;
            case '{':
                handleNewWord(depth_word_map, stk, word);
                stk->push('}');
                break;
            case ')':
            case '}':
            case ']':
                handleNewWord(depth_word_map, stk, word);
                if (stk->isEmpty() || stk->pop() != each_char) {
                    cout << "\t|mismatched groups!" << endl;
                    return;
                }
                break;
            default:
                word += each_char;
                break;
        }
    }

    handleNewWord(depth_word_map, stk, word);
    logFinalOutput(depth_word_map, stk);
}

int main()
{
    string s;
    cout << "input:\n\t";
    getline(cin, s);
    cout << "output:"<< endl;
    logWordsWithLevel(s);
    return 0;
}

// "yes(does{[[well!]]}work)this"
// this one sparks joy
// this one does'nt

// ([{}]){[{}]}
// ([}{])
// (does{[[well!]]}work)this
// (doesn’t{[[work!]})this
// 0_word(1_word[2_word{3_word 4_word}5_word]6_word)7_word
// _(![@])_
// single white spaced sentence