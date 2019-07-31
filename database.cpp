// Реализуйте функции и методы классов и при необходимости добавьте свои

#include"database.h"


void Database::Add(const Date& date, const string& inputEvents){
    if((events_set[date].insert(inputEvents)).second == true){
        events_vector[date].push_back(inputEvents);
    }
}

void Database::Print(ostream& os) const {
    for(const auto& eventsDate : events_vector){
        ostringstream str;
        str << setfill('0');
        str << setw(4) << eventsDate.first.GetYear() << '-';
        str << setw(2) << eventsDate.first.GetMonth() << '-';
        str << setw(2) << eventsDate.first.GetDay();
        for(const auto& event : eventsDate.second){
            os << str.str() << " " << event << endl;
        }
    }
};


int Database::RemoveIf(const std::function<bool(const Date&, const string&)>& predicate){
    int count = 0;
    for(auto iterMap(events_vector.begin()); iterMap != events_vector.end();){
        const Date& delDate = iterMap->first;
        auto predicateForErase = [&count, &predicate, &delDate](string& event){
            if(predicate(delDate, event)){
                return false;
            }else
                return true;
        };
        auto delIter = stable_partition(iterMap->second.begin(), iterMap->second.end(), predicateForErase);
        auto eventsDate = &events_set[iterMap->first];
        for(auto iter(delIter); iter != iterMap->second.end(); iter++){
            count++;
            eventsDate->erase(*iter);
        }
        iterMap->second.erase(delIter, iterMap->second.end());
        if(iterMap->second.size() == 0){
            //dates.erase(iterMap->first);
            events_set.erase(iterMap->first);
            events_vector.erase(iterMap++);
        }else {
            iterMap++;
        }
    }
    return count;
}

vector<string> Database::FindIf(const std::function<bool(const Date&, const string&)>& predicate)const{
    vector<string> foundEvents;
    for(const auto& eventsOfDate : events_vector){
            string date = eventsOfDate.first.GetDateString();
            for(const auto& event : eventsOfDate.second){
                if(predicate(eventsOfDate.first, event)){
                    foundEvents.push_back(date + " " + event);
                }
            }
        }
    return foundEvents;
}

string Database::Last(const Date& date)const{
    auto foundIter = upper_bound(events_vector.begin(), events_vector.end(), date);
    if(foundIter != events_vector.begin()){
        --foundIter;
        return foundIter->first.GetDateString() + " "
            + foundIter->second[foundIter->second.size() - 1];
    }else{
        return "No entries";
    }
}

bool operator< (const Date& date, const pair<Date, vector<string>>& lhs){
    return date < lhs.first;
}
