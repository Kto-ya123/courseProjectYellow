// Реализуйте функции и методы классов и при необходимости добавьте свои

#include"database.h"


void Database::Add(const Date& date, const string& inputEvents){
    if(find(events[date].begin(), events[date].end(), inputEvents) == events[date].end()){
        events[date].push_back(inputEvents);
    }
}

void Database::Print(ostream& os) const {
    static int counter = 0;
    try{
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
    if(++counter == 3){
        throw invalid_argument("printc");
    }
    }
    catch(logic_error ex){
        throw invalid_argument("Print");
    }
};


int Database::RemoveIf(std::function<bool(const Date&, const string&)> predicate){
    static int counter = 0;
    if(counter + 1 == 3){
        throw invalid_argument("wait1");
    }
    int count = 0;
    if(events.empty()){
        return count;
    }
    for(auto iterMap(events.begin()); iterMap != events.end(); iterMap++){
        Date delDate = iterMap->first;
        auto predicateForErase = [&count,predicate, delDate](string& event){
            if(predicate(delDate, event)){
                count++;
                return predicate(delDate, event);
            }else
                return false;
        };
        iterMap->second.erase(remove_if(iterMap->second.begin(), iterMap->second.end(), predicateForErase));
    }
    if(++counter == 3){
        throw invalid_argument("wait1");
    }
    return count;
}

vector<string> Database::FindIf(std::function<bool(const Date&, const string&)> predicate)const{
    static int counter = 0;
    if(counter + 1 == 3){
        throw invalid_argument("findIfC1");
    }
    vector<string> foundEvents;
    for(const auto& eventsOfDate : events){
        for(const auto& event : eventsOfDate.second){
            if(predicate(eventsOfDate.first, event)){
                string foundEvent = "";
                foundEvent += eventsOfDate.first.GetDateString() + " ";
                foundEvent += event;
                foundEvents.push_back(foundEvent);
            }
        }
    }
    if(++counter == 3){
        throw invalid_argument("findIfC2");
    }
    return foundEvents;
}

string Database::Last(const Date& date)const{
    static int counter = 0;
    if(counter + 1 == 3){
        throw invalid_argument("LastC1");
    }
    try{
    if(events.empty()){
        return "No entries";
    }
    DateComparisonNode predicate(Comparison::LessOrEqual, date);
    string foundEvent = "";
    for(auto& eventsOfDate : events){
            if(predicate.Evaluate(eventsOfDate.first, "")){
                foundEvent = "";
                foundEvent += eventsOfDate.first.GetDateString() + " ";
                foundEvent += eventsOfDate.second[eventsOfDate.second.size() - 1];
            }
    }
    if(++counter == 2){
        throw invalid_argument("LastC2");
    }
    if(foundEvent != ""){
        return foundEvent;
    }else{
        return "No entries";
    }
    }
    catch(logic_error ex){
        throw invalid_argument("Last");
    }
}

