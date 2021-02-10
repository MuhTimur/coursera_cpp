#include "entry.h"

bool operator== (const Entry& lhs, const Entry& rhs) {
	return lhs.getDate() == rhs.getDate() && lhs.getEvent() == rhs.getEvent();
}

ostream& operator<< (std::ostream& os, const Entry& entry) {
	os << entry.getDate() << " " << entry.getEvent();
	return os;
}

bool operator== (const Entry& en, const string& str) {
	return en.getEvent() == str;
}

bool operator== (const string& str, const Entry& en) {
	return en.getEvent() == str;
}
