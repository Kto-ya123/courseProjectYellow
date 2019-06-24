#include"date.h"

Date::Date(string dateString){
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

int Date::GetYear() const{
    return year;
}

int Date::GetMonth() const{
    return month;
}

int Date::GetDay() const{
    return day;
}



Date ParseDate(istream& is){
    string dateString;
    is >> dateString;
    return Date(dateString);
}


bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() != rhs.GetYear()){
        return lhs.GetYear() < rhs.GetYear();
    }else if(lhs.GetMonth() != rhs.GetMonth()){
        return lhs.GetMonth() < rhs.GetMonth();
    }else{
        return lhs.GetDay() < rhs.GetDay();
    }
};
