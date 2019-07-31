#pragma once
// Реализуйте функции и методы классов и при необходимости добавьте свои
#include<exception>
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<set>
#include<list>
#include<map>
#include"date.h"
#include"node.h"
#include<functional>
#include<algorithm>
#include<iomanip>

using namespace std;

class Database {
public:
    void Add(const Date& date, const string& inputEvents);
    int RemoveIf(const std::function<bool(const Date&, const string&)>&);
    string Last(const Date& date)const;
    vector<string> FindIf(const std::function<bool(const Date&, const string&)>&)const;
    void Print(ostream& os) const;
private:
    map<Date, set<string>> events_set;
    map<Date, vector<string>> events_vector;
    set<Date> dates;
};

bool operator<(pair<Date, vector<string>> lhs, pair<Date, vector<string>> rhs);
