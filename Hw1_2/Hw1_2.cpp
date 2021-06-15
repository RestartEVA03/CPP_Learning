#include <iostream>
#include "Date.h"


using namespace std;

void testDate(const Date& dt) {
	cout << "Testing date: " << dt.toString(Date::Short) << " (" << dt.toString(Date::Long) << ")" << endl;
	cout << "Is leap year: " << Date::isLeapYear(dt) << endl;
	cout << "Days in month: " << Date::daysInMonth(dt) << endl;
	cout << "Day of week: " << Date::dayOfWeek(dt) << endl;
	cout << "Next friday: " << Date::nextFriday(dt).toString() << endl;
	cout << "Days between 01.04.2020 and " << dt.toString() << ": " << dt - Date("01.04.20") << endl;
	cout << "Next day: " << (dt + 1).toString() << endl;
	cout << "Previous day: " << (dt - 1).toString() << endl;
	cout << endl;
}


int main() {
	using std::cout;
	using std::invalid_argument;

	try {
		Date testDate1(29, 2, 2020);
		testDate(testDate1);
	}
	catch (invalid_argument & err) {
		cout << "TEST1 | ERROR: " << err.what() << endl;
		cout << "TERMINATING..." << endl;
		return 1;
	}

	try {
		Date testDate2("05.04.20");
		testDate(testDate2);
	}
	catch (invalid_argument & err) {
		cout << "TEST2 | ERROR: " << err.what() << endl;
		cout << "TERMINATING..." << endl;
		return 1;
	}

	return 0;
}