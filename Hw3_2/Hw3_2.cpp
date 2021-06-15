#include <iostream>
#include <fstream>
#include <map>
#include "Student.h"


using namespace std;


static const char* COMMAND_QUIT = "quit";
static const char* COMMAND_HELP = "help";
static const char* COMMAND_LOAD_FROM_FILE = "load";
static const char* COMMAND_SAVE_TO_FILE = "save";
static const char* COMMAND_PRINT = "print";
static const char* COMMAND_ADD_STUDENT = "add";
static const char* COMMAND_DELETE_STUDENT = "delete";
static const char* COMMAND_EDIT_STUDENT = "edit";
static const char* COMMAND_FIND_STUDENT = "find";
static const char* COMMAND_CLEAR_STUDENTS = "clear";


map<int, Student> allStudents;

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
			int recBookNumber;
			inFile >> recBookNumber;
			inFile.ignore();

			Student curStudent;
			inFile >> curStudent;

			allStudents[recBookNumber] = curStudent;

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
			outFile << curStudent.first << " " << curStudent.second << endl;
	}
	else
		cout << "Failed to open file for writing!" << endl;
}

void executePrintStudentsCommand() {
	for (auto curStudent : allStudents)
		cout << curStudent.first << " - " << curStudent.second << endl;
}

void executeAddStudentCommand() {
	cout << "Enter record book number: ";
	int recBookNumber;
	cin >> recBookNumber;
	cin.ignore();

	allStudents[recBookNumber] = getStudentInfo();
}

void executeDeleteStudentCommand() {
	cout << "Enter record book number: ";
	int recBookNumber;
	cin >> recBookNumber;
	cin.ignore();

	allStudents.erase(recBookNumber);
}

void executeEditStudentCommand() {
	cout << "Enter record book number: ";
	int recBookNumber;
	cin >> recBookNumber;
	cin.ignore();

	if (allStudents.find(recBookNumber) != allStudents.end())
		allStudents[recBookNumber] = getStudentInfo();
	else
		cout << "No such student!" << endl;
}

void executeFindStudentCommand() {
	cout << "Enter record book number: ";
	int recBookNumber;
	cin >> recBookNumber;
	cin.ignore();

	auto foundStudent = allStudents.find(recBookNumber);
	if (foundStudent != allStudents.end())
		cout << foundStudent->first << " - " << foundStudent->second << endl;
	else
		cout << "No such student!" << endl;
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
	cout << COMMAND_EDIT_STUDENT << " - edit existing student" << endl;
	cout << COMMAND_FIND_STUDENT << " - find information about student" << endl;
	cout << COMMAND_CLEAR_STUDENTS << " - clear students" << endl;
	cout << COMMAND_QUIT << " - terminate the application" << endl;
	cout << endl;
}


int main() {
	map<string, void (*)()> commandFunctions;
	commandFunctions[COMMAND_HELP] = executeHelpCommand;
	commandFunctions[COMMAND_LOAD_FROM_FILE] = executeLoadFromFileCommand;
	commandFunctions[COMMAND_SAVE_TO_FILE] = executeSaveToFileCommand;
	commandFunctions[COMMAND_PRINT] = executePrintStudentsCommand;
	commandFunctions[COMMAND_ADD_STUDENT] = executeAddStudentCommand;
	commandFunctions[COMMAND_DELETE_STUDENT] = executeDeleteStudentCommand;
	commandFunctions[COMMAND_EDIT_STUDENT] = executeEditStudentCommand;
	commandFunctions[COMMAND_FIND_STUDENT] = executeFindStudentCommand;
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
