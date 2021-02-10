#include "date.h"

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() > rhs.GetYear())
		return false;
	else if (lhs.GetYear() < rhs.GetYear())
		return true;
	else if (lhs.GetMonth() > rhs.GetMonth())
		return false;
	else if (lhs.GetMonth() < rhs.GetMonth())
		return true;
	else if (lhs.GetDay() > rhs.GetDay())
		return false;
	else if (lhs.GetDay() < rhs.GetDay())
		return true;
	else // same dates
		return false;
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return lhs < rhs || rhs == lhs;
}

bool operator>(const Date& lhs, const Date& rhs) {
	return !(lhs < rhs) && rhs != lhs;
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return lhs > rhs || rhs == lhs;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return (lhs.GetDay() == rhs.GetDay()) && (lhs.GetMonth() == rhs.GetMonth()) && (lhs.GetYear() == rhs.GetYear());
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

Date ParseDate(istream& is) {
	int year, month, day;

	string line;
	getline(is, line, '-');
	year = stoi(line);
	getline(is, line, '-');
	month = stoi(line);
	getline(is, line, ' ');
	day = stoi(line);

	return { year, month, day };
}

ostream& operator<< (std::ostream& os, const Date& date) {
	os << setw(4) << setfill('0') << date.GetYear() << "-";
	os << setw(2) << setfill('0') << date.GetMonth() << "-";
	os << setw(2) << setfill('0') << date.GetDay();
	return os;
}

Date::Date() {
	this->year = 0;
	this->month = 0;
	this->day = 0;
}

Date::Date(const int& input_year, const int& input_month, const int& input_day) {
	this->year = input_year;
	this->month = input_month;
	this->day = input_day;
}

int Date::GetYear() const {
	return this->year;
}

int Date::GetMonth() const {
	return this->month;
}

int Date::GetDay() const {
	return this->day;
}