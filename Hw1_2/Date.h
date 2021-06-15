#pragma once


#include <string>


using std::string;
using uchar = unsigned char;
using ushort = unsigned short;

class Date {
private:
	uchar fDay = 1;
	uchar fMonth = 1;
	ushort fYear = 1;
public:
	enum Format {
		Short,
		Long
	};
	static const uchar MONTH_COUNT = 12;
	static const char* MONTH_NAMES[MONTH_COUNT];
	static bool isLeapYear(const int checkYear);
	static bool isLeapYear(const Date& checkDate);
	static int daysInMonth(const Date& dt);
	static int daysInMonth(const int month, const int year);
	static int daysInPreviousMonth(const Date& dt);
	static int dayOfWeek(const Date& dt);
	static Date nextFriday(const Date& dt);
	Date() = default;
	Date(const uchar day, const uchar month, const ushort year);
	Date(const string& dateStr);
	virtual ~Date() = default;
	string toString(const Format dateFormat = Short) const;
	int operator-(const Date& anotherDate) const;
	Date operator-(const uchar days) const;
	Date operator+(const uchar days) const;
	Date operator-=(const uchar days);
	Date operator++();
	Date operator++(int);
	Date operator--();
	bool operator!=(const Date& anotherDate) const;
	bool operator>(const Date& anotherDate) const;
};