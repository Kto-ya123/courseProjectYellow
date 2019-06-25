#pragma once
#include <memory>
#include<string>
#include"date.h"

using namespace std;
enum class Comparison{
   Less,
   LessOrEqual,
   Greater,
   GreaterOrEqual,
   Equal,
   NotEqual,
};

enum class TypeNode{
    EmptyNode,
    DateComparisonNode,
    EventComparisonNode,
    LogicalOperationNode,
};

enum class LogicalOperation{
    And,
    Or,
};

class Node{
    virtual TypeNode type() = 0;
};

class EmptyNode : public Node{
    TypeNode type();
};

class DateComparisonNode : public Node{
public:
    DateComparisonNode(Comparison cmp, Date& date);
    TypeNode type();
    Comparison comparison;
    Date value;
};

class EventComparisonNode : public Node{
public:
    EventComparisonNode(Comparison cmp, string event);
    TypeNode type();
    Comparison comparison;
    string value;
};

class LogicalOperationNode : public Node{
public:
    LogicalOperationNode(LogicalOperation logOper, shared_ptr<Node>& lt, shared_ptr<Node>& rh);
    TypeNode type();
    LogicalOperation logicalOperation;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

};
