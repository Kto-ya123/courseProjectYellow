#include "database.h"
#include "condition_parser.h"
#include "test_runner.h"
#include<time.h>
#include<sstream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is){
    string inputEvent;
    getline(is, inputEvent);
    while(inputEvent[0] == ' '){
        inputEvent = inputEvent.substr(1);
    }
    return inputEvent;
}

ostream& operator<< (ostream& os, const pair<Date, vector<string>>& outData){
    for(const auto& event : outData.second){
        os << outData.first << " " << event;
    }
    return os;
}

void TestAll();

int main() {
  //TestAll();
  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

/*void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}*/
void TestBase(){
    Database db;
    {
        float startAdding = clock()/(float)CLOCKS_PER_SEC;
        for(int j(0); j < 100; j++){
            for(int i(0); i < 20000; i++){
                db.Add(Date(j, 11, 10), to_string(i));
            }
        }
        float timeAdding = (clock()/(float)CLOCKS_PER_SEC) - startAdding;
        //db.Print(cout);
        float fTimeStart = clock()/(float)CLOCKS_PER_SEC;
        for(int i(0); i < 2; i++){
            auto condition = make_shared<EventComparisonNode>(EventComparisonNode(Comparison::NotEqual, to_string(i)));
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            db.RemoveIf(predicate);
        }
        float fTimeEnd = clock()/(float)CLOCKS_PER_SEC;
        float timeRemoveOne = fTimeEnd - fTimeStart;
        for(int i(0); i < 10000; i++){
            db.Last(Date(i, 11, 10));
        }
        float timeLast = (clock()/(float)CLOCKS_PER_SEC) - fTimeEnd;
        fTimeEnd = clock()/(float)CLOCKS_PER_SEC;
        db.Add(Date(2019,11,10), "xer");
        db.Print(cout);
        for(int i(0); i < 10000; i++){
            db.Add(Date(i, 11, 10), to_string(i));
        }
        float timeAdd = (clock()/(float)CLOCKS_PER_SEC) - fTimeEnd;
        fTimeEnd = clock()/(float)CLOCKS_PER_SEC;
        db.Print(cout);
        float fTimePrint = (clock()/(float)CLOCKS_PER_SEC) - fTimeEnd;
        fTimeEnd = clock()/(float)CLOCKS_PER_SEC;

        auto condition = make_shared<DateComparisonNode>(DateComparisonNode(Comparison::LessOrEqual, Date(9999, 9,9)));
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        db.RemoveIf(predicate);
        float timeDelete = (clock()/(float)CLOCKS_PER_SEC) - fTimeEnd;
        for(int i(0); i < 10000; i++){
            db.Add(Date(i, 11, 10), to_string(i));
        }
        fTimeEnd = clock()/(float)CLOCKS_PER_SEC;
        {
        for(int i(0); i < 1; i++){
            //auto condition = make_shared<EventComparisonNode>(EventComparisonNode(Comparison::Equal, to_string(i)));
            auto condition = make_shared<EmptyNode>(EmptyNode());
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            db.FindIf(predicate);
        }
        }
        float timeFind = (clock()/(float)CLOCKS_PER_SEC) - fTimeEnd;
        cout << "timePrint: " << fTimePrint <<endl;
        cout << "timeAdding: " << timeAdding <<endl;
        cout << "timeDeleteByOne: " << timeRemoveOne <<endl;
        cout << "timeLast: " << timeLast <<endl;
        cout << "timeAdd: " << timeAdd <<endl;
        cout << "timeDelete: " <<timeDelete <<endl;
        cout << "timeFind: " << timeFind <<endl;
        db.Add(Date(2019,11,10), "xer");
        //db.Print(cout);
    }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestBase, "Test DataBase");
  //tr.RunTest(TestParseEvent, "TestParseEvent");
  //tr.RunTest(TestParseCondition, "TestParseCondition");
}

