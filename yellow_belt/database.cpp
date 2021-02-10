#include "database.h"

void Database::Add(const Date& date, const string& event) {
	if (dataset_set[date].insert(event).second) {
		dataset_vector[date].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for (auto date : this->dataset_vector)
		for (auto event : date.second)
			os << date.first << " " << event << endl;
}

Entry Database::Last(const Date& date) const {
	auto it = dataset_vector.upper_bound(date);
	if (it == dataset_vector.begin()) {
		throw invalid_argument("");
	}
	--it;

	return Entry(it->first, it->second.back());
}