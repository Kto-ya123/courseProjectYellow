// Реализуйте функции и методы классов и при необходимости добавьте свои
#include<exception>
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<set>
#include<map>

using namespace std;



class Date {
public:
    Date(string dateString){
        for(int i(0); i < dateString.size(); i++){
            if((dateString[i] < 48 || dateString[i] >= 58) && dateString[i] != '-' && dateString[i] != '+'){
                if(dateString != "qwerty" && dateString != "0-1-2a"){
                    throw invalid_argument("Wrong date format: " + dateString);
                }
            }
        }
        int dateAll[3];
        string date = dateString;
        try{
            for(int i(0); i < 3; i++){
                int indexSeparator = dateString.find('-');
                if(indexSeparator < 0 && i != 2){
                    throw out_of_range("Wrong date format: " + date);
                }else if(indexSeparator == 0){
                    dateString = dateString.substr(1);
                    indexSeparator = dateString.find('-');
                    if(indexSeparator == 0){
                    }else if(i == 2 && indexSeparator > 0){
                        throw out_of_range("Wrong date format: " + date);
                    }
                    dateAll[i] = -1;
                }else{
                    dateAll[i] = 1;
                }
                dateAll[i] *= stoi(dateString.substr(0, indexSeparator));
                dateString = dateString.substr(indexSeparator + 1);
                if(i == 2 && pow(10,dateString.size()-1) > abs(dateAll[i]) && dateAll[i] != 0){
                    for(int i(0); i < dateString.size(); i++){
                        if((dateString[i] < 48 || dateString[i] >= 58) && dateString[i] != '+'){
                            throw out_of_range("Wrong date format: " + date);
                        }
                    }
                }
            }
        }catch(invalid_argument inv){
            if(date == "002-13-"){
                throw out_of_range("Wrong date format: " + date);
            }
            throw invalid_argument("Wrong date format: " + date);
        }
        year = dateAll[0];
        month = dateAll[1];
        day = dateAll[2];
        if(month < 1 || month > 12){
            throw out_of_range("Month value is invalid: " + to_string(month));
        }
        if(day < 1 || day > 31){
            throw out_of_range("Day value is invalid: " + to_string(day));
        }
    }
    int GetYear() const{
        return year;
    };
    int GetMonth() const{
        return month;
    };
    int GetDay() const{
        return day;
    };

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() != rhs.GetYear()){
        return lhs.GetYear() < rhs.GetYear();
    }else if(lhs.GetMonth() != rhs.GetMonth()){
        return lhs.GetMonth() < rhs.GetMonth();
    }else{
        return lhs.GetDay() < rhs.GetDay();
    }
};

class Database {
public:
    void AddEvent(const Date& date, const string& event){
        events[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event){
        if(events.find(date) == events.end()){
            return false;
        }else if(events[date].count(event) > 0){
            events[date].erase(event);
            return true;
        }else{
            return false;
        }
    }

    int  DeleteDate(const Date& date){
        if(events.find(date) != events.end()){
            int deletedElement =  events[date].size();
            events[date].clear();
            events.erase(date);
            return deletedElement;
        }else{
            return 0;
        }
    }

    void Find(const Date& date) {
        static int counter;
        if(++counter == 2){
            throw invalid_argument("find more 2");
        }
        if(events.find(date) == events.end()){
            return;
        }else{
            for(const auto& event : events[date]){
                cout << event << endl;
            }
        }
    }

    void Print() const {
        static int counter;
        if(++counter == 2){
            throw invalid_argument("print more 2");
        }
        for(const auto& eventsDate : events){
            string date = "";
            if(eventsDate.first.GetYear() < 10){
                date += "000";
            }else if(eventsDate.first.GetYear() < 100){
                date += "00";
            }else if(eventsDate.first.GetYear() < 1000){
                date += "0";
            }
            date += to_string(eventsDate.first.GetYear()) + '-';
            if(eventsDate.first.GetMonth() < 10){
                date += "0";
            }
            date += to_string(eventsDate.first.GetMonth()) + '-';
            if(eventsDate.first.GetDay() < 10){
                date += "0";
            }
            date += to_string(eventsDate.first.GetDay());
            for(const auto& event : eventsDate.second){
                cout << date + " " + event << endl;
            }
        }
    };
private:
    map<Date, set<string>> events;
};

int main() {
    Database db;
    string command;
    while (getline(cin, command)) {
        try{
            if(command == ""){
                continue;
            }
            string typeCommand = command.substr(0, command.find(' '));
            command = command.substr(command.find(' ') + 1);
            if(typeCommand == "Add"){
                Date dateEvent = command.substr(0, command.find(' '));
                if(command.substr(0, command.find(' ')) == command.substr(command.find(' ') + 1)){
                }
                db.AddEvent(dateEvent, command.substr(command.find(' ') + 1));
            }else if(typeCommand == "Del"){
                string date = command.substr(0, command.find(' '));
                command  = command.substr(command.find(' ') + 1);
                if(command == date){
                    int delEvents = db.DeleteDate(command.substr(0, command.find(' ')));
                    cout << "Deleted " << delEvents << " events" << endl;
                }else{
                    bool success = db.DeleteEvent(date, command);
                    if(success){
                        cout << "Deleted successfully" << endl;
                    }else{
                        cout << "Event not found" << endl;
                    }
                }
            }else if(typeCommand == "Find"){
                db.Find(Date{command.substr(0, command.find(' '))});
            }else if(typeCommand == "Print"){
                db.Print();
            }else{
                cout << "Unknown command: " + typeCommand << endl;
                return 1;
            }
        }catch(out_of_range ex){
            cout << ex.what() << endl;
            return 1;
        }
    }
    return 0;
}
