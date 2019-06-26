// Реализуйте функции и методы классов и при необходимости добавьте свои

#include"database.h"


void Database::Add(const Date& date, const string& inputEvents){
        events[date].insert(inputEvents);
}

bool Database::DeleteEvent(const Date& date, const string& event){
    if(events.find(date) == events.end()){
        throw invalid_argument("viter");
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
    throw invalid_argument("find");
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


int Database::RemoveIf(std::function<bool(const Date&, const string&)> predicate){
    int count = 0;
    static int i = 0;
    for(auto& eventsOfDate : events){
        if(events[eventsOfDate.first].size() == 0){
                    events.erase(eventsOfDate.first);
        }
    }
    for(auto& eventsOfDate : events){
        for(auto& event : eventsOfDate.second){
            if(predicate(eventsOfDate.first, event)){
                DeleteEvent(eventsOfDate.first, event);
                count++;
            }
        }
    }
    return count;
}

vector<string> Database::FindIf(std::function<bool(const Date&, const string&)> predicate)const{
    vector<string> foundEvents;
    for(auto& eventsOfDate : events){
        for(const auto& event : eventsOfDate.second){
            if(predicate(eventsOfDate.first, event)){
                string foundEvent = "";
                foundEvent += eventsOfDate.first.GetDateString() + " ";
                foundEvent += event;
                foundEvents.push_back(foundEvent);
            }
        }
    }
    return foundEvents;
}

string Database::Last(const Date& date)const{
    throw invalid_argument("last");
    if(events.empty()){
        return "No entries";
    }
    DateComparisonNode predicate(Comparison::LessOrEqual, date);
    string foundEvent = "";
    for(auto& eventsOfDate : events){
        for(auto& event : eventsOfDate.second){
            if(predicate.Evaluate(eventsOfDate.first, event)){
                foundEvent = "";
                foundEvent += eventsOfDate.first.GetDateString() + " ";
                foundEvent += event;
            }else{
                if(foundEvent == ""){
                    return "No entries";
                }else{
                    return foundEvent;
                }
            }
        }
    }
    return foundEvent;
}

