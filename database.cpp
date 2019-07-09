// Реализуйте функции и методы классов и при необходимости добавьте свои

#include"database.h"


void Database::Add(const Date& date, const string& inputEvents){
    if(dbEvents[date].find(inputEvents) == dbEvents[date].end()){
        dbEvents[date].insert(inputEvents);
        events[date].push_back(inputEvents);
    }
}

void Database::Print(ostream& os) const {
    for(const auto& eventsDate : events){
        string date = "";
        int num = eventsDate.first.GetYear();
        if(num < 10){
            date += "000";
        }else if(num < 100){
            date += "00";
        }else if(num < 1000){
            date += "0";
        }
        date += to_string(num) + '-';
        num = eventsDate.first.GetMonth();
        if(num < 10){
            date += "0";
        }
        date += to_string(num) + '-';
        num = eventsDate.first.GetDay();
        if(num < 10){
            date += "0";
        }
        date += to_string(num);
        for(const auto& event : eventsDate.second){
            os << date << " " << event << endl;
        }
    }
};


int Database::RemoveIf(std::function<bool(const Date&, const string&)> predicate){
    int count = 0;
    for(auto iterMap(events.begin()); iterMap != events.end();){
        Date delDate = iterMap->first;
        auto predicateForErase = [&count, predicate, delDate](string& event){
            if(predicate(delDate, event)){
                //this->dbEvents[delDate].erase(event);
                count++;
                return false;
            }else
                return true;
        };
        auto delIter = stable_partition(iterMap->second.begin(), iterMap->second.end(), predicateForErase);
        //iterMap->second.erase(delIter, iterMap->second.end());
        int counter = iterMap->second.end() - delIter;
        for(int i(0); i < counter; i++){
            dbEvents[delDate].erase(iterMap->second[iterMap->second.size() - 1]);
            iterMap->second.pop_back();
        }
        if(iterMap->second.size() == 0){
            events.erase(iterMap++);
        }else {
            iterMap++;
        }
    }
    return count;
}

vector<string> Database::FindIf(std::function<bool(const Date&, const string&)> predicate)const{
    vector<string> foundEvents;
    for(const auto& eventsOfDate : events){
            for(const auto& event : eventsOfDate.second){
                if(predicate(eventsOfDate.first, event)){
                    foundEvents.push_back(eventsOfDate.first.GetDateString() + " " + event);
                }
            }
        }
    return foundEvents;
}

string Database::Last(const Date& date)const{
        auto foundIter = lower_bound(events.begin(), events.end(), pair<Date, vector<string>>(date, {""}));
        if(foundIter != events.begin() || date == foundIter->first){
            if(date != foundIter->first){
                --foundIter;
            }
            return foundIter->first.GetDateString() + " "
                + foundIter->second[foundIter->second.size() - 1];
        }else{
            return "No entries";
        }
        return foundIter->first.GetDateString() + " "
                + foundIter->second[foundIter->second.size() - 1];
}

bool operator<(pair<Date, vector<string>> lhs, pair<Date, vector<string>> rhs){
    return lhs.first < rhs.first;
}
