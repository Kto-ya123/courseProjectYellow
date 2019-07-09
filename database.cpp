// Реализуйте функции и методы классов и при необходимости добавьте свои

#include"database.h"


void Database::Add(const Date& date, const string& inputEvents){
    auto& eventsDate =  events[date];
    if(eventsDate.second.find(inputEvents) == eventsDate.second.end()){
        dates.insert(date);
        eventsDate.second.insert(inputEvents);
        eventsDate.first.push_back(inputEvents);
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
        for(const auto& event : eventsDate.second.first){
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
                count++;
                return false;
            }else
                return true;
        };
        auto delIter = stable_partition(iterMap->second.first.begin(), iterMap->second.first.end(), predicateForErase);
        //iterMap->second.erase(delIter, iterMap->second.end());
        int counter = iterMap->second.first.end() - delIter;
        for(int i(0); i < counter; i++){
            iterMap->second.second.erase(iterMap->second.first[iterMap->second.first.size() - 1]);
            iterMap->second.first.pop_back();
        }
        if(iterMap->second.first.size() == 0){
            dates.erase(iterMap->first);
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
            for(const auto& event : eventsOfDate.second.first){
                if(predicate(eventsOfDate.first, event)){
                    foundEvents.push_back(eventsOfDate.first.GetDateString() + " " + event);
                }
            }
        }
    return foundEvents;
}

string Database::Last(const Date& date)const{
    auto foundIter = lower_bound(events.begin(), events.end(), pair<Date, pair<vector<string>, set<string>>>{date, {{""}, {""}}});
    if(foundIter != events.begin() || date == foundIter->first){
        if(date != foundIter->first){
            --foundIter;
        }
        return foundIter->first.GetDateString() + " "
            + foundIter->second.first[foundIter->second.first.size() - 1];
    }else{
        return "No entries";
    }
    return foundIter->first.GetDateString() + " "
            + foundIter->second.first[foundIter->second.first.size() - 1];
}

bool operator<(const pair<Date, pair<vector<string>, set<string>>>& lhs, const pair<Date, pair<vector<string>, set<string>>>& rhs){
    return lhs.first < rhs.first;
}
