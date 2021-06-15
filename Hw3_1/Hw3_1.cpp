#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <algorithm>
#include "Student.h"


using namespace std;

list<Student> allStudents;

Student getStudentInfo() {
	cout << "First name: ";
	string firstName;
	getline(cin, firstName);

	cout << "Second name: ";
	string secondName;
	getline(cin, secondName);

	cout << "Patronymic: ";
	string patronymic;
	getline(cin, patronymic);

	cout << "Year of birth: ";
	int birthYear;
	cin >> birthYear;
	cin.ignore();

	cout << "Group number: ";
	string groupNumber;
	getline(cin, groupNumber);

	return Student(firstName, secondName, patronymic, birthYear, groupNumber);
}

void executeLoadFromFileCommand() {
	cout << "File name: ";
	string fileName;
	getline(cin, fileName);

	allStudents.clear();
	ifstream inFile(fileName);
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			Student curStudent;
			inFile >> curStudent;
			allStudents.push_back(curStudent);

			while (inFile.peek() == '\n')
				inFile.ignore();
		}
	}
	else
		cout << "Failed to open file for reading!" << endl;
}

void executeSaveToFileCommand() {
	cout << "File name: ";
	string fileName;
	getline(cin, fileName);

	ofstream outFile(fileName);
	if (outFile.is_open()) {
		for (auto curStudent : allStudents)
			outFile << curStudent << endl;
	}
	else
		cout << "Failed to open file for writing!" << endl;
}

void executePrintStudentsCommand() {
	for (auto curStudent : allStudents)
		cout << curStudent << endl;
}

void executeAddStudentCommand() {
	allStudents.push_back(getStudentInfo());
}

void executeDeleteStudentCommand() {
	cout << "Enter second name: ";
	string secondName;
	getline(cin, secondName);

	auto delStudent = find_if(allStudents.begin(), allStudents.end(), [secondName](const Student& checkStudent) {
		return checkStudent.secondName() == secondName;
		});
	if (delStudent != allStudents.end())
		allStudents.erase(delStudent);
}


void executeFindBySecondNameCommand() {
	cout << "Enter second name: ";
	string secondName;
	getline(cin, secondName);

	auto foundStudent = find_if(allStudents.begin(), allStudents.end(), [secondName](const Student& s) {
		return s.secondName() == secondName;
		});
	if (foundStudent != allStudents.end())
		cout << *foundStudent << endl;
}

void executeFindByGroupNumberCommand() {
	cout << "Enter group number: ";
	string groupNumber;
	getline(cin, groupNumber);

	for_each(allStudents.begin(), allStudents.end(), [groupNumber](const Student& s) {
		if (s.groupNumber() == groupNumber)
			cout << s << endl;
		});
}

void executeSortBySecondNameCommand() {
	allStudents.sort([](const Student& s1, const Student& s2) {
		return s1.secondName() < s2.secondName();
		});
	executePrintStudentsCommand();
}

void executeSortByBirthYearCommand() {
	allStudents.sort([](const Student& s1, const Student& s2) {
		return s1.birthYear() < s2.birthYear();
		});

	executePrintStudentsCommand();
}

void executeClearStudentsCommand() {
	allStudents.clear();
}

void executeHelpCommand() {
	cout << COMMAND_HELP << " - display help for available commands" << endl;
	cout << COMMAND_LOAD_FROM_FILE << " - load students from file" << endl;
	cout << COMMAND_SAVE_TO_FILE << " - save students to file" << endl;
	cout << COMMAND_PRINT << " - display information about all students" << endl;
	cout << COMMAND_ADD_STUDENT << " - add new student" << endl;
	cout << COMMAND_DELETE_STUDENT << " - delete existing student" << endl;
	cout << COMMAND_FIND_BY_SECOND_NAME << " - find information about student by second name" << endl;
	cout << COMMAND_FIND_BY_GROUP_NUMBER << " - find information about students by group number" << endl;
	cout << COMMAND_SORT_BY_SECOND_NAME << " - sort students by second name" << endl;
	cout << COMMAND_SORT_BY_BIRTH_YEAR << " - sort students by year of birth" << endl;
	cout << COMMAND_CLEAR_STUDENTS << " - clear students" << endl;
	cout << COMMAND_QUIT << " - terminate the application" << endl;
	cout << endl;
}


static const char* COMMAND_QUIT = "quit";
static const char* COMMAND_HELP = "help";
static const char* COMMAND_LOAD_FROM_FILE = "load";
static const char* COMMAND_SAVE_TO_FILE = "save";
static const char* COMMAND_PRINT = "print";
static const char* COMMAND_ADD_STUDENT = "add";
static const char* COMMAND_DELETE_STUDENT = "delete";
static const char* COMMAND_FIND_BY_SECOND_NAME = "find_second_name";
static const char* COMMAND_FIND_BY_GROUP_NUMBER = "find_group_number";
static const char* COMMAND_SORT_BY_SECOND_NAME = "sort_second_name";
static const char* COMMAND_SORT_BY_BIRTH_YEAR = "sort_birth_year";
static const char* COMMAND_CLEAR_STUDENTS = "clear";


int main() {
	map<string, void (*)()> commandFunctions;
	commandFunctions[COMMAND_HELP] = executeHelpCommand;
	commandFunctions[COMMAND_LOAD_FROM_FILE] = executeLoadFromFileCommand;
	commandFunctions[COMMAND_SAVE_TO_FILE] = executeSaveToFileCommand;
	commandFunctions[COMMAND_PRINT] = executePrintStudentsCommand;
	commandFunctions[COMMAND_ADD_STUDENT] = executeAddStudentCommand;
	commandFunctions[COMMAND_DELETE_STUDENT] = executeDeleteStudentCommand;
	commandFunctions[COMMAND_FIND_BY_SECOND_NAME] = executeFindBySecondNameCommand;
	commandFunctions[COMMAND_FIND_BY_GROUP_NUMBER] = executeFindByGroupNumberCommand;
	commandFunctions[COMMAND_SORT_BY_SECOND_NAME] = executeSortBySecondNameCommand;
	commandFunctions[COMMAND_SORT_BY_BIRTH_YEAR] = executeSortByBirthYearCommand;
	commandFunctions[COMMAND_CLEAR_STUDENTS] = executeClearStudentsCommand;

	string command;
	while (command != COMMAND_QUIT) {
		cout << ">> ";
		getline(cin, command);

		if (commandFunctions.find(command) != commandFunctions.end())
			commandFunctions[command]();
	}

	return 0;
}