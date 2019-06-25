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
public:
    virtual TypeNode type()const = 0;
    virtual bool Evaluate(Date date, string event) const = 0;
};

class EmptyNode : public Node{
public:
    bool Evaluate(Date date, string event) const;
    TypeNode type()const;
};

class DateComparisonNode : public Node{
public:
    DateComparisonNode(Comparison cmp, Date date);
    bool Evaluate(Date date, string event) const;
    TypeNode type()const;
    Comparison comparison;
    Date value;
};

class EventComparisonNode : public Node{
public:
    EventComparisonNode(Comparison cmp, string event);
    bool Evaluate(Date date, string event) const;
    TypeNode type()const;
    Comparison comparison;
    string value;
};

class LogicalOperationNode : public Node{
public:
    LogicalOperationNode(LogicalOperation logOper, shared_ptr<Node> lt, shared_ptr<Node> rh);
    bool Evaluate(Date date, string event) const;
    TypeNode type()const;
    LogicalOperation logicalOperation;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};
