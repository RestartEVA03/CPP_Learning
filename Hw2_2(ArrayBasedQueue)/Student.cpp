#include "Student.h"


Student::Student(const string& firstName, const string& secondName, const string& patronymic, const int birthYear, const string& groupNumber)
{
	fFirstName = firstName;
	fSecondName = secondName;
	fPatronymic = patronymic;
	fBirthYear = birthYear;
	fGroupNumber = groupNumber;
}


string Student::firstName() const {
	return fFirstName;
}

string Student::secondName() const {
	return fSecondName;
}

string Student::patronymic() const {
	return fPatronymic;
}

int Student::birthYear() const {
	return fBirthYear;
}

string Student::groupNumber() const {
	return fGroupNumber;
}

ostream& operator<<(ostream& out, const Student& p) {
	out << p.fFirstName << " ";
	out << p.fSecondName << " ";
	out << p.fPatronymic << " ";
	out << p.fBirthYear << " ";
	out << p.fGroupNumber;
	return out;
}


istream& operator>>(istream& in, Student& p) {
	in >> p.fFirstName >> p.fSecondName;
	in >> p.fPatronymic;
	in >> p.fBirthYear;
	in >> p.fGroupNumber;
	return in;
}
