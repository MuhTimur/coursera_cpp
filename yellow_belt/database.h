#pragma once

#include "date.h"
#include "entry.h"

#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <memory>
#include <cmath>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	Entry Last(const Date& date) const;

    template<typename Predicate>
    vector<string> FindIf(Predicate predicate) const {
        vector<string> result;
        stringstream ss;

        for (auto& date : dataset_vector) {
            for (const auto& event : date.second) {
                if (predicate(date.first, event)) {
                    stringstream ss;
                    ss << date.first << " " << event;
                    result.push_back(ss.str());
                    ss.clear();
                }
            }
        }
        return result;
    }

    template <typename Predicate>
    int RemoveIf(Predicate predicate) {
        int result = 0;

        for (auto& entry : dataset_vector) {
            Date curr_date = entry.first;

            auto middle = stable_partition(entry.second.begin(), entry.second.end(),
                [=](auto const& event) {return predicate(curr_date, event); });

            result += distance(entry.second.begin(), middle);

            for (auto it = entry.second.begin(); it != middle; ++it) {
                dataset_set[curr_date].erase(*it);
            }

            entry.second.erase(entry.second.begin(), middle);
        }

        // Remove empty dates
        for (auto it = dataset_vector.begin(); it != dataset_vector.end(); ) {
            if (it->second.empty()) {
                dataset_set.erase(it->first);
                it = dataset_vector.erase(it);
            }
            else {
                it++;
            }
        }

        return result;
    }

private:
	map<Date, vector<string>> dataset_vector;
    map<Date, set<string>> dataset_set;
};