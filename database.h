#pragma once
// Реализуйте функции и методы классов и при необходимости добавьте свои
#include<exception>
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<set>
#include<map>
#include"date.h"
#include"node.h"
#include<functional>
#include<algorithm>

using namespace std;

class Database {
public:
    void Add(const Date& date, const string& inputEvents);
    int RemoveIf(std::function<bool(const Date&, const string&)>);
    string Last(const Date& date)const;
    vector<string> FindIf(std::function<bool(const Date&, const string&)>)const;
    void Print(ostream& os) const;
private:
    map<Date, vector<string>> events;
};
