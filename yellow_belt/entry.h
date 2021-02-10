#pragma once
#include <vector>
#include <string>
#include "date.h"

using namespace std;

class Entry {
public:
	Entry(const Date& date_, const string& event_) : date(date_), event(event_) {};

	Date getDate() const {
		return date;
	}

	string getEvent() const {
		return event;
	}
private:
	Date date;
	string event;
};

bool operator== (const Entry& lhs, const Entry& rhs);
bool operator== (const Entry& en, const string& str);
bool operator== (const string& str, const Entry& en);

ostream& operator<< (std::ostream& os, const Entry& entry);