#pragma once

#include<exception>
#include<iostream>
#include<cmath>
#include<string>

using namespace std;


class Date {
public:
    Date(string dateString);
    int GetYear() const;
    int GetMonth()const;
    int GetDay()const;

private:
    int year;
    int month;
    int day;
};

Date ParseDate(istream& is);

bool operator<(const Date& lhs, const Date& rhs);

