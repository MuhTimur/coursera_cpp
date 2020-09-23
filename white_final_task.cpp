// Финальное задание курса Основы разработки на C++: белый пояс
// Всё в одном файле, потому что так требует Курсера

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
    Date() {
        this->year = 0;
        this->month = 0;
        this->day = 0;
    }

    Date(const int& input_year, const int& input_month, const int& input_day) {
        this->year = input_year;
        this->month = input_month;
        this->day = input_day;
    }

    int GetYear() const {
        return this->year;
    }
    
    int GetMonth() const {
        return this->month;
    }

    int GetDay() const {
        return this->day;
    }

private:
    int year;
    int month;
    int day;
};

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
    else // даты совпадают
        return false;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return (lhs.GetDay() == rhs.GetDay()) && (lhs.GetMonth() == rhs.GetMonth()) && (lhs.GetYear() == rhs.GetYear());
}

class Event {
public:
    Event(const string& input_name) {
        this->name = input_name;
    }

    string GetName() const {
        return this->name;
    }

private:
    string name;
};

bool operator<(const Event& lhs, const Event& rhs) {
    if (lhs.GetName() < rhs.GetName())
        return true;
    return false;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        this->dataset[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if(this->dataset.find(date) != this->dataset.end())
            if (this->dataset.at(date).find(event) != this->dataset.at(date).end())
                return this->dataset.at(date).erase(event);

        return false;
    }

    int  DeleteDate(const Date& date) {
        if (this->dataset.find(date) != this->dataset.end()) {
            int numberOfDeletedItems = this->dataset.at(date).size();
            this->dataset.at(date).clear();
            return numberOfDeletedItems;
        } 

        return 0;        
    }

    set<string> Find(const Date& date) const {
        set<string> result;

        if(this->dataset.find(date) != this->dataset.end())
            for (auto it : this->dataset.at(date))
                result.insert(it.GetName());        

        return result;
    }

    void Print() const {
        for (auto date : this->dataset) {
            for (auto event : date.second) {
                std::cout << std::setw(4) << std::setfill('0') << date.first.GetYear() << "-";
                std::cout << std::setw(2) << std::setfill('0') << date.first.GetMonth() << "-";
                std::cout << std::setw(2) << std::setfill('0') << date.first.GetDay() << " ";
                std::cout << event.GetName() << endl;
            }
        }
    }

private:
    map<Date, set<Event>> dataset;
};

void EnsureNextSymbolAndSkip(stringstream& stream) {
    if (stream.peek() != '-') {
        stringstream ss;
        ss << "expected - , but has: " << char(stream.peek());
        throw runtime_error(ss.str());
    }
    stream.ignore(1);
    if ((stream.peek() < '0' || stream.peek() > '9') && stream.peek() != '+' && stream.peek() != '-') {
        stringstream ss;
        ss << "expected digit, but has: " << char(stream.peek());
        throw runtime_error(ss.str());
    }
}

Date StringToDate(const string& s) {
    int year, month, day;
    stringstream stream(s);
    Date date;

    // проверка первого символа
    if (stream.peek() != '-' && stream.peek() != '+' && (stream.peek() < '0' || stream.peek() > '9')) {
        stringstream ss;
        ss << "Wrong date format: " << s;
        throw runtime_error(ss.str());
    }

    try {
        stream >> year;
        EnsureNextSymbolAndSkip(stream);
        stream >> month;
        EnsureNextSymbolAndSkip(stream);
        stream >> day;
        
    }
    catch (...) {
        stringstream ss;
        ss << "Wrong date format: " << s;
        throw runtime_error(ss.str());
    }

    // проверка последнего символа
    if (stream.peek() != -1) {
        stringstream ss;
        ss << "Wrong date format: " << s;
        throw runtime_error(ss.str());
    }

    // проверка корректности диапазонов
    if (month < 1 || month > 12) {
        stringstream ss;
        ss << "Month value is invalid: " << month;
        throw runtime_error(ss.str());
    }
    else if (day < 1 || day > 31) {
        stringstream ss;
        ss << "Day value is invalid: " << day;
        throw runtime_error(ss.str());
    }

    return Date(year, month, day);;
}


int main() {
    Database db;
    string command;

    while (getline(cin, command)) {
        // Считайте команды с потока ввода и обработайте каждую

        stringstream stream(command);
        string command_name;
        stream >> command_name;

        if (command_name == "Add") {
            Date date;
            string date_string, name;
            
            stream >> date_string;
            stream >> name;

            try {
                date = StringToDate(date_string);
            }
            catch (exception& ex) {
                std::cout << ex.what() << endl;
                continue;
            }
            db.AddEvent(date, name);
        }
        else if (command_name == "Del") {

            string date_string, name;
            Date date;

            stream >> date_string;
            stream >> name;

            try {
                date = StringToDate(date_string);
            }
            catch (exception& ex) {
                std::cout << ex.what() << endl;
                continue;
            }

            if (name == "") {
                int res = db.DeleteDate(date);
                std::cout << "Deleted " << res << " events" << endl;
            }
            else {
                if (db.DeleteEvent(date, name))
                    std::cout << "Deleted successfully" << endl;
                else
                    std::cout << "Event not found" << endl;
            }        
        }
        else if (command_name == "Find") {

            string date_string, name;
            Date date;

            stream >> date_string;
            stream >> name;

            try {
                date = StringToDate(date_string);
            }
            catch (exception& ex) {
                std::cout << ex.what() << endl;
                continue;
            }

            set<string> res = db.Find(date);

            if (!res.empty()) {
                for (string it : res) {
                    cout << it << endl;
                }
            }
        }
        else if (command_name == "Print") {
            db.Print();
        }
        else if(command_name != "") {
            std::cout << "Unknown command: " << command_name << endl;
        }
    }

    return 0;
}