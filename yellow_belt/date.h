#pragma once
#include <sstream>
#include <iomanip>
#include <memory>

using namespace std;

class Date {
public:
	Date();
	Date(const int& input_year, const int& input_month, const int& input_day);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<< (std::ostream& out, const Date& date);

Date ParseDate(istream& is);