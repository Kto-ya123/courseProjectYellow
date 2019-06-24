// Реализуйте функции и методы классов и при необходимости добавьте свои

#include"database.h"


void Database::Add(const Date& date, const string& inputEvents){
        events[date].insert(inputEvents);
}

bool Database::DeleteEvent(const Date& date, const string& event){
    if(events.find(date) == events.end()){
        return false;
    }else if(events[date].count(event) > 0){
        events[date].erase(event);
        return true;
    }else{
        return false;
    }
}

int  Database::DeleteDate(const Date& date){
    if(events.find(date) != events.end()){
        int deletedElement =  events[date].size();
        events[date].clear();
        events.erase(date);
        return deletedElement;
    }else{
        return 0;
    }
}

void Database::Find(const Date& date){
    if(events.find(date) == events.end()){
        return;
    }else{
        for(const auto& event : events[date]){
            cout << event << endl;
        }
    }
}

void Database::Print(ostream& os) const {
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
            os << date + " " + event << endl;
        }
    }
};


