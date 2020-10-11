bool getStartOfListPtr(File* fileptr) {
	// find the “student# Name Email…” line, and return the file ptr from the next line;
	String line;
	While (getline(fileptr, line)) {
		if (line.find(“Student#”) != string::npos) {
	// start of the student entries is the next line
	return true;
}
}
return false; // could not find the student# line
}





// split the students into the groups
vector<vector<string>>& split_students(const vector<string>& student_names, const, const int group_size)
{
	// at most, there will be 17 students
	int group_count = student_names.size() / group_size;
	int left_students = student_names.size() % group_size;
	vector<vector<string>> result(group_count);
	vector<string> group;
	for(int i=0; i < student_names.size() ; i++) {
		result[i%(group_count)].push_back(student_name.at(i));
}
// handle left students

return result;
}

// populate all student names
void populate_student_names(vector<string> &student_names, File* fileptr, set<string>& absent_students)
{
	String line;
	String names;
	while(getline(fileptr, line)) {
		// end of the student list is marked by empty line hence below check
if (line == “”) break;
		Size_t nameindex = line.find(‘\t’);
		Size_t endNameIndex = line.find(‘\t’, nameindex+1);
		String student_name_with_com = line.substr(nameindex, endName);
		Size_t com =  student_name_with_com.find(‘,’);
		String student_lastname = student_name_with_com.split(0,com)
		// +2 because there is a space before first name

	
		

		String student_firstname = student_name_with_com.substr(com+2,student_name_with_com.length());
		If (absent_students.find(student_firstname) != absent_students.end())
			continue;

student_names.push_back(student_firstname+” ”+student_lastname);
}
}
Void read_absent_students(set<string> &absent_students) {
	String full_name;
	while(getline(cin, full_name) != ‘q’) {
		absent_students.add(full_name);
}
	
} 

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        cout << "file name and size of groups args required" << endl;
        return 0;
    }

    cout << argv[1] << endl;
    FILE * file;
    file = fopen(argv[1], “r”);
    if(file == NULL)
    {
          cout << "file name and size of groups args required" << endl;
        return 0;
    }
getStartOfListPtr(file);
set <string> absent_students;
	read_absent_students(absent_students);

vector<string> student_names;
populate_student_names(student_names, file, absent_student);
vector<vector<string>> students_in_group = split_students(student_name, group_size);
print_students_group(students_in_group);
    return 0;
}



