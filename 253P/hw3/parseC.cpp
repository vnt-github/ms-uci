#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * seeks the input file pointer till a non space character
 * this is to handle a stream of space characters like \t \r etc
 * @param program_file is the read input file stream
 * */
char skipSpaceAndGetChar(ifstream& program_file) {
    char curr_char;
    while (program_file.get(curr_char)) {
        if (!isspace(curr_char)) {
            program_file.putback(curr_char);
            return curr_char;
        }
    }
    return EOF;
}

/**
 * handles the single and double quote string
 * it needs to handle double inside single quote
 * single inside double and backslach exceptions
 * @param program_file is the read input file stream
 * */
void parseMatchingString(ifstream& program_file) {
    char parenthesis;
    program_file.get(parenthesis);
    cout << parenthesis;
    char curr_char;
    char prev_char;
    while (program_file.get(curr_char)) {
        if (curr_char == parenthesis && prev_char != '\\') {
            cout << parenthesis << endl;
            return;
        } else {
            prev_char = curr_char;
            cout << curr_char;
        }
    }
}

/**
 * parses a alpha numeric and underscored stream of characters as token
 * @param program_file is the read input file stream
 * */
void parseToken(ifstream& program_file) {
    string ans;
    char curr_char;
    while (program_file.get(curr_char)) {
        if (isalnum(curr_char) || curr_char == '_') {
            cout << curr_char;
        } else {
            program_file.putback(curr_char);
            cout << endl;
            return;
        }
    }
}

/**
 * parses various combinations of a character which is a operator
 * and different actions based on the next character like ++, += etc
 * @param program_file is the read input file stream
 * */
void parseOperator(ifstream& program_file) {
    char curr_char, next_char;
    program_file.get(curr_char);
    program_file.get(next_char);
    if ((curr_char != '*' && curr_char == next_char) || next_char == '=') {
        cout << curr_char << next_char << endl;
    } else {
        cout << curr_char << endl;
        program_file.putback(next_char);
    }
}

/**
 * parses the multi line comments
 * @param program_file is the read input file stream
 * */
void parseComment(ifstream& program_file) {
    char curr_char, prev_char;
    while (program_file.get(curr_char)) {
        if (curr_char == '/' && prev_char == '*') {
            return;
        } else {
            prev_char = curr_char;
        }
    }
}

/**
 * handles when the character encountered is /
 * because of various actions to be done based on 
 * the next character like // /= /token and multiline comment etc
 * @param program_file is the read input file stream
 * */
void parseForwardSlash(ifstream& program_file) {
    char curr_char, next_char;
    string s;
    program_file.get(curr_char);
    program_file.get(next_char);
    if (next_char == '/') {
        getline(program_file, s);
    } else if (next_char == '*') {
        parseComment(program_file);
    } else if (next_char == '=') {
        cout << curr_char << next_char << endl;
    } else {
        cout << curr_char << endl;
        program_file.putback(next_char);
    }
}

/**
 * main function which parses the c++ file
 * @param program_file is the read input file stream
 * */
void parse(ifstream& program_file) {
    char curr_char;
    string line;
    while ((curr_char = skipSpaceAndGetChar(program_file)) != EOF) {
        if (isalnum(curr_char) || curr_char == '_') {
            parseToken(program_file);
        } else if (curr_char == '\'' || curr_char == '"') {
            parseMatchingString(program_file);
        } else if (curr_char == '/') {
            parseForwardSlash(program_file);
        } else if (curr_char == '*' || curr_char == '+' || curr_char == '-' || curr_char == '=') {
            parseOperator(program_file);
        } else {
            program_file.get(curr_char);
            cout << curr_char << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        cerr << "usage: ./parseC.out [c file name to parse]";
        return 0;
    }
    ifstream program_file;

    program_file.open(argv[1]);
    if (!program_file.is_open()) {
        cerr << "unable to open the file " << argv[1] << endl;
        return -1;
    }

    parse(program_file);

    return 0;
}
