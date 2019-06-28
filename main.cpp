#include "database.h"
#include "condition_parser.h"
#include "test_runner.h"

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

void TestAll();

int main() {
    TestAll();
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
        for(int i(0); i < 10000; i++){
            db.Add(Date(i, 11, 10), to_string(i));
        }
        db.Print(cout);
        for(int i(0); i < 1000; i++){
            auto condition = make_shared<EventComparisonNode>(EventComparisonNode(Comparison::Equal, to_string(i)));
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            db.RemoveIf(predicate);

        }
        for(int i(0); i < 10000; i++){
            db.Last(Date(i, 11, 10));
        }
        db.Add(Date(2019,11,10), "xer");
        db.Print(cout);
    }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestBase, "Test DataBase");
  //tr.RunTest(TestParseEvent, "TestParseEvent");
  //tr.RunTest(TestParseCondition, "TestParseCondition");
}

