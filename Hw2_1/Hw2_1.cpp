#include <iostream>
#include <fstream>
#include <queue>
#include "Student.h"
using namespace std;


int main() {

	queue<Student> studQueue;

	ifstream inFile("test_data.txt");
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			Student curStudent;
			inFile >> curStudent;
			studQueue.push(curStudent);
		}
	}
	else
		throw runtime_error("Failed to open file for reading!");

	cout << "Number of students: " << studQueue.size();
	cout << endl << endl;

	cout << "The first student in the queue:" << endl;
	cout << studQueue.front();
	cout << endl << endl;

	cout << "The last student in the queue:" << endl;
	cout << studQueue.back();
	cout << endl << endl;

	cout << "Output all queue:" << endl;
	while (!studQueue.empty())
	{
		cout << studQueue.front();
		studQueue.pop();
	}

}