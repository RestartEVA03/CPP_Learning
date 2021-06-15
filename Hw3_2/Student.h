#pragma once

#include <string>
#include <iostream>


using namespace std;



class Student
{
private:
	string fFirstName;
	string fSecondName;
	string fPatronymic;
	int fBirthYear;
	string fGroupNumber;
public:
	Student() = default;
	Student(const Student& anotherStudent) = default;
	Student(const string& firstName, const string& secondName, const string& patronymic, const int birthYear, const string& groupNumber);
	string firstName() const;
	string secondName() const;
	string patronymic() const;
	int birthYear() const;
	string groupNumber() const;
	friend ostream& operator<<(ostream& out, const Student& p);
	friend istream& operator>>(istream& in, Student& p);
};


ostream& operator<<(ostream& out, const Student& p);
istream& operator>>(istream& in, Student& p);