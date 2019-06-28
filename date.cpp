#include"date.h"

Date::Date(int _year, int _month, int _day): year(_year), month(_month), day(_day) {};

Date::Date(string dateString){
    int dateAll[3];
    try{
        for(int i(0); i < 3; i++){
            if(i == 2){
                dateAll[i] = stoi(dateString);
                continue;
            }
            int indexSeparator = dateString.find('-');
            dateAll[i] = stoi(dateString.substr(0, indexSeparator));
            dateString = dateString.substr(indexSeparator + 1);
        }
    }catch(invalid_argument inv){
    }
    year = dateAll[0];
    month = dateAll[1];
    day = dateAll[2];
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

string Date::GetDateString()const{
        string date = "";
        if(GetYear() < 10){
            date += "000";
        }else if(GetYear() < 100){
            date += "00";
        }else if(GetYear() < 1000){
            date += "0";
        }
        date += to_string(GetYear()) + '-';
        if(GetMonth() < 10){
            date += "0";
        }
        date += to_string(GetMonth()) + '-';
        if(GetDay() < 10){
            date += "0";
        }
        date += to_string(GetDay());
        return date;
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

bool operator>(const Date& lhs, const Date& rhs){
    return !(lhs < rhs);
}

bool operator==(const Date& lhs, const Date& rhs){
    return (lhs.GetYear() == rhs.GetYear()) &&
            (lhs.GetMonth() == rhs.GetMonth()) &&
            (lhs.GetDay() == rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs){
    return !(lhs == rhs);
}

ostream& operator<< (ostream& os, const Date& date){
    os.fill('0');
    os << setw(4) << date.GetYear() << '-';
    os << setw(2) << date.GetMonth() << '-';
    os << setw(2) << date.GetDay();
    return os;
}
