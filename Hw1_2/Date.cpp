#include <stdexcept>
#include <regex>
#include "Date.h"

static const uchar MONTH_DAYS[Date::MONTH_COUNT] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


const char* Date::MONTH_NAMES[MONTH_COUNT] = { "January", "February", "March", "April",
	"May", "June", "July", "August",
	"September", "October", "November", "December" };


bool Date::isLeapYear(const int checkYear) {
	if (checkYear % 100 == 0)
		return checkYear % 400 == 0;
	else
		return checkYear % 4 == 0;
}


bool Date::isLeapYear(const Date& checkDate) {
	return isLeapYear(checkDate.fYear);
}


int Date::daysInMonth(const int month, const int year) {
	if (month == 2 && isLeapYear(year))
		return 29;
	else
		return MONTH_DAYS[month - 1];
}


int Date::daysInMonth(const Date& dt) {
	return daysInMonth(dt.fMonth, dt.fYear);
}


int Date::daysInPreviousMonth(const Date& dt) {
	if (dt.fMonth == 1)
		return daysInMonth(MONTH_COUNT - 1, dt.fYear - 1);
	else
		return daysInMonth(dt.fMonth - 1, dt.fYear);
}


int Date::dayOfWeek(const Date& dt) {
	ushort year = dt.fYear;
	uchar month = dt.fMonth;

	if (month < 3u) {
		--year;
		month += 10u;
	}
	else
		month -= 2u;
	int weekday = (dt.fDay + 31u * month / 12u + year + year / 4u - year / 100u + year / 400u) % 7u;
	return (weekday == 0) ? 7 : weekday;
}


Date Date::nextFriday(const Date& dt) {
	int weekday = dayOfWeek(dt);
	int daysToNextFriday = 5 - weekday;
	if (daysToNextFriday < 0)
		daysToNextFriday += 7;
	return dt + daysToNextFriday;
}


Date::Date(const uchar day, const uchar month, const ushort year) {
	using std::invalid_argument;

	if (month == 0 || month > MONTH_COUNT)
		throw invalid_argument("Invalid month");
	if (day == 0 || day > daysInMonth(month, year))
		throw invalid_argument("Invalid day");

	fDay = day;
	fMonth = month;
	fYear = year;
}


Date::Date(const string& dateStr) {
	using std::regex;
	using std::regex_match;
	using std::smatch;
	using std::invalid_argument;
	using std::stoul;

	const regex checkFormatRegex("([0-9]{2})\\.([0-9]{2})\\.([0-9]{2})");
	smatch dateParts;
	if (!regex_match(dateStr, dateParts, checkFormatRegex))
		throw invalid_argument("Invalid date string");

	uchar day = stoul(dateParts[1].str());
	uchar month = stoul(dateParts[2].str());
	ushort year = stoul(dateParts[3].str());
	year = (year < 30) ? 2000 + year : 1900 + year;

	if (month == 0 || month > MONTH_COUNT)
		throw invalid_argument("Invalid month");
	if (day == 0 || day > daysInMonth(month, year))
		throw invalid_argument("Invalid day");

	fDay = day;
	fMonth = month;
	fYear = year;
}


string Date::toString(const Format dateFormat) const {
	using std::to_string;

	string result;
	if (dateFormat == Short) {
		if (fDay < 10)
			result += "0";
		result += to_string(fDay) + ".";

		if (fMonth < 10)
			result += "0";
		result += to_string(fMonth) + ".";

		uchar yearRem = fYear % 100;
		if (yearRem < 10)
			result += "0";
		result += to_string(yearRem);
	}
	else
		result += to_string(fDay) + " " + MONTH_NAMES[fMonth - 1] + " " + to_string(fYear);

	return result;
}


int Date::operator-(const Date& anotherDate) const {
	Date tmpDate = *this;
	int result = 0;

	if (tmpDate > anotherDate) {
		while (tmpDate != anotherDate) {
			++result;
			--tmpDate;
		}
	}
	else {
		while (tmpDate != anotherDate) {
			--result;
			++tmpDate;
		}
	}

	return result;
}


Date Date::operator-(const uchar days) const {
	Date tmpDate = *this;
	uchar daysToSub = days;
	while (daysToSub > 0) {
		--tmpDate;
		--daysToSub;
	}

	return tmpDate;
}


Date Date::operator-=(const uchar days) {
	*this = *this - days;
	return *this;
}


Date Date::operator+(const uchar days) const {
	uchar daysToAdd = days;
	Date tmpDate = *this;
	while (daysToAdd > 0) {
		++tmpDate;
		--daysToAdd;
	}

	return tmpDate;
}


Date Date::operator++() {
	int dm = daysInMonth(*this);
	if (fDay == dm) {
		fDay = 1;
		if (fMonth == MONTH_COUNT) {
			fMonth = 1;
			++fYear;
		}
		else
			++fMonth;
	}
	else
		++fDay;

	return *this;
}

Date Date::operator++(int) {
	Date oldDate = *this;
	++(*this);
	return oldDate;
}

Date Date::operator--() {
	--fDay;
	if (fDay == 0) {
		fDay = daysInPreviousMonth(*this);
		--fMonth;
		if (fMonth == 0) {
			fMonth = MONTH_COUNT;
			--fYear;
		}
	}

	return *this;
}

bool Date::operator!=(const Date& anotherDate) const {
	return fDay != anotherDate.fDay || fMonth != anotherDate.fMonth || fYear != anotherDate.fYear;
}


bool Date::operator>(const Date& anotherDate) const {
	return fYear > anotherDate.fYear ||
		(fYear == anotherDate.fYear && fMonth > anotherDate.fMonth) ||
		(fYear == anotherDate.fYear && fMonth == anotherDate.fMonth && fDay > anotherDate.fMonth);
}