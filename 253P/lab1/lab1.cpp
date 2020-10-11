#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <random>
#include <algorithm>

using namespace std;

/**
 * reads from the standard input the list of absent students
 * @return set of absent students
 * */
set<string> getAbsentStudents() {
    string absent_student_name;
    set<string> absent_students;
    cout << "enter the name of absent student in the following format" << endl;
    cout << "last_name, first_name [middle_name(optional)]" << endl;
    while (getline(cin, absent_student_name))
    {
        if (absent_student_name == "q") break;
        absent_students.insert(absent_student_name);
    }
    return absent_students;
}

/**
 * seeks the file read pointer till the start of the student lists
 * @param roster: the input file stream to be read from
 * @return bool representing finding such point
 * */
bool seekTillStartOfList(ifstream& roster) {
    string line;
    string list_start_marker = "Student#";
    while(getline(roster, line)) {
        if (line.substr(0, list_start_marker.length()) == list_start_marker)
            return true;
    }
    return false;
}

/**
 * splits a string on the delimiter
 * @param str is the string to be split
 * @param delim is the delimeter to be split upon
 * @return a vector of strings by splitting str on delim
 * */
vector<string> split(string& str, char delim)
{
    vector<string> values;
    std::stringstream ss(str);
    string value;
    while (std::getline(ss, value, delim)) {
        values.push_back(value);
    }
    return values;
}

/**
 * returns a list of valid students after filtering absent students from all input file students
 * @param roster: the input file stream to be read from
 * @param abset_students is a set of absent student to be queried to be filtered
 * @return a list of valid students present
 * */
vector<string> getAllStudents(ifstream& roster, set<string> absent_students) {
    string student_info, student_name;
    vector<string> student_names;
    if(!seekTillStartOfList(roster)) {
        cerr << "could not find the start of students list marked with Students#" << endl;
        return student_names; 
    }
    while (getline(roster, student_info)) {
        if (student_info == "") break;
        student_name = split(student_info, '\t')[1];
        if (absent_students.find(student_name) != absent_students.end())
            continue;
        student_names.push_back(student_name);
    }
    return student_names;
}

/**
 * randomize the list of students and split into groups of group_size
 * @param students is the list of students to be grouped.
 * @param group_size is the target group size
 * @return list of group which is list of students.
 * */
vector<vector<string>> groupRandomStudents(vector<string>& students, int group_size) {
    srand(unsigned(time(NULL)));
    random_shuffle(students.begin(), students.end());

    int no_groups = group_size > int(students.size()) ? 1 : int(students.size()) / group_size;
    vector<vector<string>> groups(no_groups);
    for (int i = 0; i < int(students.size()); i++)
    {
        groups[i%no_groups].push_back(students[i]);
    }
    return groups;
}

/**
 * outputs the groups assigned to the standard input
 * @param groups: is the groups of students
 * */
void printGroups(vector<vector<string>> groups) {
    cout << "groups are as follows" << endl;
    for (int group_i = 0; group_i < int(groups.size()); group_i++)
    {
        cout << "group_no:" << group_i+1 << endl;
        for (auto &&student_name : groups[group_i])
        {
            cout << "\t" << student_name << endl;
        }
    }
}

/**
 * check if a string is a integer
 * @param s is the string to be checked
 * @return boolean representing if s is Number or not.
 * */
bool isNumber(string s)
{ 
    for (auto &&each : s)
        if (!isdigit(each))
            return false;

    return true;
}

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        cout << "file name and size of groups args required" << endl;
        return 0;
    }
    string file_name = argv[1];
    if (!isNumber(argv[2]) or stoi(argv[2]) <= 0) {
        cerr << "invalid groups size, only non negative integers are accepted" << endl;
        return -1;
    }
    int group_size = stoi(argv[2]);

    ifstream roster;
    roster.open(file_name);

    if (!roster.is_open()) {
        cerr << "unable to open the " << file_name << " file." << endl;
        return -1;
    }

    set<string> absent_students = getAbsentStudents();

    vector<string> students = getAllStudents(roster, absent_students);

    vector<vector<string>> groups = groupRandomStudents(students, group_size);

    printGroups(groups);

    return 0;
}
