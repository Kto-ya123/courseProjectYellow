#include"node.h"

EmptyNode::TypeNode type(){
    return TypeNode::EmptyNode;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, Date date) : comparison(cmp), value(date){}
DateComparisonNode::TypeNode type(){
    return TypeNode::EmptyNode;
}

EventComparisonNode::EventComparisonNode(Comparison cmp, string event) : comparison(cmp), value(event){}
EventComparisonNode::TypeNode type(){
    return TypeNode::EmptyNode;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logOper, shared_ptr<Node>& lt, shared_ptr<Node>& rh): logicalOperation(logOper), left(lt), right(rh){}
LogicalOperationNode::TypeNode type(){
    return TypeNode::EmptyNode;
}
